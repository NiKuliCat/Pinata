#pragma once
#include "Core.h"
namespace Pinata {

	class PINATA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};


	//to be defined in CLENT
	Application* CreateApplication();
}

