CC=g++
CPP=-std=c++17 -lstdc++
EXTRAS=-lm
OS=$(shell uname)
ifeq ($(OS), Linux)
	LEAKS = valgrind --leak-check=full --track-origins=yes -s ./test --gtest_filter="-*THROW*"
	GCOVFLAGS = --coverage
	GTEST=`pkg-config --cflags --libs gtest`
else
	LEAKS = leaks --atExit -- ./test --gtest_filter="-*THROW*"
	GCOVFLAGS = -fprofile-arcs -ftest-coverage
	GTEST=-lm -lgtest
endif

# Checks if compiler is not clang since max_size() is deprecated on clang but not gcc
# and will prevent the program from compiling (By default MacOS uses gcc as an alias to clang)
ifneq ($(CXX), c++)
	COMPILE_KILL=-Wall -Wextra -Werror
endif

# This works on linux & on regular mac but may fail on campus macs due to
# their unique configuration
# GTEST=`pkg-config --cflags --libs gtest`
# Try uncommenting this if pkg-config fails
# GTEST=-lm -lgtest

all: clean test codestyle 

test: clean
	$(CC) test.cc $(CPP) $(GTEST) $(EXTRAS) -o test $(COMPILE_KILL)
	./test

gcov_report: clean
	$(CC) $(GCOVFLAGS) test.cc $(CPP) $(GTEST) $(EXTRAS) -o test $(COMPILE_KILL)
	./test
	gcov test_gcov
	lcov -t "s21_containers" --no-external -o s21_constainers.info -c -d .
	genhtml -o report s21_constainers.info
	open ./report/index.html
	rm -rf *.o test *.gcda *.gcno *.info

codestyle:
	cp ../materials/linters/.clang-format .
	clang-format -i *.cc *.h
	clang-format -n *.cc *.h
	rm -rf .clang-format
	
check: test
	cppcheck --enable=all --suppress=missingIncludeSystem --std=c++17 --language=c++ *.cc *.h
	$(LEAKS)

clean:
	rm -rf *.0 *.a *.gcno *.gcda *.info *.out report *.dSYM *.gch *.o test2.out .vscode .DS_Store *.gcov test_cov test
