CC=gcc
CXX=g++
ODB=odb
RM=rm -f
TOUCH=touch
CPPFLAGS=-I/home/crash/.local/include $(EXTRA_CPPFLAGS)
CXXFLAGS=-g -std=c++1z
ODBFLAGS=-I/home/crash/.local/include -d pgsql --hxx-suffix .hpp --cxx-suffix .cpp --ixx-suffix .ipp --sql-name-case lower --generate-query
LDFLAGS=-g -L/home/crash/.local/lib
LDLIBS=-lodb -lodb-pgsql

PSQL=psql
DBNAME=crash
DROPTBL_SQL="drop table finances"
CLEARTBL_SQL="delete from finances"
LOADTBL_SQL="copy finances ( digits, guaincome, guaexpend, rembudget, monthbudget, weekcounter, percentsave, percentwarning, name) from stdin"

SRCS=main.cpp finances.cpp finances-odb.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
GENFILES=finances-odb.cpp finances-odb.hpp finances-odb.ipp finances.sql
DBTARGETS=.createdb .loaddb

all: baa-cli

baa-cli: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

finances-odb.cpp: finances.hpp
	$(ODB) $(ODBFLAGS) $<

finances.sql: finances.hpp
	$(ODB) $(ODBFLAGS) --generate-schema $<

depend: .depend

.depend: $(SRCS)
	$(RM) .depend
	$(CPP) $(CPPFLAGS) -MM $^ >> .depend;

createdb: .createdb

.createdb: finances.sql
	$(RM) $@
	$(PSQL) -ef $< $(DBNAME)
	$(TOUCH) $@

loaddb: .createdb .loaddb

.loaddb: readFile.txt
	$(RM) $@
	$(PSQL) -c $(CLEARTBL_SQL) $(DBNAME)
	sed 's/ \+/|/g9;s/ \+/\t/g;s/|/ /' $< | $(PSQL) -c $(LOADTBL_SQL) $(DBNAME)
	$(TOUCH) $@

cleandb:
	$(PSQL) -c $(DROPTBL_SQL) $(DBNAME)
	$(RM) $(DBTARGETS)

clean:
	$(RM) $(OBJS) $(GENFILES)

distclean: clean
	$(RM) *~ .depend

include .depend
