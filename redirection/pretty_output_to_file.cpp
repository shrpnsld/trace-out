//
// This file is a part of pretty_output project
// See more at https://github.com/shrpnsld/pretty_output
//

#include <fstream>


#define PRETTY_OUTPUT_TO_FILE__QUOTIZE_IMPL(something) \
			#something

#define PRETTY_OUTPUT_TO_FILE__QUOTIZE(something) \
			PRETTY_OUTPUT_TO_FILE__QUOTIZE_IMPL(something)


#if !defined(PRETTY_OUTPUT_TO_FILE)
	#define PRETTY_OUTPUT_TO_FILE pretty_output_log.txt
#endif


namespace pretty_output_to_file
{

	std::ofstream stream(PRETTY_OUTPUT_TO_FILE__QUOTIZE(PRETTY_OUTPUT_TO_FILE));


	void print(const char *string)
	{
		stream << string;
	}


	void flush()
	{
		stream.flush();
	}


	size_t width()
	{
#if defined(PRETTY_OUTPUT_WIDTH)

		return PRETTY_OUTPUT_WIDTH;

#else

		return 120;

#endif // defined(PRETTY_OUTPUT_WIDTH)
	}

}

