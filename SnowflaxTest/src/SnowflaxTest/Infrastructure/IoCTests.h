#pragma once

#include <gtest/gtest.h>
#include <Snowflax/Infrastructure/IoC/Container.h>

TEST(IoCInfrastructureTest, GetContainerInstance) {
	ASSERT_EQ(typeid(Snowflax::Infrastructure::Container::Get()), typeid(Snowflax::Infrastructure::Container&));
}