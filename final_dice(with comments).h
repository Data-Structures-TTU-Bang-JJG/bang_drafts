  
/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
Dice library that works together with the main program
Team members: Jerel Navarrette
              Grace Gomez
              Jose Sosa
* * * * * * * * * * * * * * * * * * * * * * * * * * * */
// 
stack dice_sheriff(int current, bool* gatlin, bool* dynamite, int* beer);
stack dice_sheriff_recursive(int current, bool* gatlin, bool* dynamite, int* beer, stack* sheriff_shot);
stack dice_deputy(int current, bool* gatlin, bool* dynamite, int* beer);
stack dice_deputy_recursive(int current, bool* gatlin, bool* dynamite, int* beer, stack* sheriff_shot);
stack dice_outlaw(int current, bool* gatlin, bool* dynamite, int* beer);
stack dice_outlaw_recursive(int current, bool* gatlin, bool* dynamite, int* beer, stack* sheriff_shot);
bool save_the_sheriff();
bool pull_arrow(int current);
void indian_attack(int current, int start);

// NAME: print_dice
// INPUT PARAMETERS: int dice (depending of the number on the dice, it will represent 
// one of the possible rolls you can get)
// OUTPUT: none (void)
// PURPOSE: To print what you get on the dice
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
} // End print_dice

// NAME: print_final_dice
// INPUT PARAMETERS: int gatling (number of gatling guns player rolled), int dynamite (number of dynamite
// the player rolled), int beer (number of beers player rolled)
// OUTPUT: none (void)
// PURPOSE: To print what the player got at the end of the three re-rolls
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
} // End print_final_dice

// NAME: dice_sheriff
// INPUT PARAMETERS: int current (index number representing whose turn it is),
// bool gatlin (if player gets three gatlin guns, return true), bool dynamite (if
// player gets three dynamites, return true), int beer (number of beers player kept)
// OUTPUT: stack dice_sheriff
// PURPOSE: Roll dice as a sheriff
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
} // End dice_sheriff

