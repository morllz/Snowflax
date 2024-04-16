#include "AllTests.h"
#include <gtest/gtest.h>

namespace  SnowflaxTest
{
	class Application final : public Snowflax::Application {
	public:
		Application(const int _argc, char** _argv) : m_Argc(_argc), m_Argv(_argv) {}
		Application() = default;

		void Run() override {
			::testing::InitGoogleTest(&m_Argc, m_Argv);

			RUN_ALL_TESTS();
		}
		void Shutdown() override {}
		void OnEvent(Snowflax::Event&) override {}
	private:
		int m_Argc;
		char** m_Argv;
	};

}

std::shared_ptr<Snowflax::Application> CreateApplication(int _argc, char** _argv) {
	return std::make_shared<SnowflaxTest::Application>(_argc, _argv);
}