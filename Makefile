

CC 			= gcc
CXX 		= g++
RM 			= rm
LFLAGS  	= -ggdb -llua5.1 -ldl -lstdc++ -fPIC -O0
CFLAGS  	= -ggdb -Wall -Wformat=0 -I./include -llua5.1
CXXFLAGS    = -ggdb -MMD -Wall -Wformat=0 -I./include -llua5.1

BUILDPATH = build

BIN = testlua

OBJS 	= $(BUILDPATH)/main.o $(BUILDPATH)/lua4cpp.o
DEPENDS	= $(BUILDPATH)/main.d $(BUILDPATH)/lua4cpp.d

-include $(DEPENDS)

.PHONY : all clean

all : $(BIN)

clean :
	-$(RM) -f $(BUILDPATH)/*
	-$(RM) -f $(BIN)

$(BIN) : $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

$(BUILDPATH)/%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@
$(BUILDPATH)/%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@
