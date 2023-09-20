#include "trace-out/stuff/stuff.hpp"


namespace trace_out { namespace detail
{

	std::string first_token(const std::string &tokens)
	{
		return tokens.substr(0, tokens.find(','));
	}


	std::string rest_tokens(const std::string &tokens)
	{
		standard::size_t from = tokens.find(',') + 1;
		while (tokens[from] == ' ')
		{
			++from;
		}

		return tokens.substr(from, tokens.size());
	}

}
}

