#include <Pinata.h>



class TestLayer : public Pinata::Layer
{

public:
	TestLayer()
		:Layer("TestLayer")
	{

	}

	void OnUpdata() override
	{
		PTA_INFO("TestLayer::Updata");
	}
	void OnEvent(Pinata::Event& event) override
	{
		PTA_TRACE("{0}", event.ToString());
	}


};
class Sandbox : public Pinata::Application
{
public:
	Sandbox()
	{
		PushLayer(new TestLayer());
		PushLayer(new Pinata::ImGuiLayer());
	}
	~Sandbox()
	{

	}
};

Pinata::Application* Pinata::CreateApplication()
{
	return new Sandbox();
}