// NAME: dice_sheriff_recursive
// INPUT PARAMETERS: int current (index number representing whose turn it is),
// bool gatlin (if player gets three gatlin guns, return true), bool dynamite (if
// player gets three dynamites, return true), int beer (number of beers player kept)
// stack sheriff_shot (stack holding shooting the player can do)
// OUTPUT: stack dice_sheriff_recursive
// PURPOSE: Roll dice as a sheriff
stack dice_sheriff_recursive(int current, bool* gatlin, bool* dynamite, int* beer, stack* sheriff_shot){
    // Initialize values of dynamite, gatlin guns, and reroll
	int rolled_dynamite_sheriff=0, rolled_gatlin_sheriff=0, reroll = 1;
	bool rolled_two = false;
	
	// creates dice stack that will be returned
	stack* dice_stack_sheriff = create_stack();
	// while the character has rerolls, dice and has not rolled three of more dynamites they reroll
	while ( (dice  > 0)  && reroll < 4 && *dynamite == false) {
	    // Print out the number of rerolls 
		cout << "\nRoll " << reroll << ": ";
		// While the dice stack is not empty
		while(!isEmpty(dice_stack_sheriff)) {
		    // Keep "poping" dices for the player to roll
			pop(dice_stack_sheriff);
		}
		// Number of dices is equal to the player dices
		dice = lineup.data[current].dice;
		// For all the dices the player has
		for(int i=0;i<dice;i++) {
		    // Roll them to get a random number 
			int dice_roll=rand()%6;
			// Call print_dice to show what the player rolled
			print_dice(dice_roll);
			
			// If the player rolled dynamite
			if (dice_roll == 0){ // dynamite same for everyone
			    // Increase the dynamite counter by one 
				rolled_dynamite_sheriff++;
				// Reduce the number of dices by one 
				lineup.data[current].dice--;
				// If the player rolled three dynamites
				if (rolled_dynamite_sheriff >= 3) {
				    // Make the boolean checking that equal to "true"
					*dynamite = ( 1 == 1);
					// Return the dice stack 
					return *dice_stack_sheriff;
				}
			}
			
			// If the player rolled "1" or "2"
			if (dice_roll == 1 || dice_roll == 2) { // Shots
				// if the sheriff is either two before or two next
				if (dice_roll == 2 && ( (suspicion[lineup.data[lineup.data[current].next].next] < -3) || (suspicion[lineup.data[lineup.data[current].previous].previous] < -3) ) ) {
				    // Push the value of the roll into the stack 
					push(dice_roll, sheriff_shot);
					// Reduce the number of dices the player has
					lineup.data[current].dice--;
				}
				// if the next or previous is the sheriff
				else if  (dice_roll == 1 && ( (suspicion[lineup.data[current].next]) < -3 || (suspicion[lineup.data[current].previous] < -3) ) ) {
				    // Push the value of the roll into the stack
					push(dice_roll, sheriff_shot);
					// Reduce the number of dices the player has
					lineup.data[current].dice--;
				}
                				
				else {
				    // Push the value of the roll into the stack
					push(dice_roll, dice_stack_sheriff);
				}
			}
			
			// If the player rolled "3"
			else if (dice_roll == 3) { //Beer 
			    // If the players health is not at MAX, or they have three rerolls
				if ( (lineup.data[current].bullets != lineup.data[current].hand_size) || reroll == 3 ){
				    // Increase the beer integer by one 
					*beer = *beer + 1;
					// Reduce the number of dices the player has 
					lineup.data[current].dice--;
				}
			}
			
			// Else if the player rolled "4"
			else if (dice_roll == 4) { //Gatlin
			        // Increase the counter for the gatling gun
					rolled_gatlin_sheriff++;
				}
			// Else if the player rolled "5"
			else if (dice_roll == 5) { //Arrow
			    // And the condition for indian attack happens
				if (pull_arrow(current)) {
				    // Announce the indian attack
					cout << "\nIndians Attack" ;
					// Call the function to attack player with arrows
					indian_attack(lineup.front, lineup.front);
				}
			}
			
		}
		// If the player is close to getting a gattling gun
		if( (rolled_gatlin_sheriff >= 2) && (lineup.data[current].dice >= 3) ) {
		    // If the player rolled enough dices to get gatling gun
			if (rolled_gatlin_sheriff >= 3) {
			    // Set the boolean that checks that to "true"
				*gatlin = ( 1 == 1);
				// Reduce the number of dices the player has by 3
				lineup.data[current].dice = lineup.data[current].dice - 3;
				// If the player has not rolled two 
				if (rolled_two == false) {
				    // Then reduce the number of dices by 2
					lineup.data[current].dice = lineup.data[current].dice - 2;
				}
				cout << "3G<#";
			}
			else {
			    // If the player only rolled two
				rolled_two = true;
				// Reduce the number of dices by 2
				lineup.data[current].dice = lineup.data[current].dice - 2;
				cout << "2G<#";
			}
		}
		// If the reroll is not equal to 3
		else if (reroll != 3) {
		    // Then set gatling gun equal to zero (not enough to get gattling gun)
			rolled_gatlin_sheriff = 0;
		}
		// Increase reroll counter by one 
		reroll++;
	}
	// Call function to print the final results of the rolling 
	print_final_dice(rolled_gatlin_sheriff, rolled_dynamite_sheriff,*beer);
	// Return the dice stack
	return *dice_stack_sheriff;
} // End dice_sheriff_recursive

