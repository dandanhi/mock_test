# Makefile
all: type

type: TypeTest.cpp
	g++ -o TypeTest TypeTest.cpp -lgcov -fprofile-arcs -ftest-coverage -lgtest -lgtest_main -lpthread
	./TypeTest
	gcov -b ./ mock_c_test.cpp
	lcov -c -d . -o mock_c_test.lcov --rc lcov_branch_coverage=1
	genhtml mock_c_test.lcov --rc lcov_branch_coverage=1 -o coverage

clean:
	rm -rf *.o *.gcda *.gcno *.lcov coverage TypeTest