#pragma once

#include <Snowflax.h>
#include <gtest/gtest.h>


using namespace Snowflax;

EVENT(SimpleDummyTestEvent, DummyEvent) {
public:
	SimpleDummyTestEvent() : m_DummyData(true) {
		
	}
	~SimpleDummyTestEvent() override = default;
	bool m_DummyData = false;
};

TEST(EventSystemTests, SimpleEventIdentification) {
	SimpleDummyTestEvent event; // creating dummy test event

	ASSERT_TRUE(event.m_DummyData); // test correct creation

	ASSERT_EQ(event.GetEventType(), EventType::DummyEvent); // test correct event type
}


// Part of following SimpleEventHandling and SimpleEventDispatching test. Essential for execution. Simple function and class to work as dummies
bool testDummyCallback(SimpleDummyTestEvent& _event) {
	_event.m_DummyData = false;
	return true;
}
class testDummyCallbackClass {
public:
	bool Callback(SimpleDummyTestEvent& _event) const
	{
		testDummyCallback(_event);
		return false;
	}
};
TEST(EventSystemTests, SimpleEventHandling) {
	// creating dummy event and event handler
	SimpleDummyTestEvent event;
	auto handler = EventHandler<SimpleDummyTestEvent>(testDummyCallback);

	handler.Handle(event); 
	ASSERT_FALSE(event.m_DummyData); // check if callback got called
}

TEST(EventSystemTests, SimpleEventDispatching) {
	SimpleDummyTestEvent event;
	auto dispatcher = EventDispatcher();
	dispatcher.Subscribe<SimpleDummyTestEvent>(testDummyCallback);

	dispatcher.Send(event);
	ASSERT_FALSE(event.m_DummyData);
}
TEST(EventSystemTests, ToMemberFuncEventDispatching)
{
	SimpleDummyTestEvent event;
	auto dispatcher = EventDispatcher();
	auto obj = testDummyCallbackClass();

	dispatcher.Subscribe<SimpleDummyTestEvent>(&testDummyCallbackClass::Callback, &obj);

	dispatcher.Send(event);
	ASSERT_FALSE(event.m_DummyData);
}