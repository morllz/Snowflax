#include <Snowflax.h>


class SandboxApp : public Snowflax::Application {
public:
	SandboxApp() = default;
	~SandboxApp() override = default;
};

std::shared_ptr<Snowflax::Application> CreateApplication(int, char**) {
	return std::make_shared<SandboxApp>();
}
