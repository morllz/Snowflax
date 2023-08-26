#include <Snowflax.h>


class SandboxApp : public Snowflax::Application {
public:
	SandboxApp() {

	}
	~SandboxApp() {

	}

};

Snowflax::Application* CreateApplication() {
	return new SandboxApp();
}