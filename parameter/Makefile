# Makefile
all: parameter

parameter: LeapYearCalendar.cpp LeapYearParameterizedFixture.cpp
	g++ -o LeapYearCalendar.o -c LeapYearCalendar.cpp -lgcov -fprofile-arcs -ftest-coverage 
	g++ -o LeapYearParameterizedFixture LeapYearCalendar.o LeapYearParameterizedFixture.cpp -lgcov -fprofile-arcs -ftest-coverage -lgtest -lgtest_main -lpthread
	./LeapYearParameterizedFixture
	gcov -b ./ mock_c_test.cpp
	lcov -c -d . -o mock_c_test.lcov --rc lcov_branch_coverage=1
	genhtml mock_c_test.lcov --rc lcov_branch_coverage=1 -o coverage

clean:
	rm -f *.o *.gcda *.gcno *.lcov coverage LeapYearParameterizedFixture