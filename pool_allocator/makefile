clean:
	rm -rf *.o *.a *_test
check_format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror
format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`
pool_allocator.o: pool_allocator.c pool_allocator.h
	gcc -g -c pool_allocator.c -o pool_allocator.o 
pool_allocator.a: pool_allocator.o
	ar rc pool_allocator.a pool_allocator.o 
pool_allocator_tests.o: pool_allocator_tests.c
	gcc -g -c pool_allocator_tests.c -o pool_allocator_tests.o -lm
bin: pool_allocator_tests.o pool_allocator.a
	gcc -g -static -o pool_allocator_tests pool_allocator_tests.o pool_allocator.a -lm
test:bin
	./pool_allocator_tests