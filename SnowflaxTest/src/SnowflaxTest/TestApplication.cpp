#include "AllTests.h"
#include <gtest/gtest.h>


class SnowflaxTestApplication : public Snowflax::Application {
public:
    SnowflaxTestApplication(int _argc, char** _argv) : m_argc(_argc), m_argv(_argv) {};
    ~SnowflaxTestApplication() override = default;

    void Run()  {
        ::testing::InitGoogleTest(&m_argc, m_argv);

        RUN_ALL_TESTS();
    }
    void Shutdown() {}
    void OnEvent(Snowflax::Event&) {}
private:
    int m_argc;
    char** m_argv;
};

std::shared_ptr<Snowflax::Application> CreateApplication(int _argc, char** _argv) {
    return std::make_shared<SnowflaxTestApplication>(_argc, _argv);
}