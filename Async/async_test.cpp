#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "EventDispatcher.h"

//CAUTION! should use abseil contained gTest library
class MockEventDispatcher : public EventDispatcher {
  MOCK_METHOD(bool, DispatchEvent, (int), (override));
};

TEST(EventQueueTest, EnqueueEventTest) {
  MockEventDispatcher mock_event_dispatcher;
  EventQueue event_queue(&mock_event_dispatcher);

  const int kEventId = 321;
  absl::Notification done;
  EXPECT_CALL(mock_event_dispatcher, DispatchEvent(kEventId))
      .WillOnce([&done] { done.Notify(); });

  event_queue.EnqueueEvent(kEventId);
  done.WaitForNotification();
}