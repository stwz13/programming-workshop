SUBDIRS := $(shell find . -maxdepth 1 -type d -not -path "." -not -path "./.git" -not -path "./.github")
GC_DIRS := $(shell find . -maxdepth 1 -type d -name "*gc" -not -path "." -not -path "./.git" -not -path "./.github")
TEST_MEMORY_FILES := $(foreach dir,$(GC_DIRS),$(wildcard $(dir)/test $(dir)/tests $(dir)/*test $(dir)/*tests))
test: 
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir test; \
	done
memory_test:test
	for test_exec in $(TEST_MEMORY_FILES); do \
		valgrind --leak-check=full  $$test_exec; \
	done
clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
check_format:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir check_format; \
	done
format:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir format; \
	done
