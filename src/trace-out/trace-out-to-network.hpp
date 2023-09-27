#pragma once

#include "trace-out/integer.hpp"
#include "trace-out/platform-detection.hpp"
#include "trace-out/untyped.hpp"
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <utility>

//
// Public

namespace trace_out_stream
{

inline void print(const char *string);
inline void flush();
inline unsigned int width();

}

//
// Private

namespace trace_out
{

std::ostream &trace_out_to_network_error();

bool is_valid_port_string(const char *string);
std::pair<std::string, standard::uint16_t> host_port_from_string(const char *string, std::string &error);

inline void really_send(untyped<> descriptor, const void *what, standard::size_t how_much);
inline void do_not_send(untyped<> descriptor, const void *what, standard::size_t how_much);
void (*socket_send)(untyped<> descriptor, const void *what, standard::size_t how_much) = do_not_send;

inline void really_close(untyped<> descriptor);
inline void do_not_close(untyped<> descriptor);
void (*socket_close)(untyped<> descriptor) = do_not_close;

class connection
{
public:
	inline connection(const char *endpoint);
	inline ~connection();

public:
	untyped<> descriptor;
};

inline connection &connection_instance();

}

//
// Implementation

namespace trace_out_stream
{

void print(const char *string)
{
	trace_out::socket_send(trace_out::connection_instance().descriptor, reinterpret_cast<const trace_out::standard::uint8_t *>(string), std::strlen(string));
}

void flush()
{
}

unsigned int width()
{
#if defined(TRACE_OUT_WIDTH)
	return TRACE_OUT_WIDTH;
#else
	return 80;
#endif
}

}

namespace trace_out
{

std::ostream &trace_out_to_network_error()
{
	return std::cerr << "trace-out-to-network-error: ";
}

bool is_valid_port_string(const char *string)
{
	for ( ; std::isdigit(*string); ++string);

	return *string == '\0';
}

std::pair<std::string, standard::uint16_t> host_port_from_string(const char *string, std::string &error)
{
	const char *delimiter = std::strchr(string, ':');
	if (delimiter == NULL || delimiter == string)
	{
		error = "host is not specified";
		return std::pair<std::string, standard::uint16_t>();
	}

	std::string host(string, delimiter);

	const char *port_string = delimiter + 1;
	if (*port_string == '\0')
	{
		error = "port is not specified";
		return std::pair<std::string, standard::uint16_t>();
	}

	if (!is_valid_port_string(port_string))
	{
		error = error + "port is not a number - '" + port_string + '\'';
		return std::pair<std::string, standard::uint16_t>();
	}

	standard::uint16_t port(std::atoi(delimiter + 1));

	error = "";
	return std::make_pair(host, port);
}

void do_not_send(untyped<>, const void *, standard::size_t)
{
}

void do_not_close(untyped<>)
{
}

connection &connection_instance()
{
	static connection instance(TRACE_OUT_TO_NETWORK);
	if (instance.descriptor == -1)
	{
		return instance;
	}
	return instance;
}

connection::~connection()
{
	socket_close(descriptor);
}

}

#if defined(TRACE_OUT_POSIX)

//
// POSIX Implementation

#include <cstring> // [amalgamate: leave]
#include <netdb.h> // [amalgamate:leave]
#include <sys/socket.h> // [amalgamate: leave]
#include <unistd.h> // [amalgamate: leave]

