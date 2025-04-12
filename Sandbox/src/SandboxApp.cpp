#include <Pinata.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}

class TestLayer : public Pinata::Layer
{

public:
	TestLayer()
		:Layer("TestLayer")
	{
		auto cam = camera(0.5f, { 0.5f,0.5f });
	}

	void OnUpdata() override
	{
		if (Pinata::Input::IsKeyPressed(Pinata::Key::Space))
		{
			PTA_INFO("Space is pressed !");
		}
		//PTA_INFO("TestLayer::Updata");
	}
	void OnEvent(Pinata::Event& event) override
	{
		//PTA_TRACE("{0}", event.ToString());
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