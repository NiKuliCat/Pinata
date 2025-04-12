#include <Pinata.h>

class Sandbox : public Pinata::Application
{
public:
	Sandbox()
	{
	}
	~Sandbox()
	{

	}
};

Pinata::Application* Pinata::CreateApplication()
{
	return new Sandbox();
}