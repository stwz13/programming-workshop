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

hash_table.o:hash_table.c hash_table.h ../pool_allocator/pool_allocator.h 
	gcc -g -c hash_table.c -o hash_table.o -Ipool_allocator -Ihash_table
hash_table.a: hash_table.o pool_allocator.a 
	ar rc hash_table.a hash_table.o 
hash_table_tests.o: hash_table_tests.c
	gcc -g -c hash_table_tests.c -o hash_table_tests.o -Ipool_allocator -Ihash_table -lm
bin: hash_table_tests.o hash_table.a pool_allocator.a
	gcc -g -static -o hash_table_tests hash_table_tests.o hash_table.a pool_allocator.a -lm
test:bin
	./hash_table_tests
