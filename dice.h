struct stack dice(int current, int* dynimite, int* gatlin) ;
struct stack* roll (struct player* var_player, int *gatlin, int *dynimite);

void turn(int current){
	int gatlin = 0;
	int dynimite = 0;
	bool gatlin_shot = 0;
	bool sthes = 0;
	lineup.data[current].dice = 5;
	
	/*if (lineup.data[current].role == 0) { // deputy
		savethesherrif();
	}*/
	struct player var_player;
	struct stack shots = dice(current,&dynimite,&gatlin);
	if (dynimite >= 3) return;
}

/*pop_all(){
	
}*/

struct stack dice(int current, int* dynimite, int* gatlin) {
	struct stack* dice_stack = create_stack();
	int dice_roll, rolled_gatlin;
	dice_stack = roll(&lineup.data[current],gatlin,dynimite);
	
	//What happens to gatlin dice
	if (rolled_gatlin >= 3){
		*gatlin = (1==1);
		lineup.data[current].dice = lineup.data[current].dice -3;
	}
	else if (rolled_gatlin == 2) {
		rolled_gatlin = 2;
		lineup.data[current].dice = lineup.data[current].dice - 2;
	}
	
	// Dynimite(
	if (*dynimite >= 3){
		lineup.data[current].bullets --;
		return *dice_stack;
	}
	
	if ((lineup.data[current].dice == 0) ) { // If there are no more rollable dice
		return *dice_stack;
	}
	
	else {
		//pop_all();
		dice_stack = roll(&lineup.data[current],gatlin,dynimite);
	}
	return *dice_stack;
}

struct stack* roll (struct player* var_player, int *gatlin, int *dynimite){
	struct stack* dice_stack = create_stack();
	// Don't change any bullets in this function because if there are 3 dynimite the action is null
	
	
	//roll the number of avalible dice
	for(int i=0;i<var_player->dice;i++) {
		int dice_roll=rand()%6; // randomizes dice roll
		
		if (dice_roll == 0){ //dynimite  RULE
			*dynimite++;
			lineup.data[current].dice --;
		}
		
		else if (dice_roll == 4){ //gatlin  
			*gatlin++;
		}
		
		else if (dice_roll == 5){ //arrows RULE
			if (pull_arrows) {
				indian_attack(line_up, line_up.front, line_up.front.next)
			}
			else {
				pop(arrows);
				lineup.data[current].arrows++;
			}
		}
		
		else if (dice == 3){ {// beer STRATEGY
			if (lineup.data[current].role == 0)
				savethesheriff(lineup.data[current],gatlin,dynimite);
			else if (lineup.data[current].bullets < 4) 
				var_player->beer++;
				var_player->dice --;
			}
		}
		
		else { // shots
			push(dice_roll, dice_stack);
		}
	}
	return dice_stack;
}

savethesheriff(){ // will return weither the sherif is in danger and tell the deputys what to do.
}

bool pull_arrow(struct player* var_player) {
	if (isEmpty(arrows)) {
		fill_arrows();
		return (1 == 1);
	}
	else {
		var_player.arrows++;
		return ( 0 == 1 );
	}
} 

void fill_arrows(){
	for (int i = 0 ; i < 9 ; i++) {
		push(1,arrows);
	}
}

void indian_attack(struct player_queue line_up, int current, int start) {
	for (int i = 0 ; i < line_up.data[current].arrows; i ++) {
		var_player.bullets--;
	}
	if (line_up.data[current].next == start) {
		return;
	}
	indian_attack(line_up,line_up.data[current].next,start);
}
