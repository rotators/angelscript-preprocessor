CXX ?= g++

SRC = $(wildcard *.cpp)
BIN = $(sort $(SRC:.cpp=))

INCLUDES = ..
CXXFLAGS = -std=gnu++0x -W -m32

all: preprocessor.o $(BIN)

%: %.cpp utils.h ../preprocessor.h
	@echo :: $(notdir $@) ::
	$(CXX) $(CXXFLAGS) $< $(addprefix -I, $(INCLUDES)) -o $@ preprocessor.o

preprocessor.o: ../preprocessor.cpp ../preprocessor.h
	@echo :: $(notdir $@) ::
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f preprocessor.o $(BIN)

again: clean all
