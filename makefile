all: task3_test
clean:
	rm -rf *.o *.a *_test
check_format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror
format:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`
test: task3_test
	@for test in $(shell find . -maxdepth 3 -type f -regex '.*_test'); do \
		echo "$$test is running"; \
		./$$test || exit 1; \
	done
