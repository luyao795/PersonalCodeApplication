#ifndef __CONSOLE_PRINT_H
#define __CONSOLE_PRINT_H

namespace Engine {

	namespace Azra
	{

		void ConsolePrint(const char * i_fmt, ...);

	} // Namespace Azra

	  // This is how we handle variable argument pre-processor macros
	  // This is only supported by compilers that support the C99 standard
#ifdef _DEBUG
#define DEBUG_PRINT(fmt,...) Azra::ConsolePrint((fmt),__VA_ARGS__)
#else
	  // This is one way we create a do nothing (NO OP) macro that doesn't
	  // generate a compiler warning or error
#define DEBUG_PRINT(fmt,...) void(0)
#endif

}

#endif // __CONSOLE_PRINT_H
