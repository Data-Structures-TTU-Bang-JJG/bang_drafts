// Grace Gomez
// 11/3/2019

#include<time.h> 

struct  player {
	int name; // In the print function there is a switch case that prints there name based on this number 1 -16
	int role; // 1 is Sherrif, 0 is Deputy, 3 is Outlaw, 4 is Renegade 
	int dice; // This is rollable dice and is initalized as 5 at the beginning of each turn
	int hand_size; // The largest number of bullets that an individual can have. Their starting number
	int bullets; // life points. The amount you start the game with is your maximum hand size --> hand_size. cannot exceed at the end of the turn.
	int arrows;
	int beer; //delete
	int next; // the next array element in the circular queue values between 0 and 7
};

struct player_queue{
    struct player data[8]; //queue array
    int front;
    int rear;
};

struct player_queue create_player_queue();  //to create a queue in another function call using { struct queuec* [the name of your queue] = create_queuec }
bool isEmpty_player_queue (struct player_queue varq);
bool isFull_player_queue (struct player_queue varq);
void enqueue_player (struct player_queue* varq, struct player);
void dequeue_player (struct player_queue* varq);
void peek_player (struct player_queue varq);

// NAME : create_player_queue()
// INPUT: none
// OUTPUT: returns a struct
// PURPOSE: 

struct player_queue create_player_queue() {
	struct player_queue varq;
	varq.front = -1;
	varq.rear = -1;
	memset(varq.data, '\0', sizeof(varq.data));
	return varq;
}

bool isEmpty_player_queue (struct player_queue* varq){
	return (varq->rear==-1);
}

bool isFull_player_queue (struct player_queue* varq){
	if ( ( (varq->front !=0) && (varq->rear==varq->front-1)  ) || ( (varq->front==0) && (varq->rear==MAX-1) ) ) {
		return ( 1==1 );
	}
	else
		return ( 0==1 );
}

void enqueue_player (struct player_queue* varq, struct player new_player) {
	if( isFull_player_queue (varq) ) 
		return;
    else if(varq->front==-1 && varq->rear==-1)
        {
        varq->front=varq->rear=0;
        varq->data[0] = new_player;
        }
    else if(varq->rear==MAX-1 && varq->front!=0)
        {
        varq->rear=0;
        varq->data[varq->rear] = new_player;
        }
    else
        {
        varq->rear++;
        varq->data[varq->rear] = new_player;
        }
}

void dequeue_player (struct player_queue* varq) {
	if (isEmpty_player_queue(varq))
		return;
	else if(varq->front!=-1 && varq->front==varq->rear) {
		varq->front=varq->rear=-1;
	}
	else {
		if(varq->front==MAX-1) {
			varq->front=0;
		}
		else {
			varq->front++;
		}
	}
}

void peek_player (struct player_queue varq) {
    if( isEmpty_player_queue(&varq))
        {
        cout <<"\n No One is Playing" <<endl;
        return;
        }
    else
        {
        cout << varq.data[varq.front].name;
		return;
        }
}

void shuffle_array(int* arr, int size) {
	for (int a = 0; a<5; a++) {
		for (int i = 0; i < size ; i++){
			srand(time(0));
			int var = rand()%size;
			int temp = *(arr+i);
			*(arr+i )= *(arr+var);
			*(arr+var) = temp;
		}
	}
}

/*
struct player* create_player_node(){
	malloc(sizeof(struct player*));
	struct player *temp_player = (struct player*) malloc(sizeof(struct player));
	for(int i=0;i<20;i++)
		temp_player->name[i] = NULL;
	temp_player->role=0;
	temp_player->dice =0;
	temp_player->hand_size =0;
	temp_player->bullets =0;
}
*/

struct player create_player(int char_num, int role_num) {
	struct player temp_player;
	//temp_player.name=(char*)calloc(20,sizeof(char));
	temp_player.name = char_num;
	if(char_num == 14 || char_num == 4){
		temp_player.bullets = 3;
	}
	else 
		temp_player.bullets = 4;
		
		
	if (role_num == 1) {
		temp_player.bullets = temp_player.bullets + 2;
	}
	temp_player.role = role_num;
	temp_player.dice = 6;
	temp_player.arrows = 0;
	temp_player.beer = 0;
	temp_player.hand_size = temp_player.bullets;
	return temp_player;
}

void print_player(struct player var_player) {
	cout << "\n\nNext Player: ";
	switch (var_player.name) {
		case 1: {
			cout << "Bart Cassidy" ;
			break;
		}
		case 2:{
			cout << "Black Jack";
			break;
		}
		case 3:{
			cout << "Calamity Janet";
			break;
		}
		case 4:{
			cout << "El Gringo";
			break;
		}
		case 5:{
			cout << "Jesse Jones";
			break;
		}
		case 6:{
			cout << "Jourdonnais ";
			break;
		}
		case 7:{
			cout << "Pedro Ramirez";
			break;
		}
		case 8:{
			cout << "Rose Doolan";
			break;
		}
		case 9:{
			cout <<"Sid Ketchum";
			break;
		}
		case 10:{
			cout << "Slab the Killer ";
			break;
		}
		case 11:{
			cout << "Suzy Lafayette";
			break;
		}
		case 12:{
			cout <<"Vulture Sam ";
			break;
		}
		case 13:{
			cout << "Willy the Kid";
			break;
		}
		case 14:{
			cout <<"Paul Regret";
			break;
		}
		case 15:{
			cout << "Lucky Duke";
			break;
		}
		case 16:{
			cout << "Kit Carlson";
			break;
		}
	}
	if (var_player.role == 1)	cout << "\nSHERRIF";
	if (var_player.dice) cout << "\nDice: "<<  var_player.dice;
	if (var_player.hand_size)cout << "\nHand Size: " <<  var_player.hand_size;
	if (var_player.bullets)cout << "\nBullets: " <<  var_player.bullets;
}

void print_recursive(struct player_queue line_up,int current, int first) {
	print_player(line_up.data[current]);
	if (line_up.data[current].next == first) {
		return;
	}
	print_recursive(line_up,line_up.data[current].next,first);
}

struct player_queue create_line_up(int number_of_players) {
	int char_num_arr[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}, k;
		shuffle_array(char_num_arr,16);
	struct stack* roles_stack = create_stack();
	for (int i = 0; i < (number_of_players/2); i ++) {
		push(3, roles_stack);
	}
	push(4,roles_stack);
	if (number_of_players == 8) {
		push(4, roles_stack);
	}
	int deputy = ((number_of_players-3)/2);
	for (int j = 0; j < deputy ; j++) {
		push(0,roles_stack);
	}
	shuffle_array(roles_stack->data,number_of_players);
	push(1, roles_stack); // sheriff must be the first element
	struct player_queue player_lineup = create_player_queue();
	player_lineup.front = 0;
	struct player_queue* ptr_player_lineup = &player_lineup;
	for( k = 0; k < number_of_players; k++) {
		ptr_player_lineup->data[k] = create_player(char_num_arr[k],pop(roles_stack));
		//enqueue_player(ptr_player_lineup,temp_player);
		ptr_player_lineup->data[k].next = k+1;
	}
	player_lineup.rear = k-1;
	player_lineup.data[player_lineup.rear].next = 0; 
	return player_lineup;
}
// role numbers. 1-> sheriff 2->deputy 3->outlaw 4->renegade
//turn based on circular queue of type player;
