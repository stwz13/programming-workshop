.PHONY: clean format check_format bin test

bin: linear_allocator_test

clean:
	rm -rf *.o *.a *_test linear_allocator_test

check_format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

linear_allocator.o: linear_allocator.c linear_allocator.h
	gcc -Wall -Wextra -Werror -std=c11 -g -c linear_allocator.c -o linear_allocator.o

linear_allocator_test.o: main.c
	gcc -Wall -Wextra -Werror -std=c11 -g -c main.c -o linear_allocator_test.o

linear_allocator.a: linear_allocator.o
	ar rc linear_allocator.a linear_allocator.o

linear_allocator_test: linear_allocator_test.o linear_allocator.a
	gcc -Wall -Wextra -Werror -std=c11 -g -static -o linear_allocator_test linear_allocator_test.o linear_allocator.a

test: bin
	./linear_allocator_test