#
#	"src" folder contains the .cpp files
#	"include" folder contains the .h files
#
#	Makefile configs
#

CC := g++ -std=gnu++14 #compilador e diretivas

SRC_PATH := src #pasta com os cpp
SRC_TEXT := cpp	#tipo de arquivo

INC := -I headers #pasta com os headers

OUT_PATH := bin	#pasta para o executável
TARGET := bin/main	#Executável
TARGET_OPT := bin/dist

SOURCES := $(shell find $(SRC_PATH) -type f -name *.$(SRC_TEXT)) # shellscript para procurar os source files

#
#	Makefile code
#

ALL: build run

build:
	@echo "Building source files..."
	@mkdir -p $(OUT_PATH)
	$(CC) $(SOURCES) $(INC) -o $(TARGET)
	@echo ""

run:
	@echo "Running application..."
	@echo ""
	@./$(TARGET)

clean:
	@echo "Deleting /bin folder..."
	@echo ""
	@rm -r $(OUT_PATH)

dist:
	@echo "build optimized code..."
	@echo ""
	$(CC) $(SOURCES) $(INC) -o $(TARGET_OPT) -O3
	@echo ""