SRCMODULES = str.cpp edges.cpp lex.cpp sa.cpp rpn.cpp l.cpp rpn_func.cpp rpn_types.cpp rpn_list.cpp rpn_go.cpp main.cpp exe.cpp
OBJMODULES = $(SRCMODULES: c=.o)
CXXHARDFLAGS = -g -Wall -Weffc++ -Wextra -Woverloaded-virtual -Wnon-virtual-dtor -Wold-style-cast -Wunreachable-code -Wconversion -Wsign-conversion -Winit-self
CXXFLAGS = -g -Wall -Wfatal-errors 
CXXFLAGSDEBUG = -g -Wall -Wfatal-errors -D DEBUG

string.o:
	gcc -Wall -g -c string.c -o string.o

%o: %.c %.h l.hpp str.hpp edges.hpp lex.hpp
	$(CXX) $(CXXFLAGS) -c $< -o %@ > G++LOG

la: la.cpp $(OBJMODULES) l.hpp str.hpp edges.hpp lex.hpp
	$(CXX) $(CXXFLAGS) $^ string.o -o $@ >> G++LOG

ifneq (clean, $(MAKECMDGOALS))
-include deps.mk
endif

deps.mk: $(SRCMODULES)
	$(GXX) -MM $^ > $@

clean:
	rm *.o 
	rm la
	gcc -Wall -g -c string.c -o string.o
run: la
	make string.o
	valgrind --leak-check=full ./la src.txt
runv: la
	valgrind ./la src.txt > VG_LOG
	cat VG_LOG
gdb: la
	gdb --args ./la src.txt
gdb_at: la
	valgrind --vgdb=yes --vgdb-error=1 ./la src.txt
res:
	make clean
	make run
