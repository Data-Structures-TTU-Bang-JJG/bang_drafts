// Grace Gomez
// 11/3/2019
// Comments by Jose Sosa
#include<time.h> 

// Structure that holds players info
struct  player {
	int name;             // In the print function there is a switch case that prints their name based on this number 1 - 16
	int role;             // 1 is Sherrif, 0 is Deputy, 3 is Outlaw, 4 is Renegade 
	int dice;             // This is rollable dice and is initalized as 5 at the beginning of each turn
	int hand_size;        // The largest number of bullets that an individual can have (Max Health)
	int bullets;          // life points. The amount you start the game with is your maximum hand size --> hand_size. cannot exceed at the end of the turn.
	int arrows;
	int next;             // the next array element in the circular queue values between 0 and 7
};

// Queue that tells who's turn it is, who is next, and who was the one before
struct player_queue{
    struct player data[8];    // Queue array that holds a maximum of 9 // * * * * * * SHould it be 7? * * * * 
    int front;                // Pointer to the beginning of the queue array
    int rear;                 // Pointer to the ending of the queue array 
};

// * * * * * * Where is Max of array defined? * * * * * * * 
struct player_queue create_player_queue();                         //to create a queue in another function call using { struct queuec* [the name of your queue] = create_queuec }
bool isEmpty_player_queue (struct player_queue varq);              // Function that checks if the player_queue is empty
bool isFull_player_queue (struct player_queue varq);               // Function that checks if the player_queue is full
void enqueue_player (struct player_queue* varq, struct player);    // Function that adds a player to the player_queue
void dequeue_player (struct player_queue* varq);                   // Function that deletes a player from the player_queue
void peek_player (struct player_queue varq);                       // Function that prints out the name ofthe current player playing 


// Function to create and initialize the player_queue (varq)
struct player_queue create_player_queue() {
	struct player_queue varq;                        // Player queue will be called varq
	varq.front = -1;                                 // Pointer to the beginning is equal to -1 (empty)
	varq.rear = -1;                                  // Pointer to the ending is equal to -1 (empty) 
	memset(varq.data, '\0', sizeof(varq.data));      // Data of the player queue is equal to NULL (NULL)
	return varq;                                     // Return player queue (varq)
}

// Function to check if the player queue is empty
bool isEmpty_player_queue (struct player_queue* varq){
	return (varq->rear==-1);                            // If the pointer to the ending is -1, return true
}

// Function to check if the player queue is full 
bool isFull_player_queue (struct player_queue* varq){
	if ( ( (varq->front !=0) && (varq->rear==varq->front-1)  ) || ( (varq->front==0) && (varq->rear==MAX-1) ) ) {
		return ( 1==1 );   // Return true if it is full
	}
	else
		return ( 0==1 );   // Otherwise return false
}

// Function to add player to the player queue (varq)
void enqueue_player (struct player_queue* varq, struct player new_player) {
    
    // if the player queue is full return
	if( isFull_player_queue (varq) ) 
		return;
		
	// Else if the queue is empty 
    else if(varq->front==-1 && varq->rear==-1)
        {
        // Set front and rear pointer equal to 0
        varq->front=varq->rear=0;
        
        // Set player the new player's data at the begining of the queue array
        varq->data[0] = new_player;
        }
        
    // Else if the rear is at last element of array and front is not at the beginning of array    
    else if(varq->rear==MAX-1 && varq->front!=0)
        {
        // Make the rear go around to the beginning of array
        varq->rear=0;
        // Set the new player here
        varq->data[varq->rear] = new_player;
        }
        
    else
        {
        // Else increment the rear pointer by one
        varq->rear++;
        // Set the new player here 
        varq->data[varq->rear] = new_player;
        }
}

// Function to delete player from the player queue (varq)
void dequeue_player (struct player_queue* varq) {
    
    // If the player queue is empty return
	if (isEmpty_player_queue(varq))
		return;
		
	// Else if the front pointer and the rear poiner are equal (only one element in the player queue)	
	else if(varq->front!=-1 && varq->front==varq->rear) {
	    
	    // Make front and rear pointers equal to -1 (empty player queue)
		varq->front=varq->rear=-1;
	}
	
	
	else {
	    // If front pointer is at the end of the array
		if(varq->front==MAX-1) {
		    
		    // Make the front go around to the beginning of array
			varq->front=0;
		}
		
		else {
		    // Else increment the front pointer by one
			varq->front++;
		}
	}
}

// Function to print the current player that is playing right now 
void peek_player (struct player_queue varq) {
    
    // If the player queue is empty 
    if( isEmpty_player_queue(&varq))
        {
        // Print that no one is playing and return
        cout <<"\n No One is Playing" <<endl;
        return;
        }
        
    else
        {
        // Else go to the front pointer of the player queue, and print
        // the name of the player whose turn it is right now
        cout << varq.data[varq.front].name;
        // return
		return;
        }
}

// Function that simulates the rolling of the five dices
void shuffle_array(int* arr, int size) {
    // The player starts with 5 dices, so we will get 5 random numbers
	for (int a = 0; a < 5; a++) {
	    
	    // * * * * * * What happens here * * * * * *
		for (int i = 0; i < size ; i++){
			srand(time(0));
			int var = rand()%size;
			int temp = *(arr+i);
			*(arr+i )= *(arr+var);
			*(arr+var) = temp;
		}
	}
}

