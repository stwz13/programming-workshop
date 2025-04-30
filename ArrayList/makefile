clean:
	rm -rf *.o *.a *_test *_tests *.log
check_format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror
format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

pool_allocator.o: ../pool_allocator/pool_allocator.c ../pool_allocator/pool_allocator.h
	gcc -g -c ../pool_allocator/pool_allocator.c -o pool_allocator.o 
pool_allocator.a: pool_allocator.o
	ar rc pool_allocator.a pool_allocator.o 

array.o:array.c array.h ../pool_allocator/pool_allocator.h 
	gcc -g -c array.c -o array.o -Ipool_allocator -Iarray
array.a: array.o pool_allocator.a 
	ar rc array.a array.o 
array_tests.o: array_tests.c
	gcc -g -c array_tests.c -o array_tests.o -Ipool_allocator -Iarray -lm
bin: array_tests.o array.a pool_allocator.a
	gcc -g -static -o array_tests array_tests.o array.a pool_allocator.a -lm
test:bin
	./array_tests
