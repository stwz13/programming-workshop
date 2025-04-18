clean:
	rm -rf *.o *.a *_test
check_format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror
format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`
solving_the_quadratic_equation.o: solving_the_quadratic_equation.c solving_the_quadratic_equation.h
	gcc -g -c solving_the_quadratic_equation.c -o solving_the_quadratic_equation.o 
solving_the_quadratic_equation.a: solving_the_quadratic_equation.o
	ar rc solving_the_quadratic_equation.a solving_the_quadratic_equation.o 
main.o: main.c
	gcc -g -c main.c -o main.o -lm
bin: main.o solving_the_quadratic_equation.a
	gcc -g -static -o solving_the_quadratic_equation_test main.o solving_the_quadratic_equation.a -lm
test:bin
	./solving_the_quadratic_equation_test
