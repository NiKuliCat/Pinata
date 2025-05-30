#pragma once
#include <memory>
#ifdef PINATA_PLATFORM_WINDOW

#ifdef PINATA_DYNAMIC_LINK

	#ifdef PINATA_BUILD_DLL
		#define PINATA_API __declspec(dllexport)
	#else
		#define PINATA_API __declspec(dllimport)

	#endif // PINATA_BUILD_DLL
#else 

	#define PINATA_API 

#endif // PINATA_DYNAMIC_LINK


#else
#error Pinata only support windows

#endif // PINATA_PLATFORM_WINDOW

#ifdef PINATA_ENABLE_ASSERTS
	#define PTA_ASSERT(x,...) { if(!x){PTA_ERROR("Assert Failed : {0}",__VA_ARGS__); __debugbreak();}}
	#define PTA_CORE_ASSERT(x,...) { if(!x){PTA_CORE_ERROR("Assert Failed : {0}",__VA_ARGS__); __debugbreak();}}
#else
	#define PTA_ASSERT(x, ...)
	#define PTA_CORE_ASSERT(x,...)
#endif


#define BIT(x)  (1 << x)
//#define BIND_EVENT_FUNC(fn) std::bind(&fn, this, std::placeholders::_1)
#define BIND_EVENT_FUNC(fn) [this](auto&&... args) ->decltype(auto)  {return this->fn(std::forward<decltype(args)>(args)...);}


namespace Pinata {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T ,typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}
