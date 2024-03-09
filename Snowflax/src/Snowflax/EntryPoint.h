#pragma once

#include "Application.h"


#ifdef SFX_PLATFORM_WINDOWS

extern Snowflax::Application* CreateApplication(int _argc, char** _argv);

int main(int argc, char** argv) {
	auto app = CreateApplication(argc, argv);
	app->Run();
	app->Shutdown();
	delete app;
	return 0;
}

#endif //SFX_PLATFORM_WINDOWS