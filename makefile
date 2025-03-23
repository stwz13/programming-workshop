SUBDIRS := $(shell find . -maxdepth 1 -type d -not -path "." -not -path "./.git" -not -path "./.github")
test: 
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir test; \
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