#include "Application.h"
#include "Log.h"
#include "Pinata/Event/ApplicationEvent.h"
namespace Pinata {

	void Application::Run()
	{
		WindowResizeEvent e(800, 600);
		PTA_CORE_TRACE(e.ToString());
		while (true);
	}
	Application::Application()
	{
	}
	Application::~Application()
	{
	}
}
