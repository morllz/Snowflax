#pragma once

#include "Application.h"


extern std::shared_ptr<Snowflax::Application> CreateApplication(int _argc, char** _argv);

int main(int argc, char** argv) {
	auto app = CreateApplication(argc, argv);
	app->Run();
	app->Shutdown();
	return 0;
}