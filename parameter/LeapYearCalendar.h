// LeapYearCalendar.h
#ifndef PARAMETERIZEDTESTEXAMPLESCPP_LEAPYEARCALENDAR_H
#define PARAMETERIZEDTESTEXAMPLESCPP_LEAPYEARCALENDAR_H

// 역시 고객의 코드.  C로 하려면 mock에서 했던 것처럼 wrapper 클래스로 만들어서 해야 한다.
class LeapYearCalendar {
public:
    bool isLeap(int year);
    bool isDivisibleBy4(int year);
    bool isDivisibleBy100(int year);
    bool isDivisibleBy400(int year);
};

#endif //PARAMETERIZEDTESTEXAMPLESCPP_LEAPYEARCALENDAR_H