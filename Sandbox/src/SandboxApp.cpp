#include <Pinata.h>

#include "imgui.h"
class TestLayer : public Pinata::Layer
{
	void OnImGuiRender()
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello world");
		ImGui::End();
	}
};

#include "imgui.h"
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