// Function that creates the characters for each player and assigns
// Max Health and bullets. Also initializes other elements of character (dices, arros, roles, and beer)
struct player create_player(int char_num, int role_num) {
    
    // Structure to create a temporary character player 
	struct player temp_player;
	//temp_player.name=(char*)malloc(20,sizeof(char));
	// Assign the name of the character 
	temp_player.name = char_num;
	
	// If your character "Paul Regret" or "El Gringo"
	if(char_num == 14 || char_num == 4){
	    // Assign three bullets to your character
		temp_player.bullets = 3;
	}
	
	// Else 
	else 
	    // Assign four bullets to your character
		temp_player.bullets = 4;
		
	// If the current player is the sheriff
	if (role_num == 1) {
	    // Assign 2 more bullets to this player
		temp_player.bullets = temp_player.bullets + 2;
	}
	
	// Assign the role to the character (sheriff, deputy, renegade, and outlaw)
	temp_player.role = role_num;
	// Assign number of dices the character has 
	temp_player.dice = 6;
	// Assign number of arrow the character has
	temp_player.arrows = 0;
	// Assign number of beer the character has 
	temp_player.beer = 0;
	// Assign Max Health of the character 
	temp_player.hand_size = temp_player.bullets;
	
	// Return the struct of the player created
	return temp_player;
}

// Function that prints out the information of the current character player
// (Character's name, dices, max health and remaining health)
void print_player(struct player var_player) {
    
    // Character's name
	cout << "\n\nNext Player: ";
	switch (var_player.name) {
	    // if name is 1 then print out "Bart Cassidy"
		case 1: {
			cout << "Bart Cassidy" ;
			break;
		}
		
		// if name is 2 then print out "Black Jack"
		case 2:{
			cout << "Black Jack";
			break;
		}
		
		// if name is 3 then print out "Calamity Janet"
		case 3:{
			cout << "Calamity Janet";
			break;
		}
		
		// if name is 4 then print out "El Gringo"
		case 4:{
			cout << "El Gringo";
			break;
		}
		
		// if name is 5 then print out "Jesse Jones"
		case 5:{
			cout << "Jesse Jones";
			break;
		}
		
		// if name is 6 then print out "Jourdonnais"
		case 6:{
			cout << "Jourdonnais ";
			break;
		}
		
		// if name is 7 then print out "Pedro Ramirez"
		case 7:{
			cout << "Pedro Ramirez";
			break;
		}
		
		// if name is 8 then print out "Rose Doolan"
		case 8:{
			cout << "Rose Doolan";
			break;
		}
		
		// if name is 9 then print out "Sid Ketchum"
		case 9:{
			cout <<"Sid Ketchum";
			break;
		}
		
		// if name is 10 then print out "Slab the Killer"
		case 10:{
			cout << "Slab the Killer ";
			break;
		}
		
		// if name is 11 then print out "Suzy Lafayette"
		case 11:{
			cout << "Suzy Lafayette";
			break;
		}
		
		// if name is 12 then print out "Vulture Sam"
		case 12:{
			cout <<"Vulture Sam ";
			break;
		}
		
		// if name is 13 then print out "Willy the Kid"
		case 13:{
			cout << "Willy the Kid";
			break;
		}
		// if name is 14 then print out "Paul Regret"
		case 14:{
			cout <<"Paul Regret";
			break;
		}
		
		// if name is 15 then print out "Lucky Duke"
		case 15:{
			cout << "Lucky Duke";
			break;
		}
		
		// if name is 16 then print out "Kit Carlson"
		case 16:{
			cout << "Kit Carlson";
			break;
		}
	}
	
	// If the current player is the sheriff, print it out
	if (var_player.role == 1)	cout << "\nSHERRIF";
	
	//  * * * * * * What is the purpose here * * * * * * 
	if (var_player.dice) cout << "\nDice: "<<  var_player.dice;
	if (var_player.hand_size)cout << "\nHand Size: " <<  var_player.hand_size;
	if (var_player.bullets)cout << "\nBullets: " <<  var_player.bullets;
}

// Function that goes through the player_queue and uses the print_player to print each of the
// character's info one by one 
void print_recursive(struct player_queue line_up,int current, int first) {
    
    // Calls the print_player function to print out the character's relevant info 
	print_player(line_up.data[current]);
	
	// If the next character is the first one that was printed out then return
	if (line_up.data[current].next == first) {
		return;
	}
	
	// Call this function recursively by pointing to the next character 
	print_recursive(line_up,line_up.data[current].next,first);
}

// Functions that creates the characters and assigns their roles
struct player_queue create_line_up(int number_of_players) {
    
    // Create array that represents the characters that a player can be 
	int char_num_arr[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}, k; 
	
	    // Call shuffle_array to shuffle the char_num_arr
		shuffle_array(char_num_arr,16);
		
	// Create a stack that hold the roles characters can take
	// (Sherrif, deputy, outlaw, and renegade)
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



