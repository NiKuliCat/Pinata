#pragma once

#ifdef PINATA_PLATFORM_WINDOW

extern Pinata::Application* Pinata::CreateApplication();

int main(int argc, char** argv)
{
	printf("Pinata Engine");
	auto app = Pinata::CreateApplication();
	app->Run();
	delete app;
}


#endif
