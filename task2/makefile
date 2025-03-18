
clean:
	rm -rf *.o *.a *_test
check_format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror
format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`
task2.o: task2.c task2.h
	gcc -g -c task2.c -o task2.o
task2.a: task2.o
	ar rc task2.a task2.o
main.o: main.c
	gcc -g -c main.c -o main.o -lm
test: main.o task2.a
	gcc -g -static -o task2_test main.o task2.a -lm
