#define SFLX_ENABLE_LOGGING
#include <Snowflax.h>


class SandboxApp final : public Snowflax::Application {
public:
	SandboxApp() = default;
	~SandboxApp() override = default;

	virtual void OnEvent(Snowflax::Event& _event) override
	{
		SFLX_LOG_TRACE(_event.ToString());
		Application::OnEvent(_event);
	}
};

std::shared_ptr<Snowflax::Application> CreateApplication(int, char**) {
	return std::make_shared<SandboxApp>();
}
