SRCMODULES = str.cpp edges.cpp lex.cpp sa.cpp
OBJMODULES = $(SRCMODULES: c=.o)
CXXFLAGS = -g -Wall 

%o: %.c %.h l.hpp str.hpp edges.hpp lex.hpp
	$(CXX) $(CXXFLAGS) -c $< -o %@

la: la.cpp $(OBJMODULES) l.hpp str.hpp edges.hpp lex.hpp
	$(CXX) $(CXXFLAGS) $^ string.o -o $@

ifneq (clean, $(MAKECMDGOALS))
-include deps.mk
endif

deps.mk: $(SRCMODULES)
	$(GXX) -MM $^ > $@

clean:
	rm *.o la
run: la
	valgrind  ./la src.txt
runv: la
	valgrind ./la src.txt > VG_LOG
	cat VG_LOG
gdb: la
	gdb --args ./la src.txt
gdb_at: la
	valgrind --vgdb=yes --vgdb-error=1 ./la src.txt
