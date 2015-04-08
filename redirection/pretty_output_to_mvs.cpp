//
// This file is a part of pretty_output project
// See more at https://github.com/shrpnsld/pretty_output
//

#include <windows.h>


namespace pretty_output_to_mvs
{

	void print(const char *string)
	{
		OutputDebugStringA(string);
	}


	void flush()
	{
	}

}

