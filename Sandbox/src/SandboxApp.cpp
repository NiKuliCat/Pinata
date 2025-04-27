#include <Pinata.h>
#include "imgui.h"
#include "TestLayer.h"

class Sandbox : public Pinata::Application
{
public:
	Sandbox()
	{
		PushLayer(new TestLayer());
	}
	~Sandbox()
	{

	}
};

Pinata::Application* Pinata::CreateApplication()
{
	return new Sandbox();
}