namespace trace_out
{

connection::connection(const char *endpoint)
	:
	descriptor(-1)
{
	untyped<> desc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (desc == -1)
	{
		trace_out_to_network_error() << "failed to open socket (" << strerror(errno) << ')' << std::endl;
		return;
	}

	std::string error;
	std::pair<std::string, standard::uint16_t> host_port = host_port_from_string(endpoint, error);
	if (!error.empty())
	{
		trace_out_to_network_error() << error << std::endl;
		return;
	}

	hostent *host_entry = gethostbyname(host_port.first.c_str());
	if (host_entry == NULL)
	{
		trace_out_to_network_error() << "unrecognized host - '" << host_port.first << '\'' << std::endl;
		return;
	}

	sockaddr_in socket_address;
	socket_address.sin_family = AF_INET;
	std::memcpy(&(socket_address.sin_addr.s_addr), host_entry->h_addr, host_entry->h_length);
	socket_address.sin_port = htons(host_port.second);
	int retval = connect(desc, reinterpret_cast<sockaddr *>(&socket_address), sizeof(socket_address));
	if (retval == -1)
	{
		trace_out_to_network_error() << "failed to connect to '" << endpoint << "' (" << strerror(errno) << ')' << std::endl;
		return;
	}

	socket_send = really_send;
	socket_close = really_close;
	descriptor = desc;
}

void really_send(untyped<> descriptor, const void *what, standard::size_t how_much)
{
	if (how_much == 0)
	{
		return;
	}

	ssize_t retval = send(descriptor, what, how_much, 0);
	if (retval == -1)
	{
		really_close(descriptor);
		trace_out_to_network_error() << "failed to send (" << strerror(errno) << ')' << std::endl;
		return;
	}

	if (retval == 0)
	{
		really_close(descriptor);
		trace_out_to_network_error() << "socket disconnected" << std::endl;
		return;
	}
}

void really_close(untyped<> descriptor)
{
	socket_send = do_not_send;
	socket_close = do_not_close;
	shutdown(descriptor, SHUT_RDWR);
	close(descriptor);
}

}

#elif defined(TRACE_OUT_WINDOWS)

//
// WinAPI Implementation

#pragma comment(lib, "Ws2_32.lib")

#include <WinSock2.h> // [amalgamate:leave]
#include <ws2tcpip.h> // [amalgamate:leave]
#include <Windows.h> // [amalgamate:leave]

namespace trace_out
{

size_t no_trailing_newline(char *string, size_t size);
std::string error_to_string(int code);

}

namespace trace_out
{

size_t no_trailing_newline(char *string, size_t size)
{
	const char *last_two_chars = string + size - 2;
	return std::strcmp(last_two_chars, "\r\n") == 0 ? size - 2 : size;
}

string error_to_string(int code)
{
	LPSTR buffer = NULL;
	DWORD flags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
	DWORD lang_id = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT);
	size_t size = FormatMessageA(flags, NULL, code, lang_id, (LPSTR)&buffer, 0, NULL);
	if (size == 0)
	{
		return "[failed to get error message]";
	}

	size = no_trailing_newline(buffer, size);
	std::string error_string(buffer, size);
	LocalFree(buffer);

	return error_string;
}

connection::connection(const char *endpoint)
	:
	descriptor(-1)
{
	SOCKET desc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (desc == INVALID_SOCKET)
	{
		trace_out_to_network_error() << "failed to open socket (" << error_to_string(WSAGetLastError()) << ')' << std::endl;
		return;
	}

	std::string error;
	std::pair<std::string, standard::uint16_t> host_port = host_port_from_string(endpoint, error);
	if (!error.empty())
	{
		trace_out_to_network_error() << error << std::endl;
		return;
	}

	hostent *host_entry = gethostbyname(host_port.first.c_str());
	if (host_entry == NULL)
	{
		trace_out_to_network_error() << "unrecognized host - '" << host_port.first << '\'' << std::endl;
		return;
	}

	sockaddr_in socket_address;
	socket_address.sin_family = AF_INET;
	std::memcpy(&(socket_address.sin_addr.s_addr), host_entry->h_addr, host_entry->h_length);
	socket_address.sin_port = htons(host_port.second);
	int retval = connect(desc, reinterpret_cast<sockaddr *>(&socket_address), sizeof(socket_address));
	if (retval == -1)
	{
		trace_out_to_network_error() << "failed to open socket (" << error_to_string(WSAGetLastError()) << ')' << std::endl;
		return;
	}

	socket_send = really_send;
	socket_close = really_close;
	descriptor = desc;
}

void really_send(untyped<> descriptor, const void *what, standard::size_t how_much)
{
	if (how_much == 0)
	{
		return;
	}

	int retval = send(_descriptor.get(), static_cast<const char *>(buffer), static_cast<int>(how_much), 0);
	if (retval == -1)
	{
		really_close(descriptor);
		trace_out_to_network_error() << "failed to send (" << error_to_string(WSAGetLastError()) << ')' << std::endl;
		return;
	}

	if (retval == 0)
	{
		really_close(descriptor);
		trace_out_to_network_error() << "socket disconnected" << std::endl;
	}

	return retval;
}

void really_close(int descriptor)
{
	socket_send = do_not_send;
	socket_close = do_not_close;
	shutdown(descriptor, SD_BOTH);
	closesocket(descriptor);
}

}

#endif

