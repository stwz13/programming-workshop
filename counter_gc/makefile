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

gc.o:gc.c gc.h ../pool_allocator/pool_allocator.h 
	gcc -g -c gc.c -o gc.o -Ipool_allocator -Igc
gc.a: gc.o pool_allocator.a 
	ar rc gc.a gc.o 
gc_tests.o: gc_tests.c
	gcc -g -c gc_tests.c -o gc_tests.o -Ipool_allocator -Igc -lm
bin: gc_tests.o gc.a pool_allocator.a
	gcc -g -o gc_tests gc_tests.o gc.a pool_allocator.a -lm
test:bin
	./gc_tests

	
