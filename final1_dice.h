struct stack dice_sheriff(int current, bool* gatlin, bool* dynamite, int* beer);
struct stack dice_sheriff_recursive(int current, bool* gatlin, bool* dynamite, int* beer, struct stack* sheriff_shot);
struct stack dice_deputy(int current, bool* gatlin, bool* dynamite, int* beer);
struct stack dice_deputy_recursive(int current, bool* gatlin, bool* dynamite, int* beer, struct stack* sheriff_shot);
struct stack dice_outlaw(int current, bool* gatlin, bool* dynamite, int* beer);
struct stack dice_outlaw_recursive(int current, bool* gatlin, bool* dynamite, int* beer, struct stack* sheriff_shot);
bool save_the_sheriff();
bool pull_arrow(int current);
void fill_arrows();
void indian_attack(int current, int start);

struct stack dice_sheriff(int current, bool* gatlin, bool* dynamite, int* beer){
	struct stack* sheriff_shot= create_stack();
	struct stack final_shot = dice_sheriff_recursive(current, gatlin, dynamite, beer, sheriff_shot);
	while(!isEmpty((sheriff_shot))) {
		push(pop(sheriff_shot),&final_shot);
	}
	return final_shot;
}

struct stack dice_sheriff_recursive(int current, bool* gatlin, bool* dynamite, int* beer, struct stack* sheriff_shot){
	int rolled_dynamite_sheriff=0, rolled_gatlin_sheriff=0, reroll = 0;
	struct stack* dice_stack_sheriff = create_stack();
	
	while ( (lineup.data[current].dice  > 0)  && reroll < 3) {
		while(!isEmpty(dice_stack_sheriff)) {
			pop(dice_stack_sheriff);
		}
		
		for(int i=0;i<lineup.data[current].dice;i++) {
			int dice_roll=rand()%6;
			
			if (dice_roll == 0){ // dynamite same for everyone
				rolled_dynamite_sheriff++;
				lineup.data[current].dice--;
				if (rolled_dynamite_sheriff >= 3) {
					*dynamite = ( 1 == 1);
					return *dice_stack_sheriff;
				}
			}
			
			if (dice_roll == 1 || dice_roll == 2) { // Shots
				// if the sheriff is either two before or two next
				if (dice_roll == 2 && ( (suspicion[lineup.data[lineup.data[current].next].next] < -3) || (suspicion[lineup.data[lineup.data[current].previous].previous] < -3) ) ) {
					push(dice_roll, sheriff_shot);
					lineup.data[current].dice--;
				}
				// if the next or previous is the sheriff
				else if  (dice_roll == 1 && ( (suspicion[lineup.data[current].next]) < -3 || (suspicion[lineup.data[current].previous] < -3) ) ) {
					push(dice_roll, sheriff_shot);
					lineup.data[current].dice--;
				}
				
				else {
					push(dice_roll, dice_stack_sheriff);
				}
			}
			
			else if (dice_roll == 3) { //Beer 
				if (lineup.data[current].bullets != lineup.data[current].hand_size) {
					*beer++;
					lineup.data[current].dice--;
				}
			}
			
			else if (dice_roll == 4) { //Gatlin
					rolled_gatlin_sheriff++;
				}
			
			else if (dice_roll == 5) { //Arrow
				if (pull_arrow(current)) {
					cout << "\nIndians Attack" ;
					indian_attack(lineup.front, lineup.front);
				}
			}
			
		}
		if( (rolled_gatlin_sheriff >= 2) && (lineup.data[current].dice >= 3) ) { // If they are close to or get a gatlin gun
			if (rolled_gatlin_sheriff >= 3) {
				*gatlin = ( 1 == 1);
				lineup.data[current].dice = lineup.data[current].dice - 3;
			}
		}
		else {
			rolled_gatlin_sheriff = 0;
		}
		
		reroll++;
	}
	return *dice_stack_sheriff;
}

struct stack dice_deputy(int current, bool* gatlin, bool* dynamite, int* beer){
	struct stack* sheriff_shot= create_stack();
	struct stack final_shot = dice_deputy_recursive(current, gatlin, dynamite, beer, sheriff_shot);
	while(!isEmpty((sheriff_shot))) {
		push(pop(sheriff_shot),&final_shot);
	}
	return final_shot;
}

struct stack dice_deputy_recursive(int current, bool* gatlin, bool* dynamite, int* beer, struct stack* sheriff_shot){
	int rolled_dynamite_deputy=0, rolled_gatlin_deputy=0, reroll=0;
	struct stack* dice_stack_deputy = create_stack();
	
