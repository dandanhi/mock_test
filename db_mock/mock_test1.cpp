#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "./EventQueue.h"

using namespace std;
using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;
using ::testing::Invoke;


class MockEventDispatcher {
  MOCK_METHOD(bool, DispatchEvent, (int));
};

class MockEventQueue : public testing::Test {
public:
  EventQueue<int> q0_;
  EventQueue<int> q1_;
  EventQueue<int> q2_;
}

TEST(EventQueueTest, EnqueueEventTest) {
  MockEventDispatcher mock_event_dispatcher;
  EventQueue event_queue;

  const int kEventId = 321;
  absl::Notification done;
  EXPECT_CALL(mock_event_dispatcher, DispatchEvent(kEventId))
      .WillOnce([&done] { done.Notify(); });

  event_queue.Enqueue(kEventId);
  done.WaitForNotification();
}

int ThisShouldDie() {
  return 10/0;
}

TEST(MyDeathTest, TestOne) {
  testing::FLAGS_gtest_death_test_style = "threadsafe";
  // This test is run in the "threadsafe" style:
  ASSERT_DEATH(ThisShouldDie(), "");
}

TEST(MyDeathTest, TestTwo) {
  // This test is run in the "fast" style:
  testing::FLAGS_gtest_death_test_style = "threadsafe";  
  ASSERT_DEATH(ThisShouldDie(), "");

  // absl::Notification done;
  //done.WaitForNotification();
}