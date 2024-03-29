stack dice_sheriff(int current, bool* gatlin, bool* dynamite, int* beer);
stack dice_sheriff_recursive(int current, bool* gatlin, bool* dynamite, int* beer, stack* sheriff_shot);
stack dice_deputy(int current, bool* gatlin, bool* dynamite, int* beer);
stack dice_deputy_recursive(int current, bool* gatlin, bool* dynamite, int* beer, stack* sheriff_shot);
stack dice_outlaw(int current, bool* gatlin, bool* dynamite, int* beer);
stack dice_outlaw_recursive(int current, bool* gatlin, bool* dynamite, int* beer, stack* sheriff_shot);
bool save_the_sheriff();
bool pull_arrow(int current);
void indian_attack(int current, int start);


// The print dice function prints the corresponding dice element with an integer
void print_dice(int dice){
	
	// Prints D for Dynimite
	if (dice == 0) {
		cout << "[ D ]  ";
	}
	// Prints 1 for a 1 bullseye
	else if (dice == 1) {
		cout << "[ 1 ]  ";
	}
	// Prints 2 for a 2 bullseye
	else if (dice == 2) {
		cout << "[ 2 ]  ";
	}
	// Prints B for Beer
	else if (dice == 3) {
		cout << "[ B ]  ";
	}
	// Prints G for Gatlin
	else if (dice == 4) {
		cout << "[ G ]  ";
	}
	// Prints A for Arrow
	else if (dice == 5) {
		cout << "[ A ]  ";
	}
}

//Print final dice prints the number of beer, Gatlin and dynamite a player has at the end of their turn
void print_final_dice(int gatlin, int dynamite, int beer) {
	cout << "\nFinal Dice: ";
	// Prints G for every Gatlin
	for(int i=0 ; i < gatlin ; i++){
		cout << "[ G ]  ";
	}
	// Prints D for every Dynamite
	for(int i=0 ; i < dynamite ; i++){
		cout << "[ D ]  ";
	}
	// Prints B for every Beer
	for(int i=0 ; i < beer ; i++){
		cout << "[ B ]  ";
	}
}

// Roll dice as a sheriff
stack dice_sheriff(int current, bool* gatlin, bool* dynamite, int* beer){
	
	// creates a stack for shot they want to take meaning a character in that index has a suspision of -3
	stack* sheriff_shot= create_stack();
	
	// returns a stack from dice_recursive sheriff which will also return the bool pointer gatlin and dynimite and the int pointer beer
	stack final_shot = dice_sheriff_recursive(current, gatlin, dynamite, beer, sheriff_shot);
	stack temp = final_shot;
	
	// prints out the shot dice returned in dice_sheriff_recursive to be output for the final roll
	while(!isEmpty(&temp)) {
		cout << "[ " << peek(&temp) << " ]  ";
		pop(&temp);
	}
	
	// combines the sheriff_shot and final_shot functions
	while(!isEmpty(sheriff_shot)) {
		cout << "[ " << peek(sheriff_shot) << " ]  ";
		push(pop(sheriff_shot),&final_shot);
	}
	
	// returns all shot dice in the final roll
	return final_shot;
}

stack dice_sheriff_recursive(int current, bool* gatlin, bool* dynamite, int* beer, stack* sheriff_shot){
	int rolled_dynamite_sheriff=0, rolled_gatlin_sheriff=0, reroll = 1;
	bool rolled_two = false;
	
	// creates dice stack that will be returned
	stack* dice_stack_sheriff = create_stack();
	// while the character has rerolls, dice and has not rolled three of more dynamites they reroll
	while ( (dice  > 0)  && reroll < 4 && *dynamite == false) {
		cout << "\nRoll " << reroll << ": ";
		while(!isEmpty(dice_stack_sheriff)) {
			pop(dice_stack_sheriff);
		}
		dice = lineup.data[current].dice;
		for(int i=0;i<dice;i++) {
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
				if ( (lineup.data[current].bullets != lineup.data[current].hand_size) || reroll == 3 ){
					*beer = *beer + 1;
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
				if (rolled_two == false) {
					lineup.data[current].dice = lineup.data[current].dice - 2;
				}
				cout << "3G<#";
			}
			else {
				rolled_two = true;
				lineup.data[current].dice = lineup.data[current].dice - 2;
				cout << "2G<#";
			}
		}
		else if (reroll != 3) {
			rolled_gatlin_sheriff = 0;
		}
		
		reroll++;
	}
	print_final_dice(rolled_gatlin_sheriff, rolled_dynamite_sheriff,*beer);
	return *dice_stack_sheriff;
}

