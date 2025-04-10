clean:
	rm -rf *.o *.a *_test
check_format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror
format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`
list.o: list.c list.h
	gcc -g -c list.c -o list.o 
list.a: list.o
	ar rc list.a list.o 
main.o: main.c
	gcc -g -c main.c -o main.o -lm
bin: main.o list.a
	gcc -g -static -o list_test main.o list.a -lm
test:bin
	./list_test

