clean:
	rm -rf *.o *.a *_test
check_format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror
format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`
integral.o: integral.c integral.h
	gcc -g -c integral.c -o integral.o 
integral.a: integral.o
	ar rc integral.a integral.o 
main.o: main.c
	gcc -g -c main.c -o main.o -lm
bin: main.o integral.a
	gcc -g -static -o integral_test main.o integral.a -lm
test:bin
	./integral_test

