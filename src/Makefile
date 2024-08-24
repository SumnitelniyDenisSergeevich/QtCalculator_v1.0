CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -std=c11
LDFLAGS=-O2 -Wall -Wextra -Werror -std=c11
SOURCE=$(wildcard backend/s21_*.c)
SOURCE_CALCULATOR=backend/s21_credit_calculator.c backend/s21_deposit_calculator.c backend/s21_notation_calculator.c
SOURCE_STACK=backend/s21_stack.c
SOURCE_LIST=backend/s21_list.c
OBJECTS=s21_credit_calculator.o s21_deposit_calculator.o s21_notation_calculator.o
UNAME:=$(shell uname -s) # определяем ОС
ifeq ($(UNAME),Linux ) # Linux
	OPEN_CMD=xdg-open # команда для открытия отчета
	ADD_LIB=-lm -lrt -lpthread -lsubunit # дополнительные библиотеки
	BREW=/home/darkwolf/homebrew
endif
ifeq ($(UNAME),Darwin ) # MacOS
	OPEN_CMD=open
	ADD_LIB= 
	BREW=${HOME}/homebrew
endif
PATH := $(PATH):$(BREW)/bin # пути поиска lcov и genhtml
GCOV=--coverage
PROJECTNAME=s21_calculator
STACK=s21_stack
LIST=s21_list
TESTC=backend/check_s21_calculator.c

all: clean install gcov_report

$(STACK).a: $(SOURCE_STACK)
	${CC} $(CFLAGS) ${ADD_LIB} $(SOURCE_STACK)
	ar rc $(STACK).a $(STACK).o
	ranlib $(STACK).a
	@make clean_objects

$(LIST).a: $(SOURCE_LIST)
	${CC} $(CFLAGS) ${ADD_LIB} $(SOURCE_LIST)
	ar rc $(LIST).a $(LIST).o
	ranlib $(LIST).a
	@make clean_objects


$(PROJECTNAME).a: ${SOURCE_CALCULATOR}
	${CC} $(CFLAGS) ${ADD_LIB} $^
	ar rc $(PROJECTNAME).a ${OBJECTS}
	ranlib $(PROJECTNAME).a
	@make clean_objects

test: clean $(TESTC) $(PROJECTNAME).a $(STACK).a $(LIST).a
	${CC} ${LDFLAGS} -o $@ $(TESTC) $(PROJECTNAME).a $(STACK).a $(LIST).a -lcheck ${ADD_LIB}
	./$@
	-rm -rf *.a

gcov_report: clean ${SOURCE} $(TESTC)
	-mkdir report
	${CC} ${LDFLAGS} -o $@ ${GCOV} $(TESTC) ${SOURCE} -lcheck ${ADD_LIB}
	-./$@
	--gcov $(TESTC)
	if [ "$(UNAME)","Linux " ]; then \
        lcov -t ${PROJECTNAME} -o ${PROJECTNAME}.info -c -d .;\
		genhtml -o report ${PROJECTNAME}.info;\
    else \
        $(shell PATH=$(PATH) which lcov)  -t ${PROJECTNAME} -o ${PROJECTNAME}.info -c -d .;\
		$(shell PATH=$(PATH) which genhtml) -o report ${PROJECTNAME}.info;\
    fi
	-rm -rf *.gcda && rm -rf *.gcno 
	-rm -rf *.info && rm -rf ./gcov_report
	-$(OPEN_CMD) ./report/index.html

rebuild: clean all

foo.dvi: manual.texi
	makeinfo manual.texi --html

dvi: foo.dvi
	-$(OPEN_CMD) manual/index.html


dist: install foo.dvi
	-mkdir dist
	cp -r build/Calc.app dist/Calc.app
	cp manual/index.html dist/manual.html
	tar -czvf dist.tar.gz dist
	rm -rf dist
	rm -rf manual
	rm -rf build

install: clean $(STACK).a $(LIST).a $(PROJECTNAME).a
	rm -rf build
	mkdir build
	cd build && cmake .. && cmake --build .
	-rm -rf *.a

uninstall:
	rm -rf build

clean:
	-rm -rf *.o && rm -rf *.a 
	-rm -rf *.gcov && rm -rf ./test 
	-rm -rf report && rm -rf build 
	-rm -rf ./gcov_report && rm -rf *.gz
	-rm -rf dist && rm -rf manual
	-rm -rf *.gcda && rm -rf *.gcno 
	-rm -rf *.info

valgrind: test
	valgrind --tool=memcheck --leak-check=yes -s ./test

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i backend/*.c backend/*.h
	rm .clang-format	

clang_err:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n backend/*.c backend/*.h
	rm .clang-format	

clean_objects:
	-rm -rf *.o

.PHONY: all clean