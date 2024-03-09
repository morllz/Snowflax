#include <Snowflax.h>


class SandboxApp : public Snowflax::Application {
public:
	SandboxApp() = default;
	~SandboxApp() = default;

	void Run() {};
	void Shutdown() {};
};

Snowflax::Application* CreateApplication(int _argc, char** _argv) {
	return new SandboxApp();
}