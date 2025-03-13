
clean:
	rm -rf *.o *.a *_test
check_format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror
format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`
task3.o: task3.c task3.h
	gcc -g -c task3.c -o task3.o
task3.a: task3.o
	ar rc task3.a task3.o
main.o: main.c
	gcc -g -c main.c -o main.o
task3_test: main.o task3.a
	gcc -g -static -o task3_test main.o task3.a
test3: task3_test
	./task3_test
test: task3_test
