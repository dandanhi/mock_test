// LeapYearCalendar.cpp
#include "LeapYearCalendar.h"

// 고객의 코드.  즉 테스트 대상 코드
bool LeapYearCalendar::isLeap(int year){
    // 윤년인지 아닌지 리턴한다.
    // 한 문장으로 되어 있지만 and와 or 조건이 있으므로 branch상로는 2*2의 branch이다.
    return isDivisibleBy4(year) and (!isDivisibleBy100(year) or isDivisibleBy400(year));
}

bool LeapYearCalendar::isDivisibleBy4(int year){
    return year % 4 == 0;
}

bool LeapYearCalendar::isDivisibleBy100(int year){
    return year % 100 == 0;
}

bool LeapYearCalendar::isDivisibleBy400(int year){
    return year % 400 == 0;
}