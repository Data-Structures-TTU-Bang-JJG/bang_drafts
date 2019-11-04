// Grace Gomez
// 11/3/2019

struct  player {
	char name[20];
	int role;
	int dice;
	int hand_size;
	int bullets; // life points. The amount you start the game with is your maximum hand size --> hand_size. cannot exceed at the end of the turn.
};

// player queue
typedef struct player_queue{
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
	varq->data = {};
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
    if( isEmpty_player_queue)
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

struct player_queue* create line_up() {
	
}

// role numbers. 1-> sheriff 2->deputy 3->outlaw 4->renegade

struct player* create_player(int char_num int role_num) {
	struct player* temp_player = (struct player*)malloc(sizeof(struct player));
	switch (player_num) {
		case 1: {
			temp_player->name = "Bart Cassidy";
			temp_player->bullets = 4;
			break;
		}
		case 2:{
			temp_player->name = "Black Jack";
			temp_player->bullets = 4;
			break;
		}
		case 3:{
			temp_player->name = "Calamity Janet";
			temp_player->bullets = 4;
			break;
		}
		case 4:{
			temp_player->name = "El Gringo";
			temp_player->bullets = 3;
			break;
		}
		case 5:{
			temp_player->name = "Jesse Jones";
			temp_player->bullets = 4;
			break;
		}
		case 6:{
			temp_player->name = "Jourdonnais ";
			temp_player->bullets = 4;
			break;
		}
		case 7:{
			temp_player->name = "Pedro Ramirez";
			temp_player->bullets = 4;
			break;
		}
		case 8:{
			temp_player->name = "Rose Doolan";
			temp_player->bullets = 4;
			break;
		}
		case 9:{
			temp_player->name = "Sid Ketchum";
			temp_player->bullets = 4;
			break;
		}
		case 10:{
			temp_player->name = "Slab the Killer ";
			temp_player->bullets = 4;
			break;
		}
		case 11:{
			temp_player->name = "Suzy Lafayette";
			temp_player->bullets = 4;
			break;
		}
		case 12:{
			temp_player->name = "Vulture Sam ";
			temp_player->bullets = 4;
			break;
		}
		case 13:{
			temp_player->name = "Willy the Kid";
			temp_player->bullets = 4;
			break;
		}
		case 14:{
			temp_player->name = "Paul Regret";
			temp_player->bullets = 3;
			break;
		}
		case 15:{
			temp_player->name = "Lucky Duke";
			temp_player->bullets = 4;
			break;
		}
		case 16:{
			temp_player->name = "Kit Carlson";
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

turn based on circular queue of type player;