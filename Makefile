CC=g++
FLAGS=-Wall -Werror -pedantic
LIB=-L/usr/local/lib/
INC=-I/usr/local/include/
LINKER=-lboost_regex -lboost_date_time

all: ps4b

ps4b: kronos_main.cpp kronos_parse_class.o
	$(CC) kronos_main.cpp kronos_parse_class.o $(INC) $(LIB) $(FLAGS) $(LINKER) -o ps4b

kronos_parse_class.o: kronos_parse_class.hpp kronos_parse_class.cpp
	$(CC) -c kronos_parse_class.cpp kronos_parse_class.hpp $(INC)

run: ps4b
	clear
	./ps4b device5_intouch.log

clean:
	rm -r ps4b *.rpt *~ *.gch *.o