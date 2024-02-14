#pragma once

#include "trace-out/integer.hpp"
#include "trace-out/platform-detection.hpp"
#include "trace-out/resource.hpp"
#include "trace-out/untyped.hpp"
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <streambuf>
#include <string>
#include <utility>

#if defined(TRACE_OUT_STREAM_TO_ENDPOINT)

//
// Public

namespace trace_out_stream_to_endpoint
{

inline std::ostream &stream();

}

//
// Private

namespace trace_out
{

class socket_stream_buf
	:
	public std::basic_streambuf<char>
{
public:
	inline socket_stream_buf(const char *endpoint);
	inline ~socket_stream_buf();

	inline virtual std::streamsize xsputn(const char_type *what, std::streamsize how_much);
	inline virtual int_type overflow(int_type ch);

private:
	untyped<> _descriptor;
};

inline socket_stream_buf &socket_stream_buf_instance();

std::ostream &trace_out_to_endpoint_error();

bool is_valid_port_string(const char *string);
std::pair<std::string, std::string> host_port_from_string(const char *string, std::string &error);

inline void really_send(untyped<> descriptor, const void *what, standard::size_t how_much);
inline void do_not_send(untyped<> descriptor, const void *what, standard::size_t how_much);
void (*socket_send)(untyped<> descriptor, const void *what, standard::size_t how_much) = do_not_send;

inline void really_close(untyped<> descriptor);
inline void do_not_close(untyped<> descriptor);
void (*socket_close)(untyped<> descriptor) = do_not_close;

}

//
// Implementation

namespace trace_out_stream_to_endpoint
{

std::ostream &stream()
{
	static std::ostream _stream(&trace_out::socket_stream_buf_instance());

	return _stream;
}

}

namespace trace_out
{

socket_stream_buf &socket_stream_buf_instance()
{
	static socket_stream_buf _buffer(TRACE_OUT_STREAM_TO_ENDPOINT);

	return _buffer;
}

std::streamsize socket_stream_buf::xsputn(const char_type *what, std::streamsize how_much)
{
	socket_send(_descriptor, what, how_much);
	return how_much;
}

socket_stream_buf::int_type socket_stream_buf::overflow(int_type ch)
{
	socket_send(_descriptor, &ch, 1);
	return traits_type::not_eof(ch);
}

std::ostream &trace_out_to_endpoint_error()
{
	return std::cerr << "trace-out-to-network-error: ";
}

bool is_valid_port_string(const char *string)
{
	for ( ; std::isdigit(*string); ++string);

	return *string == '\0';
}

std::pair<std::string, std::string> host_port_from_string(const char *string, std::string &error)
{
	const char *delimiter = std::strchr(string, ':');
	if (delimiter == NULL || delimiter == string)
	{
		error = "host is not specified";
		return std::pair<std::string, std::string>();
	}

	std::string host(string, delimiter);

	const char *port_string = delimiter + 1;
	if (*port_string == '\0')
	{
		error = "port is not specified";
		return std::pair<std::string, std::string>();
	}

	if (!is_valid_port_string(port_string))
	{
		error = error + "port is not a number - '" + port_string + '\'';
		return std::pair<std::string, std::string>();
	}

	std::string port(delimiter + 1);

	error = "";
	return std::make_pair(host, port);
}

void do_not_send(untyped<>, const void *, standard::size_t)
{
}

void do_not_close(untyped<>)
{
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

resource<addrinfo *> get_addresses(const char *host, const char *port, std::string &error);
untyped<> open_socket_and_connect(const addrinfo *addresses, std::string &error);

}

namespace trace_out
{

resource<addrinfo *> get_addresses(const char *host, const char *port, std::string &error)
{
	addrinfo hints;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = 0;

	addrinfo *addresses;

	int retval = getaddrinfo(host, port, &hints, &addresses);
	if (retval != 0)
	{
		error = error + "failed to recognize host and/or port '" + host + ':' + port + "' (" + gai_strerror(retval) + ')';
		return resource<addrinfo *>(NULL, NULL);
	}

	return resource<addrinfo *>(addresses, freeaddrinfo);
}

untyped<> open_socket_and_connect(const addrinfo *addresses, std::string &error)
{
	untyped<> descriptor;
	for (const addrinfo *address = addresses; address != NULL; address = address->ai_next)
	{
		descriptor = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
		if (descriptor == -1)
		{
			if (address->ai_next == NULL)
			{
				error = error + "failed to open socket (" + strerror(errno) + ')';
				return -1;
			}

			continue;
		}

		int retval = connect(descriptor, address->ai_addr, address->ai_addrlen);
		if (retval == -1)
		{
			close(descriptor);

			if (address->ai_next == NULL)
			{
				error = error + "failed to connect (" + strerror(errno) + ')';
				return -1;
			}

			continue;
		}

		break;
	}

	return descriptor;
}

socket_stream_buf::socket_stream_buf(const char *endpoint)
	:
	_descriptor(-1)
{
	std::string error;
	std::pair<std::string, std::string> host_port = host_port_from_string(endpoint, error);
	if (!error.empty())
	{
		trace_out_to_endpoint_error() << error << std::endl;
		return;
	}

	resource<addrinfo *> addresses(get_addresses(host_port.first.c_str(), host_port.second.c_str(), error), MOVE_RESOURCE);
	if (addresses.get() == NULL)
	{
		trace_out_to_endpoint_error() << error << std::endl;
		return;
	}

	untyped<> descriptor = open_socket_and_connect(addresses.get(), error);
	if (descriptor == -1)
	{
		trace_out_to_endpoint_error() << error << std::endl;
		return;
	}

	socket_send = really_send;
	socket_close = really_close;
	_descriptor = descriptor;
}

socket_stream_buf::~socket_stream_buf()
{
	socket_close(_descriptor);
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
		trace_out_to_endpoint_error() << "failed to send (" << strerror(errno) << ')' << std::endl;
		return;
	}

