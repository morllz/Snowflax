#pragma once

#include "Application.h"


extern std::shared_ptr<Snowflax::Application> CreateApplication(int, char**);

int main(const int _argc, char** _argv) {
	const auto app = CreateApplication(_argc, _argv);
	app->Run();
	app->Shutdown();
	return 0;
}