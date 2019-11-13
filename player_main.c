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

struct stack* arrows;
struct player_queue lineup;

#include "dice22.h"

/*{ Library functions table of content 

stacks.h
create_stack();
push(int, stack)
pop(stack)
isEmpty(stacks);
isFull(stack)

player.h
struct player_queue create_player_queue();                         //to create a queue in another function call using { struct queuec* [the name of your queue] = create_queuec }
bool isEmpty_player_queue (struct player_queue varq);              // Function that checks if the player_queue is empty
bool isFull_player_queue (struct player_queue varq);               // Function that checks if the player_queue is full
void enqueue_player (struct player_queue* varq, struct player);    // Function that adds a player to the player_queue
void dequeue_player (struct player_queue* varq);                   // Function that deletes a player from the player_queue
void peek_player (struct player_queue varq);                       // Function that prints out the name ofthe current player playing

dice.h
struct stack dice_sheriff(int current, bool* gatlin, bool* dynamite, int* beer);
struct stack dice_deputy(int current, bool* gatlin, bool* dynamite, int* beer);
struct stack dice_outlaw(int current, bool* gatlin, bool* dynamite, int* beer);
bool save_the_sheriff();
bool pull_arrow(int current);
void fill_arrows();
void indian_attack(int current, int start); )*/


int main(int argc, char **argv)
{
	printf("hello world\n");
	cout << sizeof(player);
	lineup = create_line_up(8);//(srand(time(0))%5+4);
	struct player_queue debugg = lineup;
	arrows = create_stack();
	print_recursive(lineup,lineup.front,lineup.front);
	//struct stack shot = dice_sheriff(0,&g,&d&b);
	//while((line_upfront != 1) || (sides <= 1) || (line_up.front == line_up.rear)){
		
	//}
	cout << "The winner is: " ;
	print_recursive(lineup,lineup.front,lineup.front);
	return 0;
}

//when a character dies sides = sides - temp_player->role.
