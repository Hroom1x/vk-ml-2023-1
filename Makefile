TARGET = ./main.out
VALGRIND_LOG = "valgrind.log"
ARGS = 'echo 123 | echo 321'

SRCS = \
		src/main.cpp \
		src/ioperation.cpp \
		src/parser.cpp

HDRS = \
		include/ioperation.hpp \
		include/parser.hpp

.PHONY: all build memtest rebuild clean

all: clean build memtest

$(TARGET) : $(SRCS) $(HDRS)
	$(CXX) -std=c++17 -g -fdiagnostics-color -O0 -Wall -Wextra -Werror -I. -o $(TST_TARGET) $(TST_SRCS)

build: $(TARGET)

memtest: $(TARGET)
	valgrind --tool=memcheck --leak-check=full --log-file=$(VALGRIND_LOG) $(TARGET) $(ARGS)

rebuild: clean build

$(TARGET): $(SRCS)
	$(CXX) -std=c++20 -O2 -fdiagnostics-color -O0 -Wall -Wextra -Werror -I. -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET) ${VALGRIND_LOG}

