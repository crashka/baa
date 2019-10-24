CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=
CXXFLAGS=-g -std=c++1z
LDFLAGS=-g
LDLIBS=

SRCS=main.cpp finances.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: baa-cli

baa-cli: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	$(RM) .depend
	$(CPP) $(CPPFLAGS) -MM $^ >> .depend;

clean:
	$(RM) $(OBJS) $(GENFILES)

distclean: clean
	$(RM) *~ .depend

include .depend