// NAME: dice_deputy
// INPUT PARAMETERS: int current (index number representing whose turn it is),
// bool gatlin (if player gets three gatlin guns, return true), bool dynamite (if
// player gets three dynamites, return true), int beer (number of beers player kept)
// OUTPUT: final_shot
// PURPOSE: Roll dice as a deputy
stack dice_deputy(int current, bool* gatlin, bool* dynamite, int* beer){
    // Create a stack to hold who is the deputy going to shoot
	stack* sheriff_shot= create_stack();
	// Call the dice_deputy_recursive function to get the results of deputy rolls
	stack final_shot = dice_deputy_recursive(current, gatlin, dynamite, beer, sheriff_shot);
	// Store the results on a temporal stack 
	stack temp = final_shot;
	// While the stack is not empty
	while(!isEmpty(&temp)) {
	    // Print the data on the stack
		cout << "[ " << peek(&temp) << " ]  ";
		// Once you print it "pop" the data
		pop(&temp);
	}
	// While the sheriff_shot stack is not empty
	while(!isEmpty(sheriff_shot)) {
	    // Print the data on the stack
		cout << "[ " << peek(sheriff_shot) << " ]  ";
		// Push the data on sheriff_shot stack into the final shot stack
		push(pop(sheriff_shot),&final_shot);
	}
	// Return final_shot stack
	return final_shot;
} // End dice_deputy

// NAME: dice_deputy_recursive
// INPUT PARAMETERS: int current (index number representing whose turn it is),
// bool gatlin (if player gets three gatlin guns, return true), bool dynamite (if
// player gets three dynamites, return true), int beer (number of beers player kept)
// stack sheriff_shot (stack holding shooting the player can do)
// OUTPUT: stack dice_stack_deputy
// PURPOSE: Roll dice as a deputy
stack dice_deputy_recursive(int current, bool* gatlin, bool* dynamite, int* beer, stack* sheriff_shot){
    // Initialize values of dynamite, gatlin guns, and reroll
	int rolled_dynamite_deputy=0, rolled_gatlin_deputy=0, reroll=1;
	bool rolled_two = false;
	// creates dice stack that will be returned
	stack* dice_stack_deputy = create_stack();
	
	    // Number of dices is equal to the player dices
		int dice = lineup.data[current].dice;
	// While the character has rerolls, dice and has not rolled three of more dynamites they reroll
	while ( (dice  > 0) && reroll < 4 && *dynamite == false) {
	    // Print out the number of rerolls 
		cout << "\nRoll " << reroll << ": ";
		// While the dice_stack_deputy is not empty
		while(!isEmpty(dice_stack_deputy)) {
		    // Keep poping whatever is on the stack 
			pop(dice_stack_deputy);
		}
		// Number of dices is equal to the player dices
		dice = lineup.data[current].dice;
		// For all the dices the player has
		for(int i=0;i<dice;i++) {
		    // Roll them to get a random number
			int dice_roll=rand()%6;
			// Print whatever the player has rolled
			print_dice(dice_roll);
			// If the player rolled dynamite
			if (dice_roll == 0){ // dynamite
			    // Increase the counter for dynamite
				rolled_dynamite_deputy++;
				// Reduce the number of dices the player has by one 
				lineup.data[current].dice--;
				// If the player rolls 3 or more dynamites
				if (rolled_dynamite_deputy >= 3) {
				    // Set the boolean that checks that to "true"
					*dynamite = ( 1 == 1);
					// Return the dice_stack_deputy
					return *dice_stack_deputy;
				}
			}
			
			// If the player rolls "1" or "2"
			if (dice_roll == 1 || dice_roll == 2) { // Shots
				// if the sheriff is either two before or two next
				if (dice_roll == 2 && ( (suspicion[lineup.data[lineup.data[current].next].next] < -3) || (suspicion[lineup.data[lineup.data[current].previous].previous] < -3) ) ) {
				    // Push the value of the shooting "range"
					push(dice_roll, sheriff_shot);
					// Reduce the number of dices the player has by one 
					lineup.data[current].dice--;
				}
				// if the next or previous is the sheriff
				else if  (dice_roll == 1 && ( (suspicion[lineup.data[current].next]) < -3 || (suspicion[lineup.data[current].previous] < -3) ) ) {
				    // Push the value of the shooting "range"
					push(dice_roll, sheriff_shot);
					// Reduce the number of dices the playe has by one
					lineup.data[current].dice--;
				}
				
				else {
				    // Else, just push the value player got 
					push(dice_roll, dice_stack_deputy);
				}
			}
			
			// If the player rolled "3"
			if (dice_roll == 3) { //Beer
			    // If "save_the_sheriff" is true or the players health is below 4 or they can reroll 3 times
				if ((save_the_sheriff() || lineup.data[current].bullets < 4) || reroll == 3) {
				    // Increase the beer integer by one
					*beer = *beer + 1;
					// Reduce the number of dices the player holds
					lineup.data[current].dice--;
				}
			}
			// If the player rolled "4"
			if (dice_roll == 4) { //Gatlin
			    // And "save_the_sheriff" if not true
				if(!save_the_sheriff()) {
				    // Increase the gatlin gun counter by one
					rolled_gatlin_deputy++;
				}
			}
			
			// If the player rolled "5"
			if (dice_roll == 5) { //Arrow
			    // And the condition for an indian attack is true
				if (pull_arrow(current)) {
				    // Print it out
					cout << "\nIndians Attack" ;
					// Call the function to damage players with arrows
					indian_attack(lineup.front, lineup.front);
				}
			}
			
		}
		
		// If they are close to get a gatlin gun
		if(rolled_gatlin_deputy >= 2 && lineup.data[current].dice >= 3) {
		    // If the player rolled 3 or more gatlin guns
			if (rolled_gatlin_deputy >= 3) {
			    // Set the boolean that checks that equal to true
				*gatlin = ( 1 == 1);
				// Reduce the number of dices the players holds by 3
				lineup.data[current].dice = lineup.data[current].dice - 3;
				// If the did not roll two 
				if (rolled_two == false) {
				    // Reduce the number of dices by 2
					lineup.data[current].dice = lineup.data[current].dice - 2;
				}
				cout << "3G<#";
			}
			else {
			    // If they did roll two 
				rolled_two = true;
				// Reduce the number of dices by 2
				lineup.data[current].dice = lineup.data[current].dice - 2;
				cout << "2G<#";
			}
		}
		// If the reroll is not equal to 3
		else if (reroll != 3 ){
		    // Then set gatling gun equal to zero (not enough to get gattling gun)
			rolled_gatlin_deputy = 0;
		}
		// Increase reroll counter by one 
		reroll++;
	}
	// Call function to print the final results of the rolling 
	print_final_dice(rolled_gatlin_deputy, rolled_dynamite_deputy, *beer);
	// Return the dice stack 
	return (*dice_stack_deputy);
} // End dice_deputy_recursive

