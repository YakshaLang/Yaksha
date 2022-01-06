# Makefile to run coverage, etc
.PHONY: coverage

COV:=$(shell realpath "./bin/coverage")
FUZZ:=$(shell realpath "./bin/fuzz")
coverage:
	echo calculating code coverage
	@echo coverage folder is $(COV)
	@echo fuzz folder is $(FUZZ)
	docker build -t yaksha-sc .
	docker run -v $(COV):/coverage -v $(FUZZ):/fuzz --rm -it --entrypoint /app/scripts/code-coverage.sh yaksha-sc
