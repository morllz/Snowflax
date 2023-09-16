#pragma once

#include "Application.h"


#ifdef SFX_PLATFORM_WINDOWS

extern Snowflax::Application* CreateApplication();

int main(int argc, char** argv) {
	auto app = CreateApplication();
	app->Run();
	app->Shutdown();
	delete app;
	return 0;
}

#endif //SFX_PLATFORM_WINDOWS