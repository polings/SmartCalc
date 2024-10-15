CC=g++
CFLAGS=-Wall -Werror -Wextra -std=c++17

all: clean style test gcov_report install

cmake: 
	mkdir -p build && cd build && cmake ..

install: uninstall cmake
	cd build && make
	cd build && open view.app

uninstall: clean
	rm -rf build

test: clean
	$(CC) $(CFLAGS) --coverage tests/*.cc model/*.cc model/expressioncalculator/*.cc model/expressioncalculator/stringparser/*.cc model/expressioncalculator/rpncalculation/*.cc model/expressioncalculator/convertertorpn/*.cc model/creditcalculator/credit_calculator.cc -lgtest -lgtest_main -lpthread -o test
	./test

gcov_report: test
	@lcov -t test -o s21_SmartCalc.info -c -d . --ignore-errors mismatch,inconsistent
	@lcov -e s21_SmartCalc.info '*/src/model/expressioncalculator/*.cc' -o s21_SmartCalc.info --ignore-errors mismatch,inconsistent
	@genhtml -o gcov_report s21_SmartCalc.info --ignore-errors mismatch,inconsistent
	@open ./gcov_report/index.html

clean:
	@rm -rf test *.gcda *.gcno *.info gcov_report

style:
	@clang-format -style=Google -n *.cc controller/* view/*.cc view/*.h
	@clang-format -style=Google -n model/*.cc model/*.h model/expressioncalculator/*.cc model/expressioncalculator/*.h model/expressioncalculator/common/* model/expressioncalculator/convertertorpn/* model/expressioncalculator/rpncalculation/* model/expressioncalculator/stringparser/*
	@clang-format -style=Google -n model/creditcalculator/*
	@clang-format -style=Google -n tests/*.cc

clang:
	@clang-format -style=Google -i *.cc controller/* view/*.cc view/*.h
	@clang-format -style=Google -i model/*.cc model/*.h model/expressioncalculator/*.cc model/expressioncalculator/*.h model/expressioncalculator/common/* model/expressioncalculator/convertertorpn/* model/expressioncalculator/rpncalculation/* model/expressioncalculator/stringparser/*
	@clang-format -style=Google -i model/creditcalculator/*
	@clang-format -style=Google -i tests/*.cc

valgrind:
	@CK_FORK=no valgrind --leak-check=full --tool=memcheck --leak-check=yes make test

install_brew:
	@cd ~
	@curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

install_lcov:
	@brew install lcov
