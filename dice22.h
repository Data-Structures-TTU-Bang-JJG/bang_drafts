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

void print_dice(int dice){
	if (dice == 0) {
		cout << "[ D ]  ";
	}
	if (dice == 1) {
		cout << "[ 1 ]  ";
	}
	if (dice == 2) {
		cout << "[ 2 ]  ";
	}
	if (dice == 3) {
		cout << "[ B ]  ";
	}
	if (dice == 4) {
		cout << "[ G ]  ";
	}
	if (dice == 5) {
		cout << "[ A ]  ";
	}
}

void print_final_dice(int gatlin, int dynamite, int beer) {
	for(int i=0 ; i < gatlin ; i++){
		cout << "[ G ]  ";
	}
	for(int i=0 ; i < dynamite ; i++){
		cout << "[ D ]  ";
	}
	for(int i=0 ; i < beer ; i++){
		cout << "[ B ]  ";
	}
}

struct stack dice_sheriff(int current, bool* gatlin, bool* dynamite, int* beer){
	struct stack* sheriff_shot= create_stack();
	struct stack final_shot = dice_sheriff_recursive(current, gatlin, dynamite, beer, sheriff_shot);
	for(int i=0; i<sheriff_shot->top;i++) {
		int temp = pop(sheriff_shot);
		push(temp,&final_shot);
		cout << "[ " << temp << " ]  ";
	}
	return final_shot;
}

struct stack dice_sheriff_recursive(int current, bool* gatlin, bool* dynamite, int* beer, struct stack* sheriff_shot){
	int rolled_dynamite_sheriff=0, rolled_gatlin_sheriff=0, reroll = 1;
	struct stack* dice_stack_sheriff = create_stack();
	
	
	while ( (lineup.data[current].dice  > 0)  && reroll < 4) {
		cout << "Roll " << reroll << ": ";
		
		dice_stack_sheriff->top = 0;
		
		for(int i=0;i<lineup.data[current].dice;i++) {
			int dice_roll=rand()%6;
			
			print_dice(dice_roll);
			
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
				else {
					pop(arrows);
					lineup.data[current].arrows++;
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
	
	print_final_dice(rolled_gatlin_sheriff, rolled_dynamite_sheriff, *beer);
	
	return *dice_stack_sheriff;
}

struct stack dice_deputy(int current, bool* gatlin, bool* dynamite, int* beer) {
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
		cout << "Roll " << reroll << ": ";
		
		dice_stack_deputy->top = 0;
		
		for(int i=0;i<lineup.data[current].dice;i++) {
			int dice_roll=rand()%6;
			
			print_dice(dice_roll);
			
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
					indian_attack(lineup.front, lineup.front);
				}
				else {
					pop(arrows);
					lineup.data[current].arrows++;
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
	
	print_final_dice(rolled_gatlin_deputy, rolled_dynamite_deputy, *beer);
	
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
		cout << "\nRoll " << reroll << ": ";
		
		dice_stack_outlaw->top = 0;
		for(int i=0;i<lineup.data[current].dice;i++) {
			int dice_roll=rand()%6;
			
			print_dice(dice_roll);        
			
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
					indian_attack(lineup.front, lineup.front);
				}
				else {
					pop(arrows);
					lineup.data[current].arrows++;
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
	
	print_final_dice(rolled_gatlin_outlaw, rolled_dynamite_outlaw, *beer);
	
	return (*dice_stack_outlaw);
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
		lineup.data[current].arrows++;
		return ( 0 == 1 );
	}
} 

void fill_arrows(){
	for (int i = 0 ; i <= 9 ; i++) {
		push(1,arrows);
	}
	return;
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
