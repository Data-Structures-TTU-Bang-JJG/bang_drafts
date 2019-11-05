// Grace Gomez
// 11/3/2019

#include<time.h> 

struct  player {
	char* name;
	int role;
	int dice;
	int hand_size;
	int bullets; // life points. The amount you start the game with is your maximum hand size --> hand_size. cannot exceed at the end of the turn.
};

// player queue
struct player_queue{
    struct player* data[8]; //queue array
    int front;
    int rear;
};

struct player_queue* create_player_queue();  //to create a queue in another function call using { struct queuec* [the name of your queue] = create_queuec }
bool isEmpty_player_queue (struct player_queue* varq);
bool isFull_player_queue (struct player_queue* varq);
void enqueue_player (struct player_queue* varq, struct player*);
void dequeue_player (struct player_queue* varq);
void peek_player (struct player_queue* varq);

struct player_queue* create_player_queue() {
	struct player_queue* varq = (struct player_queue*)malloc(sizeof(struct player_queue*));
	varq->front = -1;
	varq->rear = -1;
	memset(varq->data, NULL, sizeof(varq->data));
	return varq;
}

bool isEmpty_player_queue (struct player_queue* varq){
	return (varq->rear==-1);
}

bool isFull_player_queue (struct player_queue* varq){
	if ( (varq->front !=0) && (varq->rear==varq->front-1)  || ( (varq->front==0) && (varq->rear==MAX-1) ) ) {
		return ( 1==1 );
	}
	else
		return ( 0==1 );
}

void enqueue_player (struct player_queue* varq, struct player* new_player) {
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

void peek_player (struct player_queue* varq) {
    if( isEmpty_player_queue(varq))
        {
        cout <<"\n No One is Playing" <<endl;
        return;
        }
    else
        {
        cout << varq->data[varq->front]->name;
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

struct player* create_player(int char_num, int role_num) {
	struct player *temp_player = (struct player*)malloc(sizeof(struct player*));
	//temp_player->name=(char*)calloc(20,sizeof(char));
	switch (char_num) {
		case 1: {
			strcpy(temp_player->name ,"Bart Cassidy" );
			temp_player->bullets = 4;
			break;
		}
		case 2:{
			strcpy(temp_player->name,"Black Jack");
			temp_player->bullets = 4;
			break;
		}
		case 3:{
			strcpy(temp_player->name,"Calamity Janet");
			temp_player->bullets = 4;
			break;
		}
		case 4:{
			strcpy(temp_player->name , "El Gringo");
			temp_player->bullets = 3;
			break;
		}
		case 5:{
			strcpy(temp_player->name , "Jesse Jones");
			temp_player->bullets = 4;
			break;
		}
		case 6:{
			strcpy(temp_player->name , "Jourdonnais ");
			temp_player->bullets = 4;
			break;
		}
		case 7:{
			strcpy(temp_player->name , "Pedro Ramirez");
			temp_player->bullets = 4;
			break;
		}
		case 8:{
			strcpy(temp_player->name , "Rose Doolan");
			temp_player->bullets = 4;
			break;
		}
		case 9:{
			strcpy(temp_player->name, "Sid Ketchum");
			temp_player->bullets = 4;
			break;
		}
		case 10:{
			strcpy(temp_player->name , "Slab the Killer ");
			temp_player->bullets = 4;
			break;
		}
		case 11:{
			strcpy(temp_player->name , "Suzy Lafayette");
			temp_player->bullets = 4;
			break;
		}
		case 12:{
			strcpy(temp_player->name , "Vulture Sam ");
			temp_player->bullets = 4;
			break;
		}
		case 13:{
			strcpy(temp_player->name , "Willy the Kid");
			temp_player->bullets = 4;
			break;
		}
		case 14:{
			strcpy(temp_player->name , "Paul Regret");
			temp_player->bullets = 3;
			break;
		}
		case 15:{
			strcpy(temp_player->name , "Lucky Duke");
			temp_player->bullets = 4;
			break;
		}
		case 16:{
			strcpy(temp_player->name , "Kit Carlson");
			temp_player->bullets = 4;
			break;
		}
	}
	if (role_num == 1) {
		temp_player->bullets++;
	}
	temp_player->role = role_num;
	temp_player->dice = 6;
	temp_player->hand_size = temp_player->bullets;
	return temp_player;
}

void print_player(struct player* var_player) {
	cout << "Name: " << var_player->name;
	cout << "Role: " <<  var_player->role;
	cout << "Dice: " <<  var_player->dice;
	cout << "Hand Size: " <<  var_player->hand_size;
	cout << "Bullets: " <<  var_player->bullets;
}

void print_all_players(struct player_queue* line_up){
	struct player_queue* temp = line_up;
	while(!isEmpty_player_queue(temp)) {
		print_player(temp->data[temp->front]);
		dequeue_player(temp);
	}
}

struct player_queue* create_line_up(int number_of_players) {
	int char_num_arr[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
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
		push(2,roles_stack);
	}
	shuffle_array(roles_stack->data,number_of_players);
	push(0, roles_stack); // sheriff must be the first element
	struct player_queue* player_lineup = create_player_queue();
	for( int k = 0; k < number_of_players; k++) {
		enqueue_player(player_lineup,create_player(char_num_arr[k],pop(roles_stack)));
		cout << "done";
	}
	print_all_players(player_lineup);
	return player_lineup;
}
// role numbers. 1-> sheriff 2->deputy 3->outlaw 4->renegade
//turn based on circular queue of type player;
