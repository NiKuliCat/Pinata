#pragma once

#ifdef PINATA_PLATFORM_WINDOW

extern Pinata::Application* Pinata::CreateApplication();

int main(int argc, char** argv)
{
	Pinata::Log::Init();
	PTA_CORE_INFO(" Core Log system Init");
	PTA_CORE_ERROR(" Client Log system Init");
	printf("Pinata Engine");
	auto app = Pinata::CreateApplication();
	app->Run();
	delete app;
}


#endif
