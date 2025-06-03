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

object_control.o:object_control.c object_control.h ../pool_allocator/pool_allocator.h 
	gcc -g -c object_control.c -o object_control.o -Ipool_allocator -Igc
object_control.a: object_control.o pool_allocator.a 
	ar rc object_control.a object_control.o 
object_control_tests.o: object_control_tests.c
	gcc -g -c object_control_tests.c -o object_control_tests.o -Ipool_allocator -Igc -lm
bin: object_control_tests.o object_control.a pool_allocator.a
	gcc -g -static -o object_control_tests object_control_tests.o object_control.a pool_allocator.a -lm
test:bin
	./object_control_tests