	if (retval == 0)
	{
		really_close(descriptor);
		trace_out_to_endpoint_error() << "socket disconnected" << std::endl;
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

#include "trace-out/windows-headers.hpp"

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

std::string error_to_string(int code)
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

socket_stream_buf::socket_stream_buf(const char *endpoint)
	:
	_descriptor(-1)
{
	WSADATA wsa_data;
	int retval = WSAStartup(MAKEWORD(2, 0), &wsa_data);
	if (retval != 0)
	{
		trace_out_to_endpoint_error() << "failed to initialize Windows Sockets libray (" << error_to_string(WSAGetLastError()) << ')' << std::endl;
		return;
	}

	SOCKET descriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (descriptor == INVALID_SOCKET)
	{
		trace_out_to_endpoint_error() << "failed to open socket (" << error_to_string(WSAGetLastError()) << ')' << std::endl;
		return;
	}

	std::string error;
	std::pair<std::string, standard::uint16_t> host_port = host_port_from_string(endpoint, error);
	if (!error.empty())
	{
		trace_out_to_endpoint_error() << error << std::endl;
		return;
	}

	hostent *host_entry = gethostbyname(host_port.first.c_str());
	if (host_entry == NULL)
	{
		trace_out_to_endpoint_error() << "unrecognized host - '" << host_port.first << '\'' << std::endl;
		return;
	}

	sockaddr_in socket_address;
	socket_address.sin_family = AF_INET;
	std::memcpy(&(socket_address.sin_addr.s_addr), host_entry->h_addr, host_entry->h_length);
	socket_address.sin_port = htons(host_port.second);
	retval = connect(descriptor, reinterpret_cast<sockaddr *>(&socket_address), sizeof(socket_address));
	if (retval == -1)
	{
		trace_out_to_endpoint_error() << "failed to open socket (" << error_to_string(WSAGetLastError()) << ')' << std::endl;
		return;
	}

	socket_send = really_send;
	socket_close = really_close;
	_descriptor = descriptor;
}

socket_stream_buf::~socket_stream_buf()
{
	socket_close(_descriptor);
	WSACleanup();
}

void really_send(untyped<> descriptor, const void *what, standard::size_t how_much)
{
	if (how_much == 0)
	{
		return;
	}

	int retval = send(descriptor, static_cast<const char *>(what), static_cast<int>(how_much), 0);
	if (retval == -1)
	{
		really_close(descriptor);
		trace_out_to_endpoint_error() << "failed to send (" << error_to_string(WSAGetLastError()) << ')' << std::endl;
		return;
	}

	if (retval == 0)
	{
		really_close(descriptor);
		trace_out_to_endpoint_error() << "socket disconnected" << std::endl;
	}

	return retval;
}

void really_close(untyped<> descriptor)
{
	socket_send = do_not_send;
	socket_close = do_not_close;
	shutdown(descriptor, SD_BOTH);
	closesocket(descriptor);
}

}

#endif

#endif // defined(TRACE_OUT_STREAM_TO_ENDPOINT)

