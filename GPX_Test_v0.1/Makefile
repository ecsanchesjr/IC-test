SOURCES := $(shell find $(SRC_PATH) -type f -name *.$(SRC_TEXT))

all: build run

build:
	g++ -std=gnu++14 $(SOURCES)

run:
	./a.out