stack dice_deputy(int current, bool* gatlin, bool* dynamite, int* beer){
	stack* sheriff_shot= create_stack();
	stack final_shot = dice_deputy_recursive(current, gatlin, dynamite, beer, sheriff_shot);
	stack temp = final_shot;
	while(!isEmpty(&temp)) {
		cout << "[ " << peek(&temp) << " ]  ";
		pop(&temp);
	}
	while(!isEmpty(sheriff_shot)) {
		cout << "[ " << peek(sheriff_shot) << " ]  ";
		push(pop(sheriff_shot),&final_shot);
	}
	return final_shot;
}

stack dice_deputy_recursive(int current, bool* gatlin, bool* dynamite, int* beer, stack* sheriff_shot){
	int rolled_dynamite_deputy=0, rolled_gatlin_deputy=0, reroll=1;
	bool rolled_two = false;
	stack* dice_stack_deputy = create_stack();
	
		int dice = lineup.data[current].dice;
	
	while ( (dice  > 0) && reroll < 4 && *dynamite == false) {
		cout << "\nRoll " << reroll << ": ";
		while(!isEmpty(dice_stack_deputy)) {
			pop(dice_stack_deputy);
		}
		dice = lineup.data[current].dice;
		for(int i=0;i<dice;i++) {
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
				if ((save_the_sheriff() || lineup.data[current].bullets < 4) || reroll == 3) {
					*beer = *beer + 1;
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
				if (rolled_two == false) {
					lineup.data[current].dice = lineup.data[current].dice - 2;
				}
				cout << "3G<#";
			}
			else {
				rolled_two = true;
				lineup.data[current].dice = lineup.data[current].dice - 2;
				cout << "2G<#";
			}
		}
		else if (reroll != 3 ){
			rolled_gatlin_deputy = 0;
		}
		
		reroll++;
	}
	print_final_dice(rolled_gatlin_deputy, rolled_dynamite_deputy, *beer);
	return (*dice_stack_deputy);
}

stack dice_outlaw(int current, bool* gatlin, bool* dynamite, int* beer){
	stack* sheriff_shot= create_stack();
	stack final_shot = dice_outlaw_recursive(current, gatlin, dynamite, beer, sheriff_shot);
	stack temp = final_shot;
	while(!isEmpty(&temp)) {
		cout << "[ " << peek(&temp) << " ]  ";
		pop(&temp);
	}
	while(!isEmpty(sheriff_shot)) {
		cout << "[ " << peek(sheriff_shot) << " ]  ";
		push(pop(sheriff_shot),&final_shot);
	}
	return final_shot;
}
	
stack dice_outlaw_recursive(int current, bool* gatlin, bool* dynamite, int* beer, stack* sheriff_shot){
	int rolled_dynamite_outlaw=0, rolled_gatlin_outlaw=0, reroll = 1;
	bool rolled_two = false;
	stack* dice_stack_outlaw = create_stack();
	
	int dice = lineup.data[current].dice;
	
	while ( (dice  > 0) && reroll < 4 && *dynamite == false) {
		while(!isEmpty(dice_stack_outlaw)) {
			pop(dice_stack_outlaw);
		}
		cout << "\nRoll " << reroll << ": ";
		dice = lineup.data[current].dice;
		for(int i=0;i<dice;i++) {
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
					push(2, sheriff_shot);
					lineup.data[current].dice--;
				}
				// if the next or previous is the sheriff
				else if  (dice_roll == 1 && ( (suspicion[lineup.data[current].next]) > 3 || (suspicion[lineup.data[current].previous] > 3) ) ) {
					push(1, sheriff_shot);
					lineup.data[current].dice--;
				}
				
				else {
					push(dice_roll, dice_stack_outlaw);
				}
			}
			
			if (dice_roll == 3) { //Beer 
				if( (lineup.data[current].bullets + *beer) < (lineup.data[current].hand_size) ||  (reroll == 3)) {
					*beer = *beer + 1;
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
			if (rolled_gatlin_outlaw>= 3) {
				*gatlin = ( 1 == 1);
				lineup.data[current].dice = lineup.data[current].dice - 1;
				if (rolled_two == false) {
					lineup.data[current].dice = lineup.data[current].dice - 2;
				}
				cout << "3G<#";
			}
			else {
				rolled_two = true;
				lineup.data[current].dice = lineup.data[current].dice - 2;
				cout << "2G<#";
			}
		}
		else if (reroll != 3) {
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
	if (lineup.data[current].arrows > 0) {
		cout << endl;
		print_player_name(lineup.data[current].name);
		cout << " was hit for " << lineup.data[current].arrows;
	}
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