// NAME: dice_outlaw
// INPUT PARAMETERS: int current (index number representing whose turn it is),
// bool gatlin (if player gets three gatlin guns, return true), bool dynamite (if
// player gets three dynamites, return true), int beer (number of beers player kept)
// OUTPUT: final_shot
// PURPOSE: Roll dice as an outlaw
stack dice_outlaw(int current, bool* gatlin, bool* dynamite, int* beer){
    // Create a stack to hold who is the deputy going to shoot
	stack* sheriff_shot= create_stack();
	// Call the dice_outlaw_recursive function to get the results of outlaw rolls
	stack final_shot = dice_outlaw_recursive(current, gatlin, dynamite, beer, sheriff_shot);
	// Store the results on a temporal stack 
	stack temp = final_shot;
	// While the stack is not empty
	while(!isEmpty(&temp)) {
	    // Print the data on the stack
		cout << "[ " << peek(&temp) << " ]  ";
		// Keep poping whatever is on the stack 
		pop(&temp);
	}
	// While the sheriff_shot stack is not empty
	while(!isEmpty(sheriff_shot)) {
	    // Print the data on the stack
		cout << "[ " << peek(sheriff_shot) << " ]  ";
		// Push the data on sheriff_shot stack into the final shot stack
		push(pop(sheriff_shot),&final_shot);
	}
	// Return final_shot stack
	return final_shot;
} // End dice_outlaw

