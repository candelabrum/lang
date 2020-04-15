#include <stdio.h>
#include <stdlib.h>
#include "game_info.hpp"
#include "interp.hpp"

int main(int argc, char **argv)
{
    Interpretator interp;
    bot bot1;
	char *bot_name, *ip;
    int port;
	
	if (argc != 7)
	{
		printf("WRONG\n");
		return 0;
	}
    ip = argv[1];
	port = atoi(argv[2]);
	printf("%d\n", port);
	bot1.set(argv[5], ip, port, argv[3], argv[4]);
	bot1.enter_to_serv();
    bot1.check_start_game(); 
    bot1.prepare_to_first_move();
    interp.Start(argv[6]); 

	return 0;
}
