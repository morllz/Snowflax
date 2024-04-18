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


// Part of following SimpleEventHandling and SimpleEventDispatching test. Essential for execution. Simple function and class to work as dummies
void testDummyCallback(SimpleDummyTestEvent& _event) {
	_event.m_DummyData = false;
}
class testDummyCallbackClass {
public:
	void Callback(SimpleDummyTestEvent& _event)
	{
		testDummyCallback(_event);
	}
};
TEST(EventSystemTests, SimpleEventHandling) {
	// creating dummy event and event handler
	auto testEvent = SimpleDummyTestEvent();
	auto handler = EventHandler<SimpleDummyTestEvent>(testDummyCallback);

	handler.Handle(testEvent); 
	ASSERT_FALSE(testEvent.m_DummyData); // check if callback got called
}

TEST(EventSystemTests, SimpleEventDispatching) {
	auto testEvent = SimpleDummyTestEvent();
	auto dispatcher = EventDispatcher();
	dispatcher.Subscribe<SimpleDummyTestEvent>(testDummyCallback);

	dispatcher(testEvent);
	ASSERT_FALSE(testEvent.m_DummyData);
}
TEST(EventSystemTests, InObjectEventDispatching)
{
	auto testEvent = SimpleDummyTestEvent();
	auto dispatcher = EventDispatcher();
	auto obj = testDummyCallbackClass();

	dispatcher.Subscribe<SimpleDummyTestEvent, testDummyCallbackClass>(&testDummyCallbackClass::Callback, &obj);

	dispatcher(testEvent);
	ASSERT_FALSE(testEvent.m_DummyData);
}