// NAME: dice_outlaw_recursive
// INPUT PARAMETERS: int current (index number representing whose turn it is),
// bool gatlin (if player gets three gatlin guns, return true), bool dynamite (if
// player gets three dynamites, return true), int beer (number of beers player kept)
// stack sheriff_shot (stack holding shooting the player can do)
// OUTPUT: stack dice_stack_outlaw
// PURPOSE: Roll dice as an outlaw
stack dice_outlaw_recursive(int current, bool* gatlin, bool* dynamite, int* beer, stack* sheriff_shot){
    // Initialize values of dynamite, gatlin guns, and reroll
	int rolled_dynamite_outlaw=0, rolled_gatlin_outlaw=0, reroll = 1;
	bool rolled_two = false;
	// Create a dice stack that will be returned
	stack* dice_stack_outlaw = create_stack();
	// Set the number of dices equal to number of dices the player has
	int dice = lineup.data[current].dice;
	// While the character has rerolls, dice and has not rolled three of more dynamites they reroll
	while ( (dice  > 0) && reroll < 4 && *dynamite == false) {
	    // While the dice_stack_outlaw is not empty
		while(!isEmpty(dice_stack_outlaw)) {
		    // Keep poping whatever is on the stack
			pop(dice_stack_outlaw);
		}
		// Print out the number or re-rolls
		cout << "\nRoll " << reroll << ": ";
		// Set up the number of dices
		dice = lineup.data[current].dice;
		// For all the dices
		for(int i=0;i<dice;i++) {
		    // Roll them to get a random number
			int dice_roll=rand()%6;
			// Print out the result of the dice 
			print_dice(dice_roll);
			
			// If the player rolled dynamite
			if (dice_roll == 0){ // dynamite
			    // Increase the counter for dynamite
				rolled_dynamite_outlaw++;
				// Reduced the number of dices the player has by one
				lineup.data[current].dice--;
				// If the number of dynamites is 3 or more
				if (rolled_dynamite_outlaw >= 3) {
				    // Set the boolean that is checking that to "true"
					*dynamite = ( 1 == 1);
					// Return the dice stack
					return *dice_stack_outlaw;
				}
			}
			// If the player rolls "1" or "2"
			if (dice_roll == 1 || dice_roll == 2) { // Shots
				// if the sheriff is either two before or two next
				if (dice_roll == 2 && ( (suspicion[lineup.data[lineup.data[current].next].next] > 3) || (suspicion[lineup.data[lineup.data[current].previous].previous] > 3) ) ) {
				    // Push the shooting "range" into the stack
					push(2, sheriff_shot);
					// Reduce the number of dices the player has by one
					lineup.data[current].dice--;
				}
				// if the next or previous is the sheriff
				else if  (dice_roll == 1 && ( (suspicion[lineup.data[current].next]) > 3 || (suspicion[lineup.data[current].previous] > 3) ) ) {
				    // Push the shooting "range" into the stack
					push(1, sheriff_shot);
					// Reduce the number of dices the player has by one 
					lineup.data[current].dice--;
				}
				
				else {
				    // Else, just push the value players got 
					push(dice_roll, dice_stack_outlaw);
				}
			}
			
			// If player got "3"
			if (dice_roll == 3) { //Beer 
			    // And the number of beers player got is not goint to be over his max health or player still has 3 re-roll
				if( (lineup.data[current].bullets + *beer) < (lineup.data[current].hand_size) ||  (reroll == 3)) {
				    // Increase the beer integer of the player by one
					*beer = *beer + 1;
					// Reduce the number of dices the player has by one
					lineup.data[current].dice--;
				}
			}
			
			// If player rolled "4"
			if (dice_roll == 4) { //Gatlin
			    // Increase gatlin gun counter by one
				rolled_gatlin_outlaw++;
			}
			
			// If the player rolled "5"
			if (dice_roll == 5) { //Arrow
			    // And the condition for "indian attack" is met
				if (pull_arrow(current)) {
				    // Print it out to the players
					cout << "\nIndians Attack" ;
					// Call the function to damage all players with arrows
					indian_attack(lineup.front, lineup.front);
				}
			}
			
		}
		// If player is close to getting the gatlin gun
		if((rolled_gatlin_outlaw >= 2) && lineup.data[current].dice >= 3) { // If they are close to or get a gatlin gun
		    // If the player got 3 or more gatlin gun
			if (rolled_gatlin_outlaw>= 3) {
			    // Set the boolean for gattlin gun equal to "true"
				*gatlin = ( 1 == 1);
				// Reduce the number of dices of the player by one
				lineup.data[current].dice = lineup.data[current].dice - 1;
				// If the player did not roll two
				if (rolled_two == false) {
				    // Reduce the number of the dices the player has by two
					lineup.data[current].dice = lineup.data[current].dice - 2;
				}
				cout << "3G<#";
			}
			else {
			    // If the player did roll two
				rolled_two = true;
				// Reduce the number of the dices the player has by two
				lineup.data[current].dice = lineup.data[current].dice - 2;
				cout << "2G<#";
			}
		}
		// If the re-roll is not equal to 3
		else if (reroll != 3) {
		    // Then set gatling gun equal to zero (not enough to get gattling gun)
			rolled_gatlin_outlaw = 0;
		}
		// Increase the re-roll counter by one
		reroll++;
	}
	// Call function to print the final results of the rolling 
	print_final_dice(rolled_gatlin_outlaw, rolled_dynamite_outlaw, *beer);
	// Return the dice stack 
	return (*dice_stack_outlaw);
} // End dice_outlaw_recursive

