
struct stack dice_sheriff(int current, bool* gatlin, bool* dynamite, int* beer){
	int rolled_dynamite_sheriff, rolled_gatlin_sheriff, reroll = 0;
	
	while ( roll_again && reroll < 3) {
		struct stack* dice_stack_sheriff = create_stack();
		for(int i=0;i<lineup.data[current].dice;i++) {
			int dice_roll=rand()%6;
			
			if (dice_roll == 0){ // dynamite same for everyone
				rolled_dynamite++;
				lineup.data.[current].dice--;
				if (rolled_dynamite >= 3) {
					dynamite = ( 1 == 1);
					return *dice_stack_sheriff;
				}
			}
			
			if (dice_roll == 1 || dice_roll == 2) { // Shots
				push(dice_roll, dice_stack)
			}
			
			if (dice_roll == 3) { //Beer 
				if (lineup.data[current].bullets != lineup.data[current].hand_size) {
					*beer++;
					lineup.data[current].dice--;
				}
			}
			
			if (dice_roll == 4) { //Gatlin
					rolled_gatlin_sheriff++;
				}
			
			if (dice_roll == 5) { //Arrow
				if (pull_arrows) {
					indian_attack(line_up, line_up.front, line_up.front.next)
				}
				else {
					pop(arrows);
					lineup.data[current].arrows++;
				}
			}
			
		}
		if(rolled_gatlin >= 2 && lineup[current].dice >= 3) { // If they are close to or get a gatlin gun
			if (rolled gatlin >= 3) {
				*gatlin = ( 1 == 1);
				lineup.data[current].dice = lineup.data[current].dice - 3;
			}
		}
		else {
			rolled_gatlin = 0;
		}
		
		reroll++;
	}
	return *dice_stack_sheriff;
}

struct stack dice_deputy(int current, bool* gatlin, bool* dynamite, int* beer){
	int rolled_dynamite_deputy, rolled_gatlin_deputy;
	
	while ( roll_again && reroll < 4) {
		struct stack* dice_stack_deputy = create_stack();
		for(int i=0;i<lineup.data[current].dice;i++) {
			int dice_roll=rand()%6;
			
			if (dice_roll == 0){ // dynamite
				rolled_dynamite++;
				lineup.data.[current].dice--;
				if (rolled_dynamite_deputy >= 3) {
					dynamite = ( 1 == 1);
					return *dice_stack_deputy;
				}
			}
			
			if (dice_roll == 1 || dice_roll == 2) { // Shots
				push(dice_roll, dice_stack)
			}
			
			if (dice_roll == 3) { //Beer 
				if (savethesheriff || lineup.data[current].bullets < 4) {
					*beer++;
					lineup.data[current].dice--;
				}
			}
			
			if (dice_roll == 4) { //Gatlin
				if(!savethesheriff) {
					rolled_gatlin_deputy++;
				}
			}
			
			if (dice_roll == 5) { //Arrow
				if (pull_arrows) {
					indian_attack(line_up, line_up.front, line_up.front.next)
				}
				else {
					pop(arrows);
					lineup.data[current].arrows++;
				}
			}
			
		}
		if(rolled_gatlin >= 2 && lineup[current].dice >= 3) { // If they are close to or get a gatlin gun
			if (rolled gatlin >= 3) {
				*gatlin = ( 1 == 1);
				lineup.data[current].dice = lineup.data[current].dice - 3;
			}
		}
		else {
			rolled_gatlin = 0;
		}
		
		reroll++;
	}
}

struct stack dice_outlaw(int current, bool* gatlin, bool* dynamite, int* beer){
	int rolled_dynamite_outlaw, rolled_gatlin_outlaw;
	
	while ( roll_again && reroll < 4) {
		struct stack* dice_stack_outlaw = create_stack();
		for(int i=0;i<lineup.data[current].dice;i++) {
			int dice_roll=rand()%6;
			
			if (dice_roll == 0){ // dynamite
				rolled_dynamite_outlaw++;
				lineup.data.[current].dice--;
				if (rolled_dynamite_outlaw >= 3) {
					dynamite = ( 1 == 1);
					return *dice_stack_outlaw;
				}
			}
			
			if (dice_roll == 1 || dice_roll == 2) { // Shots
				push(dice_roll, dice_stack)
			}
			
			if (dice_roll == 3) { //Beer 
				if( (lineup.data[current].bullets + *beer) < (lineup.data[current].hand_size)) {
					*beer++;
					lineup.data[current].dice--;
				}
			}
			
			if (dice_roll == 4) { //Gatlin
				rolled_gatlin_outlaw++;
			}
			
			if (dice_roll == 5) { //Arrow
				if (pull_arrows) {
					indian_attack(line_up, line_up.front, line_up.front.next)
				}
				else {
					pop(arrows);
					lineup.data[current].arrows++;
				}
			}
			
		}
		if(rolled_gatlin >= 2 && lineup[current].dice >= 3) { // If they are close to or get a gatlin gun
			if (rolled gatlin >= 3) {
				*gatlin = ( 1 == 1);
				lineup.data[current].dice = lineup.data[current].dice - 3;
			}
		}
		else {
			rolled_gatlin = 0;
		}
		
		reroll++;
	}
}

bool save_the_sheriff() {
	if (lineup.data[lineup.front].bullets < (lineup.data[lineup.front].hand_size/2));
		return (1 == 1);
}

bool pull_arrow(int current) {
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

void indian_attack(int current, int start) {
	for (int i = 0 ; i < line_up.data[current].arrows; i ++) {
		lineup.data[current].bullets--;
		if (lineup.data[current].bullets == 0) {
			death(lineup.data[current]);
		}
	}
	if (lineup.data[current].next == start) {
		return;
	}
	indian_attack(lineup.data[current].next,start);
}
