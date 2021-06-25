// LeapYearParameterizedFixture.cpp
#include <gtest/gtest.h>

#include "LeapYearCalendar.h"

// gTest에서 지원하는 parameterized test class를 상속받는다.
class LeapYearParameterizedTestFixture :public ::testing::TestWithParam<int> {
protected:
    LeapYearCalendar leapYearCalendar;
};

// TEST_P라는 매크로로 INSTANTIATE_TEST_CASE_P에서 만든 파리미터 갯수간큼 테스트를 돈다.
TEST_P(LeapYearParameterizedTestFixture, OddYearsAreNotLeapYears) {
    int year = GetParam();
    // 실패시 굳이 다음 테스트를 돌 필요 없으므로 그냥 끝나도록 assert를 썼다.
    ASSERT_FALSE(leapYearCalendar.isLeap(year));
}

// 윤년이 아닌 파라미터 4개를 집어넣다.
INSTANTIATE_TEST_CASE_P(
    LeapYearTests,
    LeapYearParameterizedTestFixture,
    ::testing::Values(
        1, 711, 1989, 2015
    )
);
