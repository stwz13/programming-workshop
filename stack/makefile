clean:
	rm -rf *.o *.a *_test
check_format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror
format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`
stack.o: stack.c stack.h
	gcc -g -c stack.c -o stack.o 
stack.a: stack.o
	ar rc stack.a stack.o 
main.o: main.c
	gcc -g -c main.c -o main.o -lm
bin: main.o stack.a
	gcc -g -static -o stack_test main.o stack.a -lm
test:bin
	./stack_test
