OUTPUT_DIR=build

all: build

${OUTPUT_DIR}/Makefile:
	@./configure

.PHONY: build
build: ${OUTPUT_DIR}/Makefile
	${MAKE} -C ${OUTPUT_DIR}

.PHONY: tests
tests:  ${OUTPUT_DIR}/Makefile
	${MAKE} -C ${OUTPUT_DIR} tests
