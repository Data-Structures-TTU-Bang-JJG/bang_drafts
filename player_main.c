#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <iostream>
#include <fstream> 
#include <string.h>

#define MAX 50

using namespace std;

#include "stacks.h"
//#include "queue.h"
#include "player.h"
#include "dice.h"

struct stack* arrows;
struct player_queue lineup;
bool savethesheriff;

int main(int argc, char **argv)
{
	printf("hello world\n");
	cout << sizeof(player);
	lineup = create_line_up(8);
	print_recursive(lineup,lineup.front,lineup.front);
	//while((line_upfront != 1) || (sides <= 1) || (line_up.front == line_up.rear)){
		
	}//
	cout << "The winner is: " ;
	print_recursive(lineup,lineup.front,lineup.front);
	return 0;
}

//when a character dies sides = sides - temp_player->role.
