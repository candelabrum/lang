#include <stdio.h>
#include <stdlib.h>
#include "first_step/game.hpp"
#include "interp.hpp"

int main(int argc, char **argv)
{
	Game *game; 
	Interpretator interp;
	FILE *f;
	
	if (argc != 7)
	{
		printf("WRONG\n");
		return 0;
	}
	game = new Game();
	game->me.set(argv[5], argv[1], atoi(argv[2]), argv[3], argv[4]);
	game->me.enter_to_serv();
    game->me.check_start_game(); 
	game->me.prepare_to_first_move(game->gi);

	f = fopen(argv[6], "r");
	if (!f)
	    return 0;

	interp.Run(f, game);
	fclose(f);

	game->gi->disappear();

	delete game;

	return 0;
}
