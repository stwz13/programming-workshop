
clean:
	rm -rf *.o *.a *_test
check_format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror
format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`
task4.o: task4.c task4.h
	gcc -g -c task4.c -o task4.o
task4.a: task4.o
	ar rc task4.a task4.o
main.o: main.c
	gcc -g -c main.c -o main.o
test: main.o task4.a
	gcc -g -static -o task4_test main.o task4.a
