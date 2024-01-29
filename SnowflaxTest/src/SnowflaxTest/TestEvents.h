#pragma once

#include <Snowflax.h>
#include <gtest/gtest.h>

using namespace Snowflax::Infrastructure::Events;

EVENT(SimpleTestEvent, None, None) {
public:
	SimpleTestEvent() {
		m_Created = true;
	}
	~SimpleTestEvent() {

	}
private:
	bool m_Created = false;
}

TEST(EventSystemTests, SimpleEventIdentification) {

}