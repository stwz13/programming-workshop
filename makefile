SUBDIRS := $(shell find . -maxdepth 1 -type d -not -path "." -not -path "./.git" -not -path "./.github")
bin: 
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir test; \
	done
test: bin
	@for dir in $(SUBDIRS); do \
		cd $$dir; \
		for test in $$(find . -maxdepth 1 -type f -executable -name "*_test*"); do \
			./$$test || exit 1; \
		done; \
		cd ..; \
	done

clean:
	@echo $(SUBDIRS) | xargs -I {} $(MAKE) -C {} clean
	rm -rf *_test *.o *.a
