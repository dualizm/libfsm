# projects

LIB := lib
EXAMPLES := examples

all: makeDirs $(LIB) $(EXAMPLES)

makeDirs:
	mkdir -p bin out

$(LIB):
	cd $(LIB) && $(MAKE)

$(EXAMPLES):
	cd $(EXAMPLES) && $(MAKE)

clean:
	rm -rf bin out

.PHONY: all makeDirs clean $(LIB) $(EXAMPLES)
