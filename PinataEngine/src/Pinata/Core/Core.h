#pragma once

#ifdef PINATA_PLATFORM_WINDOW

	#ifdef PINATA_BUILD_DLL
		#define PINATA_API __declspec(dllexport)
	#else
		#define PINATA_API __declspec(dllimport)

	#endif // PINATA_BUILD_DLL

#else
#error Pinata only support windows

#endif // PINATA_PLATFORM_WINDOW


#define BIT(x)  (1 << x)
