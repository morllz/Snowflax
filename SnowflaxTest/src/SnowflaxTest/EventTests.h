#pragma once

#include <Snowflax.h>
#include <gtest/gtest.h>


using namespace Snowflax;

EVENT(SimpleDummyTestEvent, DummyEvent, None) {
public:
	SimpleDummyTestEvent() : m_DummyData(true) {
		
	}
	~SimpleDummyTestEvent() override = default;
	bool m_DummyData = false;
};

TEST(EventSystemTests, SimpleEventIdentification) {
	auto testEvent = SimpleDummyTestEvent(); // creating dummy test event

	ASSERT_TRUE(testEvent.m_DummyData); // test correct creation

	ASSERT_EQ(testEvent.GetEventType(), EventType::DummyEvent); // test correct event type
	ASSERT_TRUE(testEvent.InCategory(EventCategory::None)); // test correct event category
}


// Part of following SimpleEventHandling and SimpleEventDispatching test. Essential for execution. Simple function to work as dummy callback
void testDummyCallback(SimpleDummyTestEvent& _event) {
	_event.m_DummyData = false;
}
TEST(EventSystemTests, SimpleEventHandling) {
	// creating dummy event and event handler
	auto testEvent = SimpleDummyTestEvent();
	auto handler = EventHandler<SimpleDummyTestEvent>();

	handler += testDummyCallback; // subscribe dummy callback

	handler.Handle(testEvent); 
	ASSERT_FALSE(testEvent.m_DummyData); // check if callback got called

	// check for working unsubscribing
	testEvent.m_DummyData = true;
	handler -= testDummyCallback;
	handler.Handle(testEvent);
	ASSERT_TRUE(testEvent.m_DummyData);


}

TEST(EventSystemTests, SimpleEventDispatching) {
	// creating dummy event and event handler
	auto testEvent = SimpleDummyTestEvent();
	auto handler = EventHandler<SimpleDummyTestEvent>();
	auto dispatcher = EventDispatcher();
	dispatcher += handler;

	handler += testDummyCallback; // subcribe dummy callback

	dispatcher.Dispatch(testEvent);
	ASSERT_FALSE(testEvent.m_DummyData); // check if callback got called

	// check for working unsubscribing
	testEvent.m_DummyData = true;
	dispatcher -= handler;
	dispatcher.Dispatch(testEvent);
	ASSERT_TRUE(testEvent.m_DummyData);
}

