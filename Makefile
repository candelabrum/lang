CXXFLAGS = -g -Wall -Wfatal-errors -D FIRST -D WATCH

CXXFLAGSDEBUG = -g -Wall -Wfatal-errors -D FIRST DEBUG_EXE DEBUG

source_dirs := . first_step

search_wildcards := $(addsuffix /*.cpp,$(source_dirs)) 

main: $(notdir $(patsubst %.cpp,%.o,$(wildcard $(search_wildcards))))
	$(CXX) $(CXXFLAGS) $^ mystr.o -o $@ >> G++LOG

VPATH := $(source_dirs)
     
%.o: %.cpp
	g++ $(CXXFLAGS) -c -MD $(addprefix -I,$(source_dirs)) $<

include $(wildcard *.d) 

mystr.o:
	gcc -Wall -g -c mystr.c -o mystr.o

string.h:
	echo "hello" > counter.txt
first_step/l.hpp:
	echo "hello" > counter.txt

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -MD $(addprefix -I,$(SOURCE_DIRS)) $<

clean:
	rm *.o 
	rm *.d
	rm main 
	gcc -Wall -g -c string.c -o string.o
run: main
	valgrind --leak-check=full ./main 0 4774 .create 2 bot src.txt
runv: main 
	valgrind ./main src.txt > VG_LOG
	cat VG_LOG
gdb: main 
	gdb --args ./main 0 4774 .create 2 bot src.txt
gdb_at: main 
	valgrind --vgdb=yes --vgdb-error=1 ./main src.txt 
res:
	make clean
	make run
run_join:
	valgrind --leak-check=full ./main 0 4774 join bot bot1 src.txt
run_idiot:
	valgrind --leak-check=full ./main 0 4774 .create 4 bot idiot.txt 
