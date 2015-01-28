#include "pretty_output.h"


namespace pretty_output
{

	tls<std::string> _indentation;
	uint64_t _current_thread_id;
	tls<std::string> _thread_name;
	mutex _output_mutex;


	uint64_t current_thread_id()
	{
		return (uint64_t)pthread_self();
	}


	const std::string current_thread_name()
	{
		return _thread_name.get();
	}


	void set_current_thread_name(const std::string &name)
	{
		_thread_name.set(name);
	}


	bool is_running_same_thread()
	{
		if (_current_thread_id != current_thread_id())
		{
			_current_thread_id = current_thread_id();
			return false;
		}

		return true;
	}


	void lock_output()
	{
		_output_mutex.lock();
	}


	void unlock_output()
	{
		_output_mutex.unlock();
	}


	const std::string &indentation()
	{
		return _indentation.get();
	}


	void indentation_add()
	{
		_indentation.set(_indentation.get() + INDENTATION);
	}


	void indentation_remove()
	{
		const std::string &old_indentation = _indentation.get();
		_indentation.set(old_indentation.substr(0, old_indentation.length() - INDENTATION_SIZE));
	}

}