	while ( (lineup.data[current].dice  > 0) && reroll < 3) {
		while(!isEmpty(dice_stack_deputy)) {
			pop(dice_stack_deputy);
		}
		
		for(int i=0;i<lineup.data[current].dice;i++) {
			int dice_roll=rand()%6;
			
			if (dice_roll == 0){ // dynamite
				rolled_dynamite_deputy++;
				lineup.data[current].dice--;
				if (rolled_dynamite_deputy >= 3) {
					*dynamite = ( 1 == 1);
					return *dice_stack_deputy;
				}
			}
			
			if (dice_roll == 1 || dice_roll == 2) { // Shots
				// if the sheriff is either two before or two next
				if (dice_roll == 2 && ( (suspicion[lineup.data[lineup.data[current].next].next] < -3) || (suspicion[lineup.data[lineup.data[current].previous].previous] < -3) ) ) {
					push(dice_roll, sheriff_shot);
					lineup.data[current].dice--;
				}
				// if the next or previous is the sheriff
				else if  (dice_roll == 1 && ( (suspicion[lineup.data[current].next]) < -3 || (suspicion[lineup.data[current].previous] < -3) ) ) {
					push(dice_roll, sheriff_shot);
					lineup.data[current].dice--;
				}
				
				else {
					push(dice_roll, dice_stack_deputy);
				}
			}
			
			if (dice_roll == 3) { //Beer 
				if (save_the_sheriff() || lineup.data[current].bullets < 4) {
					*beer++;
					lineup.data[current].dice--;
				}
			}
			
			if (dice_roll == 4) { //Gatlin
				if(!save_the_sheriff()) {
					rolled_gatlin_deputy++;
				}
			}
			
			if (dice_roll == 5) { //Arrow
				if (pull_arrow(current)) {
					cout << "\nIndians Attack" ;
					indian_attack(lineup.front, lineup.front);
				}
			}
			
		}
		if(rolled_gatlin_deputy >= 2 && lineup.data[current].dice >= 3) { // If they are close to or get a gatlin gun
			if (rolled_gatlin_deputy >= 3) {
				*gatlin = ( 1 == 1);
				lineup.data[current].dice = lineup.data[current].dice - 3;
			}
		}
		else {
			rolled_gatlin_deputy = 0;
		}
		
		reroll++;
	}
	return (*dice_stack_deputy);
}

struct stack dice_outlaw(int current, bool* gatlin, bool* dynamite, int* beer){
	struct stack* sheriff_shot= create_stack();
	struct stack final_shot = dice_outlaw_recursive(current, gatlin, dynamite, beer, sheriff_shot);
	while(!isEmpty((sheriff_shot))) {
		push(pop(sheriff_shot),&final_shot);
	}
	return final_shot;
}
	
struct stack dice_outlaw_recursive(int current, bool* gatlin, bool* dynamite, int* beer, struct stack* sheriff_shot){
	int rolled_dynamite_outlaw=0, rolled_gatlin_outlaw=0, reroll = 0;
	struct stack* dice_stack_outlaw = create_stack();
	
	while ( (lineup.data[current].dice  > 0) && reroll < 3) {
		while(!isEmpty(dice_stack_outlaw)) {
			pop(dice_stack_outlaw);
		}
		for(int i=0;i<lineup.data[current].dice;i++) {
			int dice_roll=rand()%6;
			
			if (dice_roll == 0){ // dynamite
				rolled_dynamite_outlaw++;
				lineup.data[current].dice--;
				if (rolled_dynamite_outlaw >= 3) {
					*dynamite = ( 1 == 1);
					return *dice_stack_outlaw;
				}
			}
			
			if (dice_roll == 1 || dice_roll == 2) { // Shots
				// if the sheriff is either two before or two next
				if (dice_roll == 2 && ( (suspicion[lineup.data[lineup.data[current].next].next] > 3) || (suspicion[lineup.data[lineup.data[current].previous].previous] > 3) ) ) {
					push(dice_roll, sheriff_shot);
					lineup.data[current].dice--;
				}
				// if the next or previous is the sheriff
				else if  (dice_roll == 1 && ( (suspicion[lineup.data[current].next]) > 3 || (suspicion[lineup.data[current].previous] > 3) ) ) {
					push(dice_roll, sheriff_shot);
					lineup.data[current].dice--;
				}
				
				else {
					push(dice_roll, dice_stack_outlaw);
				}
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
				if (pull_arrow(current)) {
					cout << "\nIndians Attack" ;
					indian_attack(lineup.front, lineup.front);
				}
			}
			
		}
		if((rolled_gatlin_outlaw >= 2) && lineup.data[current].dice >= 3) { // If they are close to or get a gatlin gun
			if (rolled_gatlin_outlaw >= 3) {
				*gatlin = ( 1 == 1);
				lineup.data[current].dice = lineup.data[current].dice - 3;
			}
		}
		else {
			rolled_gatlin_outlaw = 0;
		}
		
		reroll++;
	}
	return (*dice_stack_outlaw);
}

bool save_the_sheriff() {
	if (lineup.data[lineup.front].bullets < (lineup.data[lineup.front].hand_size/2));
		return (1 == 1);
}

bool pull_arrow(int current) {
	if (arrows == 0) {
		arrows = 9;
		return (1 == 1);
	}
	else {
		lineup.data[current].arrows++;
		arrows--;
		return ( 0 == 1 );
	}
} 

void indian_attack(int current, int start) {
	while (lineup.data[current].arrows > 0) {
		lineup.data[current].bullets--;
		lineup.data[current].arrows--;
	}
	
	if (lineup.data[current].bullets == 0) {
			death(current);
			if (current == start) {
				start = lineup.data[current].next;
			}
		}
	
	if (lineup.data[current].next == start || current == lineup.data[start].previous) {
		return;
	}
	indian_attack(lineup.data[current].next,start);
}
