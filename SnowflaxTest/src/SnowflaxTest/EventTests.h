#pragma once

#include <Snowflax.h>
#include <gtest/gtest.h>

using namespace Snowflax::Infrastructure::Events;

EVENT(SimpleTestEvent, TestEvent, None) {
public:
	SimpleTestEvent() {
		m_Created = true;
	}
	~SimpleTestEvent() {

	}
	bool m_Created = false;
};

TEST(EventSystemTests, SimpleEventIdentification) {
	SimpleTestEvent testEvent = SimpleTestEvent();
	ASSERT_TRUE(testEvent.m_Created);
	ASSERT_EQ(testEvent.GetEventType(), EventType::TestEvent);
	ASSERT_TRUE(testEvent.InCategory(None));
}


// Part of following SimpleEventHandling test. Essential for execution
void changeCreated(SimpleTestEvent& _event) {
	_event.m_Created = false;
}
TEST(EventSystemTests, SimpleEventHandling) {
	SimpleTestEvent testEvent = SimpleTestEvent();
	EventHandler<SimpleTestEvent> handler = EventHandler<SimpleTestEvent>();
	ASSERT_TRUE(testEvent.m_Created);
	handler += changeCreated;
	handler.Handle(testEvent);
	ASSERT_FALSE(testEvent.m_Created);
	testEvent.m_Created = true;
	handler -= changeCreated;
	handler.Handle(testEvent);
	ASSERT_TRUE(testEvent.m_Created);


}