// NAME: save_the_sheriff
// INPUT PARAMETERS: 
// OUTPUT: true or false (if the sheriff's life is lens than half his max, return true)
// PURPOSE: To let players know the sheriff needs help
bool save_the_sheriff() {
    // If the health of the sheriff is less than half his max health
	if (lineup.data[lineup.front].bullets < (lineup.data[lineup.front].hand_size/2));
	// Return true
		return (1 == 1);
} // End save_the_sheriff

// NAME: pull_arrow
// INPUT PARAMETERS: int current (index number representing the player whose turn it is 
// arrows are going to be pulled)
// OUTPUT: true or false 
// PURPOSE: To pull arrow of current player
bool pull_arrow(int current) {
    // If the arrows int is equal to 0
	if (arrows == 0) {
	    // Store the value of 9
		arrows = 9;
		// Return true
		return (1 == 1);
	}
	else {
	    // Else, increse the number of arrows a player has by one
		lineup.data[current].arrows++;
		// Decrease the arrow counter by one
		arrows--;
		// Return false
		return ( 0 == 1 );
	}
} // End pull_arrow 

// NAME: indian_attack
// INPUT PARAMETERS: int current (index number representing the player whose turn it is 
// to take damage depending on the number of arrows), int start (index representing the
// player that trigerred the indian attack)
// OUTPUT: none
// PURPOSE: To check number of arrow each player has and damage according to this number
void indian_attack(int current, int start) {
    // If the current player has arrows
	if (lineup.data[current].arrows > 0) {
		cout << endl;
		// Print out his name
		print_player_name(lineup.data[current].name);
		// And print how many times he is going to be hit
		cout << " was hit for " << lineup.data[current].arrows;
	}
	// While the player still has arrows
	while (lineup.data[current].arrows > 0) {
	    // Reduce the number of bullets of the player by one
		lineup.data[current].bullets--;
		// Reduce the number of arrows of the player by one
		lineup.data[current].arrows--;
	}
	// If the player died
	if (lineup.data[current].bullets == 0) {
	        // Call the death function to announce the player died
			death(current);
			// If the player that died was the first one on the queue
			// make the next player the new first
			if (current == start) {
				start = lineup.data[current].next;
			}
		}
	// If the next player is the one who trigerred the indian attack
	if (lineup.data[current].next == start || current == lineup.data[start].previous) {
	    // Return
		return;
	}
	// If not keep calling this function recursively
	indian_attack(lineup.data[current].next,start);
} // End indian_attack