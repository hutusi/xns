
# Makefile for xns 

ROOT = ..
XNS_INCLUDE_DIR = $(ROOT)/include
XNS_SRC_DIR = $(ROOT)/src

ALL_SRC = $(notdir $(wildcard $(XNS_SRC_DIR)/*.cpp))
ALL_OBJS = $(patsubst %.cpp,%.o,$(ALL_SRC))

CPPFLAGS += -I$(XNS_INCLUDE_DIR)

vpath %.cpp $(XNS_SRC_DIR)

$(ALL_OBJS) : %.o : %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ -o $@

all: $(ALL_OBJS)


print:
	@echo $(ALL_SRC)
	@echo $(ALL_OBJS)

