#pragma once

#include <gtest/gtest.h>
#include "Snowflax/Infrastructure/IoC/Container.h"


using namespace Snowflax::Infrastructure;

TEST(IoCInfrastructureTest, GetContainerInstance) {
	ASSERT_EQ(typeid(Container::Get()), typeid(Container&));
}
TEST(IoCInfrastructureTest, RegisterAndResolveNotParametrizesGenerator) {
	Container::Get().RegisterFactory<int> ([]() { return std::make_shared<int>(); });
	auto pInt = Container::Get().Resolve<int>();
	ASSERT_EQ(typeid(pInt), typeid(std::make_shared<int>()));
}