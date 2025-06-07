clean:
	rm -rf *.o *.a *_test *_tests *.log gc_tests

check_format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

gc_mark_sweep.o: gc_mark_sweep.c gc_mark_sweep.h
	gcc -g -c gc_mark_sweep.c -o gc_mark_sweep.o

gc_mark_sweep.a: gc_mark_sweep.o
	ar rc gc_mark_sweep.a gc_mark_sweep.o

gc_tests.o: gc_mark_sweep_tests.c
	gcc -g -c gc_mark_sweep_tests.c -o gc_tests.o

bin: gc_tests.o gc_mark_sweep.a
	gcc -g -o gc_tests gc_tests.o gc_mark_sweep.a

test: bin
	./gc_tests

