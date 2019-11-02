DIRS := $(shell find . -maxdepth 1 -mindepth 1 -type d -not -name '.git')
run: $(DIRS)
$(DIRS):
	$(MAKE) -C $@

.PHONY: run $(DIRS)
