SRCMODULES = str.cpp edges.cpp lex.cpp sa.cpp
OBJMODULES = $(SRCMODULES: c=.o)
CXXFLAGS = -g -Wall -Weffc++ -Wextra -Woverloaded-virtual -Wnon-virtual-dtor -Wold-style-cast -Wunreachable-code -Wconversion -Wsign-conversion -Winit-self

string.o:
	gcc -Wall -g -c string.c -o string.o

%o: %.c %.h l.hpp str.hpp edges.hpp lex.hpp
	$(CXX) $(CXXFLAGS) -c $< -o %@ 2> G++LOG

la: la.cpp $(OBJMODULES) l.hpp str.hpp edges.hpp lex.hpp
	$(CXX) $(CXXFLAGS) $^ string.o -o $@ 2>> G++LOG

ifneq (clean, $(MAKECMDGOALS))
-include deps.mk
endif

deps.mk: $(SRCMODULES)
	$(GXX) -MM $^ > $@

clean:
	rm *.o la
	gcc -Wall -g -c string.c -o string.o
run: la
	cppcheck $(SRCMODULES)
	valgrind  ./la src.txt
runv: la
	valgrind ./la src.txt > VG_LOG
	cat VG_LOG
gdb: la
	gdb --args ./la src.txt
gdb_at: la
	valgrind --vgdb=yes --vgdb-error=1 ./la src.txt
