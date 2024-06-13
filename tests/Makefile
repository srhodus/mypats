CXX = g++
CXX_FLAGS = -Wfatal-errors -Wall -Wextra -Wpedantic -Wconversion -Wshadow \
            -g -fstack-protector-strong
# GIT_HASH := "$(shell git rev-parse HEAD)"
CXX_FLAGS += -DGIT_HASH=\"$(GIT_HASH)\"
BIN = a.out
LDFLAGS =
INCL = $(shell pkg-config gtest --cflags) $(shell pkg-config Qt6Core --cflags)
LIBS = $(LDFLAGS) $(shell pkg-config gtest --libs) $(shell pkg-config Qt6Core --libs)
SRC = $(wildcard *.cc) ../Rules.cc
OBJ = $(SRC:%.cc=%.o) ../Rules.o
DEP = $(OBJ:%.o=%.d) ../Rules.d
$(BIN) : $(OBJ)
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) $(INCL) $^ $(LIBS) -o $@
-include $(DEP)
%.o : %.cc
	$(CXX) $(CXX_FLAGS) $(INCL) -MMD -c $< -o $@
.PHONY : clean
clean :
	rm -f $(BIN) *.o *.d core.*
