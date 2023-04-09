TARGET = ./main.out
VALGRIND_LOG = "valgrind.log"
ARGS = \
		-d /home/hrmx/Desktop/name.basics.tsv \
		-t /home/hrmx/Desktop/title.basics.tsv \
		-a /home/hrmx/Desktop/title.akas.tsv \
		-n "Aleksey Balabanov"

SRCS = \
		vk-ml-2023-1/src/main.cpp \
		vk-ml-2023-1/src/utilities.cpp \
		vk-ml-2023-1/src/utilities.hpp

.PHONY: all build memtest rebuild clean

all: clean build memtest

build: $(TARGET)

memtest: $(TARGET)
	valgrind --tool=memcheck --leak-check=full --log-file=$(VALGRIND_LOG) --args $(ARGS) $(TARGET)

rebuild: clean build

$(TARGET): $(SRCS)
	$(CXX) -std=c++20 -O2 -fdiagnostics-color -O0 -Wall -Wextra -Werror -I. -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET) ${VALGRIND_LOG}

