/******************************************************************************
AUTHORS: 
    Grace Gomez
    Jose E. Sosa Andrade
    Jerel Navarrette
FILENAME: 
    Project "Bang!!! The Boardgame" - Part 2
    
SPECIFICATION:
    Project simulates the boardgame. It includes different participants in the boardgame,
    it assigns the values of the characters (life point, roles, number of dices, etc). 
    The program simulates the game and provides outputs of what happens every turn and 
    keeps going until someone wins
CLASS:
    CS 2413 Data Structures Section 002
*******************************************************************************/

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <iostream>
#include <fstream> 
#include <string.h>

#define MAX 20

using namespace std;

// Array that holds integers representing the suspicion of each player
int suspicion[8];

#include "final2_stacks.h"
//#include "queue.h"
#include "final2_player.h"

// Max number of arrows for an indian attack to happen
int arrows = 9;
struct player_queue lineup;

// Checks if anyone has reached health of 0 or less, changes their status to "dead" if true
void check_Death(int current, int first);
// Checks "dead" status and skips these players if they are, also check if any winning
// condition has happened
void death (int current);
// Shoots players within range to the right or left of the current player
void shooting(stack dice_stack,int range, int current);
// This function checks if sherriff is the only player alive besides the renegade
// because renegade will act differently 
void check_Death(int current, int first, int count);
// Damages everyone except the player that called this function
int renegade_Attitude(int current, int first, int characterRole);
// Simulates what happens every turn, and print the results
void damage_AllPlayers(int current, int first);
// Checks if any of the winning conditions has happened
void turn(int current);
// Function for good guys to shoot rivals (shoot guys with low suspicion)
void goodGuys_shooting(stack dice_stack, int range, int current);
// Function for bad guys to shoot rivals (shoot guys with high suspicion)
void badGuys_shooting(stack dice_stack, int range, int current);
// Function the check if any condition for winning has been met
bool end_game(int current);
// Function to clear suspicion of the renegade
bool clear_suspicion(int current);

#include "final2_dice.h"

/*{ Library functions table of content 
stacks.h
create_stack();
push(int, stack)
pop(stack)
isEmpty(stacks);
isFull(stack)
player.h
struct player_queue create_player_queue();  //to create a queue in another function call using { struct queuec* [the name of your queue] = create_queuec }
bool isEmpty_player_queue (struct player_queue varq);
bool isFull_player_queue (struct player_queue varq);
void enqueue_player (struct player_queue* varq, struct player);
void dequeue_player (struct player_queue* varq);
void peek_player (struct player_queue varq);
dice.h
stack dice_sheriff(int current, bool* gatlin, bool* dynamite, int* beer);
stack dice_deputy(int current, bool* gatlin, bool* dynamite, int* beer);
stack dice_outlaw(int current, bool* gatlin, bool* dynamite, int* beer);
bool save_the_sheriff();
bool pull_arrow(int current);
void fill_arrows();
void indian_attack(int current, int start); )*/

int main(int argc, char **argv)
{
	freopen ("myfile.txt","w",stdout);
	printf ("This sentence is redirected to a file.");
	// Sets up the system that generates random numbers
	srand(time(0));
	// Randomizes the number of players from 4 to 8
	//int players = (rand()%5+4);
	int players = 8;
	// Creates the lineup of players
	lineup = create_line_up(players);
	//print_recursive(lineup,lineup.front,lineup.front);
	turn(lineup.front);
	//fclose (stdout);
	print_recursive(lineup,0,0,false);
	cout << "help";
	return 0;
}//End Main

// Jose Sosa
// 11/13/19
// Turn function

// NAME: Death
// INPUT PARAMETERS: int current (represents the index number of the player
// whose turn it is right now)
// OUTPUT: none (void)
// PURPOSE: To skip players that are dead, and to check if any winning condition has happened
void death (int current){
	// Used to store the reference to the next player
	int the_next = 	lineup.data[current].next;
	// Used to store the reference to the previous player
	int the_previous = 	lineup.data[current].previous;
	
	// If the health of the player is 0 or less
	if (lineup.data[current].bullets <= 0) {
		// Makes it so that next and previous will skip the dead player 
		lineup.data[the_next].previous = the_previous;
		lineup.data[the_previous].next = the_next;
		
		// Returns the arrows of the players that just died
		arrows = lineup.data[current].arrows + arrows;
		// Sets the player to dead
		lineup.data[current].dead = true;
		// Skip two lines
		cout << "\n\n****";
		// Prints the info of the current player (who died)
		print_player_name(lineup.data[current].name);
		cout << " has DIED *******\n****ROLE: " ;
		// Depending on the role number it will print if it was Deputy, Sheriff
		// Outlaw or Renegade
		if (lineup.data[current].role == 0) cout << "Deputy *****\n";
		else if (lineup.data[current].role == 1) cout << "Sheriff *****\n";
		else if (lineup.data[current].role == 2) cout << "Outlaw *****\n";
		else if (lineup.data[current].role == 3) cout << "Renegade *****\n";
		
	}
		// Call end game function to check if any winning condition has happened
		end_game(lineup.data[current].previous);
}


// Function that simulates every turn, calling dices function depending of the role of the current player, and after the dices have been
// roled takes the correct action (increase health, shoot someone, checks arrows, and check if anyone has died). After this is done, it points 
// to the next player whose turn it is. 

// NAME: Turn
// INPUT PARAMETERS: int current (represents the index number of the player
// whose turn it is right now)
// OUTPUT: none (void)
// PURPOSE: Simulate every turn, calling dices depending of the role of the current player, and after
// the dices have been rolled takes the correct action (increase health, shoot someone, checks arrows, 
// and check if anyone has died). After this is done, it points to the next player whose turn it is.
void turn(int current){

	bool gatling = false;      // Initialize gatling boolean as false
    bool dynamite = false;     // Initialize dynamite boolean as false
    int beer = 0;              // Initialize beer int as 0
    
    // If it is the sheriff's turn and he is still alive
	if (current == 0 && lineup.data[0].dead == false) {
	    // Print what every die means
		cout << "//////// Top of the lineup /////////" << endl;
		cout << "//////// [ D ] is Dynimite /////////" << endl;
		cout << "//////// [ G ] is Gatlin /////////" << endl;
		cout << "//////// [ B ] is Beer /////////" << endl;
		cout << "//////// [ A ] is Arrow /////////" << endl;
		cout << "//////// [ 1 ] is shooting one to the left or to the right /////////" << endl;
		cout << "//////// [ 2 ] is shooting two to the left or to the right /////////" << endl;
		// Print the current player line-up (circular queue)
		print_recursive(lineup,current,current,false);
	}
    // Reset number of dices to 5 for the current player
    lineup.data[current].dice = 5;
    lineup.data[current].dice = 5;
		
        // Announce whose turn it is (Print out info)
        cout << "\n\nNEW TURN" << endl;
        print_player(lineup.data[current]);
        
        // Check players role to call the correct dice function
        // if the current player is the sherriff
        if(lineup.data[current].role == 1)
        {
            // Call correct dice function according to the player's role
            stack dice_stack = dice_sheriff(current, &gatling, &dynamite, &beer);
			
			// Announce the results once all the dices had been rolled
			// If player got three dynamites
			if(dynamite == true)
			{
				// Reduce player's life by one
				lineup.data[current].bullets--;
				// Print it out
				cout << "\n\tYou rolled three dynamites!!! You lost one life point";
			}
			
			else
			{
				// If player got three gatlin guns
				if(gatling == true)
				{
					// Call function to damage everyone (-1 health)
					damage_AllPlayers(lineup.data[current].next, current);
					cout << "\n\tYou rolled three Gatlin Guns!!! Shoot everyone once";
				
					arrows = arrows + lineup.data[current].arrows;
					// Dispose of any arrows character has
					lineup.data[current].arrows = 0;
					cout << "\n\t\tYour arrows were dropped!!!";
				}
				// Check if player has any beer that he kept
				if(beer == 0)
				{
					cout << "\n\tYou don't have any beer!!!";
				}
				//no beer
				else
				{
					// Else if player kept beer 
					for(int i = 0; i <= beer; i++)
					{
						// Increase their life by the number of beers they kept
						if (lineup.data[current].bullets < lineup.data[current].hand_size)
						lineup.data[current].bullets++;
					}
					
					//Print it out
					cout << "\n\tYou have " << beer << " beers!!! Your life now, bullets: " << lineup.data[current].bullets;
				}
				
				// Check if the dice stack is empty (to shoot player to the right or the left)
				if(isEmpty(&dice_stack) == false)
				{
					// Call shooting function
					 goodGuys_shooting(dice_stack, pop(&dice_stack), current);
				}
		
				// Anounce if you have any arrows
				if(lineup.data[current].arrows > 0)
				{
					cout << "\n\tYou have " << lineup.data[current].arrows << " arrows!!!";
				}
				
				else
				{
					// Else if you do not have any print it out
					cout << "\n\tYou did not get any arrows this turn!!!";
				}
				
				// Check if the dice stack is empty (to shoot player to the right or the left)
				if(isEmpty(&dice_stack) == false)
				{
					// Call shooting function
					goodGuys_shooting(dice_stack,pop(&dice_stack), current);
				}
				
				else
				{
					// Else if no shooting happens, print it out
					cout << "\n\tNo one was shot!!!";
				}
			}
			// Check if anyone is dead, and change that status if needed
			check_Death(current, current,0);
			// Check if only renegades and the sheriff are playing
		  	while(clear_suspicion(current) == false)
		    	{
		   		// If only renegades and sheriff are playing, clear the
				// suspicion number of the renegades
				clear_suspicion(current);
		    	}
			//Checking if any winning conditions have happened
			 end_game(current);
			
			// Announce the turn has finished
			cout << "\n\tThe turn has ended!!!";
        }
        
        // if the current player is a deputy
        else if(lineup.data[current].role == 0)
        {
            // Call correct dice function according to the player's role
            stack dice_stack = dice_deputy(current, &gatling, &dynamite, &beer);
            {
                // Announce the results once all the dices had been rolled
                // If player got three dynamites
                if(dynamite == true)
                {
                    // Reduce player's life by one
                    lineup.data[current].bullets--;
                    // Print it out
                    cout << "\n\tYou rolled three dynamites!!! You lost one life point";
                }
                
                else
                {
                    // If player got three gatlin guns
                    if(gatling == true)
                    {
                        // Call function to damage everyone (-1 health)
                        damage_AllPlayers(lineup.data[current].next, current);
                        cout << "\n\tYou rolled three Gatlin Guns!!! Shoot everyone once";
                    
                        // Put number of arrows players has back into the pile
                       arrows = arrows + lineup.data[current].arrows;
					   
                        lineup.data[current].arrows = 0;
                        cout << "\n\tYour arrows were dropped!!!" ;
					}
					// Check if player has any beer that he kept
                     if(beer == 0)
                        {
                            cout << "\n\tYou don't have any beer!!!" ;
                        }
                        
                     else
                      {
						while ( (lineup.data[0].bullets < (lineup.data[0].hand_size/2)) && (beer > 0)) {
							cout << "\n\t+1 bullet for the Sheriff";
							lineup.data[current].bullets++;
							beer--;
							suspicion[current]++;
						}
						// Else if player kept beer 
						for(int i = 0; i <= beer; i++)
						{
							if (lineup.data[current].bullets < lineup.data[current].hand_size)// Increase their life by the number of beers they kept
							lineup.data[current].bullets++;
						}
						cout << "\n\tYou have " << beer << " beers!!! Your life now, bullets: " << lineup.data[current].bullets;
					}
                        
                        // Check if the dice stack is empty (to shoot player to the right or the left)
                        if(isEmpty(&dice_stack) == false)
                        {
                            // Call shooting function
                            goodGuys_shooting(dice_stack,pop(&dice_stack), current);
                        }
                        
                        else
                        {
                            // Else if no shooting happens, print it out
                            cout << "\n\tNo one was shot!!!";
                        }
                        // Anounce if you have any arrows
                        if(lineup.data[current].arrows > 0)
                        {
                            cout << "\n\tYou got " << lineup.data[current].arrows << " arrows!!!" ;
                        }
                        
                        else
                        {
                            // Else if you do not have any print it out
                            cout << "\n\tYou did not get any arrows this turn!!!";
                        }
				}
                // Check if anyone is dead, and change that status if needed
                check_Death(current, current,0);
                // Check if only renegades and the sheriff are playing
		while(clear_suspicion(current) == false)
		{
		    	// If only renegades and sheriff are playing, clear the
			// suspicion number of the renegades
		    	clear_suspicion(current);
	        }
                // Announce the turn has finished
                cout << "\nThe turn has ended!!!";
            }
        }
        
        // if the current player is an outlaw
        else if(lineup.data[current].role == 2)
        {
            // Call correct dice function according to the player's role
            stack dice_stack = dice_outlaw(current, &gatling, &dynamite, &beer);
            {
                // Announce the results once all the dices had been rolled
                // If player got three dynamites
                if(dynamite == true)
                {
                    // Reduce player's life by one
                    lineup.data[current].bullets--;
                    // Print it out
                    cout << "\n\tYou rolled three dynamites!!! You lost one life point";
                }
                
                else
                {
                    // If player got three gatlin guns
                    if(gatling == true)
                    {
                        // Call function to damage everyone (-1 health)
                        damage_AllPlayers(lineup.data[current].next, current);
                        cout << "\n\tYou rolled three Gatlin Guns!!! Shoot everyone once";
                    
                        // Push number of arrows players has back into the pile
                        arrows = arrows + lineup.data[current].arrows;
                        // Dispose of any arrows character has
                        lineup.data[current].arrows = 0;
                        cout << "\n\tYour arrows were dropped!!!";
						}
                        // Check if player has any beer that he kept
					if(beer == 0)
					{
						cout << "\n\tYou don't have any beer!!!";
					}
					
					else
					{
						// Else if player kept beer 
						for(int i = 0; i <= beer; i++)
						{
							if (lineup.data[current].bullets < lineup.data[current].hand_size) // Increase their life by the number of beers they kept
							lineup.data[current].bullets++;
						}
						//Print it out
						cout << "\n\tYou have " << beer << " beers!!! Your life now, bullets: " << lineup.data[current].bullets;
					}
					
					// Check if the dice stack is empty (to shoot player to the right or the left)
					if(isEmpty(&dice_stack) == false)
					{
						// Call shooting function
						badGuys_shooting(dice_stack,pop(&dice_stack), current);
					}
					
					else
					{
						// Else if no shooting happens, print it out
						cout << "\n\tNo one was shot!!!";
					}
		
				
					// Anounce if you have any arrows
					if(lineup.data[current].arrows > 0)
					{
						cout << "\n\tYou now have " << lineup.data[current].arrows << " arrows!!!";
					}
					
					else
					{
						// Else if you do not have any print it out
						cout << "\n\tYou did not get any arrows this turn!!!";
					}
					
					// Check if player has any beer that he kept
					if(beer == 0)
					{
						cout << "\n\tYou don't have any beer!!!";
					}
				}
                // Check if anyone is dead, and change that status if needed
                check_Death(current, current,0);
		// Check if only renegades and the sheriff are playing
		while(clear_suspicion(current) == false)
	        {
	         	// If only renegades and sheriff are playing, clear the
			// suspicion number of the renegades
		    	clear_suspicion(current);
	        }
                // Announce the turn has finished
                cout << "\n\tThe turn has ended!!!";
            }
        }
        
        // if the current player is a renegade
        else if(lineup.data[current].role == 3)
        {
            // Store the value of the roles of the characters combined
            int renegade_Status = renegade_Attitude(current, current, 0);
            
            // If the status is equal to 4 (renegade is 3 and sherriff 1)
            // The renegade will act as an outlaw (only the dice_sheriff and the renegade are alive) 
            if(renegade_Status == 4)
            {
                // Call correct dice function according to the player's role
                stack dice_stack = dice_outlaw(current, &gatling, &dynamite, &beer);
                {
                    // Announce the results once all the dices had been rolled
                    // If player got three dynamites
                    if(dynamite == true)
                    {
                        // Reduce player's life by one
                        lineup.data[current].bullets--;
                        // Print it out
                        cout << "\n\tYou rolled three dynamites!!! You lost one life point";
                    }
                
                    else
                    {
                        // If player got three gatlin guns
                        if(gatling == true)
                        {
                            // Call function to damage everyone (-1 health)
                            damage_AllPlayers(lineup.data[current].next, current);
                            cout << "\n\tYou rolled three Gatlin Guns!!! Shoot everyone once";
                    
                            // Push number of arrows players has back into the stack
                            arrows = arrows + lineup.data[current].arrows;
                            // Dispose of any arrows character has
                            lineup.data[current].arrows = 0;
                            cout << "\n\tYour arrows were dropped!!!";
                        }
                            // Check if player has any beer that he kept
                            if(beer == 0)
                            {
                                cout << "\n\tYou don't have any beer!!!";
                            }
                        
                            else
                            {
                                // Else if player kept beer 
                                for(int i = 0; i <= beer; i++)
                                {
                                    if (lineup.data[current].bullets < lineup.data[current].hand_size) // Increase their life by the number of beers they kept
                                    lineup.data[current].bullets++;
                                }
                            
                                // Print it out
                                cout << "\n\tYou have " << beer << " beers!!! Your life now, bullets: " << lineup.data[current].bullets;
                            }
                        
                            // Check if the dice stack is empty (to shoot player to the right or the left)
                            if(isEmpty(&dice_stack) == false)
                            {
                                // Call shooting function
                                badGuys_shooting(dice_stack,pop(&dice_stack), current);
                            }
                        
                            else
                            {
                                // Else if no shooting happens, print it out
                                cout << "\n\tNo one was shot!!!";
                            }
                        // Prints the number of arrows the person has. 
							cout << "\n\tYou got " << lineup.data[current].arrows << " arrows!!!";
                                // Print it out
                        }
                    }
                    // Check if anyone is dead, and change that status if needed
                    check_Death(current, current,0);
		    // Check if only renegades and the sheriff are playing
		    while(clear_suspicion(current) == false)
		    {
		    	// If only renegades and sheriff are playing, clear the
			// suspicion number of the renegades
		    	clear_suspicion(current);
		    }
                    // Announce the turn has finished
                    cout << "\n\tThe turn has ended!!!" << endl;
                }
            
            // Else the renegade will act as a deputy (Renegade must protect the sherriff)
			else
			{
				// Call correct dice function according to the player's role
				stack dice_stack = dice_deputy(current, &gatling, &dynamite, &beer);
				{
					// Announce the results once all the dices had been rolled
					// If player got three dynamites
					if(dynamite == true)
					{
						// Reduce player's life by one
						lineup.data[current].bullets--;
						// Print it out
						cout << "\n\tYou rolled three dynamites!!! You lost one life point";
					}
					
					else
					{
						// If player got three gatlin guns
						if(gatling == true)
						{
							// Call function to damage everyone (-1 health)
							damage_AllPlayers(lineup.data[current].next, current);
							cout << "\n\tYou rolled three Gatlin Guns!!! Shoot everyone once";
						
							// Push number of arrows players has back into the stack
							arrows = arrows + lineup.data[current].arrows;
							// Dispose of any arrows character has
							lineup.data[current].arrows = 0;
							cout << "\n\tYour arrows were dropped!!!" ;
						}
						// Check if player has any beer that he kept
						 if(beer == 0)
							{
								cout << "\n\tYou don't have any beer!!!" ;
							}
							
						 else
						  {
						    // Else player kept beer while the sheriff's health is less than half
							while (lineup.data[0].bullets < (lineup.data[0].hand_size/2)) {
							    // Print that player will give beer
								cout << "\n\t+1 bullet for the Sheriff";
								lineup.data[current].bullets++;
								// Decrease the number of beers by one
								beer--;
								// Increase suspicion (player is becoming good guy)
								suspicion[current]++;
							}
							// Else if player kept beer 
							for(int i = 0; i <= beer; i++)
							{
								if (lineup.data[current].bullets < lineup.data[current].hand_size) // Increase their life by the number of beers they kept
								lineup.data[current].bullets++;
							}
							cout << "\n\tYou have " << beer << " beers!!! Your life now, bullets: " << lineup.data[current].bullets;
						}
							
							// Check if the dice stack is empty (to shoot player to the right or the left)
							if(isEmpty(&dice_stack) == false)
							{
								// Call shooting function
								goodGuys_shooting(dice_stack,pop(&dice_stack), current);
							}
							// Anounce if you have any arrows
							if(lineup.data[current].arrows > 0)
							{
								cout << "\n\tYou got " << lineup.data[current].arrows << " arrows!!!" ;
							}
							
							else
							{
								// Else if you do not have any print it out
								cout << "\n\tYou did not get any arrows this turn!!!";
							}
					}
					// Check if anyone is dead, and change that status if needed
					check_Death(current, current,0);
					// Check if only renegades and the sheriff are playing
		                        while(clear_suspicion(current) == false)
		    			{
		    				// If only renegades and sheriff are playing, clear the
						// suspicion number of the renegades
		    				clear_suspicion(current);
		    			}
					// Announce the turn has finished
					cout << "\n\tThe turn has ended!!!";
				}
			}
		}
    
	check_Death(current,current,0);
    // Point to the next player whose turn it is
    turn(lineup.data[current].next);
	
} // End turn

// NAME: damage_AllPlayers
// INPUT PARAMETERS: int current (represents the index number of the player
// whose turn it is to receive damage), int first (hold the index number of the player that
// activated the gattling gun)
// OUTPUT: none (void)
// PURPOSE: Function to traverse the current circular player queue and reduce the health of 
// everyone by one (except the player that got gatling gun)
void damage_AllPlayers(int current, int first){
    // Reduce the life of the current player by one
    lineup.data[current].bullets--;
    
    // If the first player dies for any reason
	while(lineup.data[first].dead == true) {
	    // Change the first player to the one after him
		first = lineup.data[first].next;
	}
    // If the next character is the first 
    if(lineup.data[current].next == first)
    {
        // Decrease suspicion of the player that activated gatling gun
		suspicion[first] = suspicion[first] - 1;
        // Return
        return;
    }
    
    // Call this function recursively by pointing to the next character
    damage_AllPlayers(lineup.data[current].next, first);
} // End damage_AllPlayers

// NAME: renegade_Attitude
// INPUT PARAMETERS: int current (represents the index number of the player
// whose turn it is), int first (hold the index number of the player that
// was the first on the queue), int characterRoleSum (summation of the numerical
// value of the roles of the players)
// OUTPUT: characterRoleSum (summation of the roles so far)
// PURPOSE: Function that traverses the current circular player queue and adds up all the 
// character's role. This is to check if the sherriff is the only player alive
int renegade_Attitude(int current, int first, int characterRoleSum){
    // The  value will be equal to the summation of the character's role so far 
	if (lineup.data[0].dead == true) {
		return -1;
	}
	
	// If the first player dies for any reason
	while(lineup.data[first].dead == true) {
	    // Change the first player to the one after him
		current = first = lineup.data[first].next;
	}
	// Add up the role of the current player to the summation so far
    characterRoleSum = lineup.data[current].role + characterRoleSum;
    
    // If the next character is the first 
    if(lineup.data[current].next == first)
    {
        // Return the summation of the character's role so far
        return characterRoleSum;
    }
    
    // Call this function recursively by pointing to the next character
    renegade_Attitude(lineup.data[current].next, first, characterRoleSum);
} // End renegade_Attitude

// NAME: check_Death
// INPUT PARAMETERS: int current (represents the index number of the player
// whose turn it is), int first (hold the index number of the player that
// was the first on the queue), int count (integer that hold number of players
// counted so far)
// OUTPUT: none
// PURPOSE: Function to traverse the current circular player queue and depending of 
// the health of the player, they will change the "dead" status
void check_Death(int current, int first, int count){
    // If the life of the current player is equal or less than 0
    if(lineup.data[current].bullets <= 0)
    {
        // Change the status of player to "dead"
        //lineup.data[current].dead == true;
		death(current);
	}
    
    // If the next character is the first 
    if(lineup.data[current].next == first || count > 8)
    {
        // Return
        return;
    }
    
    // Check if any condition for winning the game has happened
	end_game(current);
	
    check_Death(lineup.data[current].next, first, ++count);
}  // End check_Death

// NAME: goodGuys_shooting
// INPUT PARAMETERS: dice_stack (points to the stack holding any shooting dices the player got), int 
// range (the value of how far will the current player shoot), int current (the index value of the 
// player doing the shooting)
// OUTPUT: none
// PURPOSE: Function used by the "good guys" to "shoot" the "bad guys" within 
// the range specified by the dices
void goodGuys_shooting(stack dice_stack, int range, int current){
        // Check what is the range
        // If range of shooting is 1
        if(range == 1)
        {
            
            // If the suspicion of the player on the left is lower than the one 
            // on the right
            if(suspicion[lineup.data[current].next] < suspicion[lineup.data[current].previous])
            {
                // Shoot the player to the left (-1 health)
                lineup.data[lineup.data[current].next].bullets--; 
				cout << "\n*";
				// Print out the name of the player shot
                print_player_name(lineup.data[lineup.data[current].next].name);
				cout << " was shot! Bullets: " << lineup.data[lineup.data[current].next].bullets;
		// Player shot a "bad guy", increase suspicion
		suspicion[current] = suspicion[current] + 1; 
            }
            
            // Else if the suspicion of the player on the right is lower than 
            // the one on the left
            else if(suspicion[lineup.data[current].next] >= suspicion[lineup.data[current].previous])
            {
                // Shoot the player to the right (-1 health)
                lineup.data[lineup.data[current].previous].bullets--;
				cout << "\n*";
				// Print out the name of the player shot
                print_player_name(lineup.data[lineup.data[current].previous].name);
				cout << " was shot! Bullets: " << lineup.data[lineup.data[current].previous].bullets;
		// Player shot a "bad guy", increase suspicion
		suspicion[current] = suspicion[current] + 1;
            }
        }
        
        // If range of shooting is 2
        if(range == 2)
        {
            // If the suspicion of the player two spaces to the left is lower than
            // the one two spaces to the right
            if(suspicion[lineup.data[lineup.data[current].next].next] < suspicion[lineup.data[lineup.data[current].previous].previous])
            {
                // Shoot the player two positions to the left (-1 health)
                lineup.data[lineup.data[lineup.data[current].next].next].bullets--;
				cout << "\n*";
				// Print out the name of the player shot
                print_player_name(lineup.data[lineup.data[lineup.data[current].next].next].name); 
				cout << " was shot! Bullets: " << lineup.data[lineup.data[lineup.data[current].next].next].bullets;
		// Player shot a "bad guy", increase suspicion
		suspicion[current] = suspicion[current] + 1;
            }
            
            // If the suspicion of the player two spaces to the right is lower than
            // the one two spaces to the left
            else if(suspicion[lineup.data[lineup.data[current].next].next] >= suspicion[lineup.data[lineup.data[current].previous].previous])
            {
                // Shoot the player two positions to the right (-1 health)
                lineup.data[lineup.data[lineup.data[current].previous].previous].bullets--;
				cout << "\n*";
				// Print out the name of the player shot
                print_player_name(lineup.data[lineup.data[lineup.data[current].previous].previous].name);
				cout << " was shot! Bullets: " << lineup.data[lineup.data[lineup.data[current].previous].previous].bullets;
		// Player shot a "bad guy", increase suspicion
		suspicion[current] = suspicion[current] + 1;
            }
        }
        
		check_Death(lineup.data[current].next,current,0);
        // Call this function recursively
		if (!isEmpty(&dice_stack)) {
			goodGuys_shooting(dice_stack,pop(&dice_stack), current);
		}
    
    // If the stack is empty then return
    return;
} // End goodGuys_shooting

// NAME: badGuys_shooting
// INPUT PARAMETERS: dice_stack (points to the stack holding any shooting dices the player got), int 
// range (the value of how far will the current player shoot), int current (the index value of the 
// player doing the shooting)
// OUTPUT: none
// PURPOSE: Function used by the "bad guys" to "shoot" the "good guys" within 
// the range specified by the dices
void badGuys_shooting(stack dice_stack, int range, int current){
        // Check what is the range
        // If range of shooting is 1
        if(range == 1)
        {
            
            // If the suspicion of the player on the left is higher than the one 
            // on the right
            if(suspicion[lineup.data[current].next] > suspicion[lineup.data[current].previous])
            {
                // Shoot the player to the left (-1 health)
                lineup.data[lineup.data[current].next].bullets--; 
				cout << "\n*";
				// Print out the name of the player shot
                print_player_name(lineup.data[lineup.data[current].next].name);
				cout << " was shot! Bullets: " << lineup.data[lineup.data[current].next].bullets;
	        // Player shot a "good guy", decrease suspicion
		suspicion[current] = suspicion[current] - 1;
            }
            
            // Else if the suspicion of the player on the right is higher than 
            // the one on the left
            else if(suspicion[lineup.data[current].next] <= suspicion[lineup.data[current].previous])
            {
                // Shoot the player to the right (-1 health)
                lineup.data[lineup.data[current].previous].bullets--;
				cout << "\n*";
				// Print out the name of the player shot
                print_player_name(lineup.data[lineup.data[current].previous].name);
				cout << " was shot! Bullets: " << lineup.data[lineup.data[current].previous].bullets;
		// Player shot a "good guy", decrease suspicion
		suspicion[current] = suspicion[current] - 1;
            }
        }
        
        // If range of shooting is 2
        if(range == 2)
        {
            // If the suspicion of the player two spaces to the left is higher than
            // the one two spaces to the right
            if(suspicion[lineup.data[lineup.data[current].next].next] > suspicion[lineup.data[lineup.data[current].previous].previous])
            {
                // Shoot the player two positions to the left (-1 health)
                lineup.data[lineup.data[lineup.data[current].next].next].bullets--;
				cout << "\n*";
				// Print out the name of the player shot
                print_player_name(lineup.data[lineup.data[lineup.data[current].next].next].name);
				cout << " was shot! Bullets: " << lineup.data[lineup.data[lineup.data[current].next].next].bullets;
			// Player shot a "good guy", decrease suspicion
				suspicion[current] = suspicion[current] - 1;
            }
            
            // If the suspicion of the player two spaces to the right is higher than
            // the one two spaces to the left
            else if(suspicion[lineup.data[lineup.data[current].next].next] <= suspicion[lineup.data[lineup.data[current].previous].previous])
            {
                // Shoot the player two positions to the right (-1 health)
                lineup.data[lineup.data[lineup.data[current].previous].previous].bullets--;
				cout << "\n*";
				// Print out the name of the player shot
                print_player_name(lineup.data[lineup.data[lineup.data[current].previous].previous].name);
				cout << " was shot! Bullets: " << lineup.data[lineup.data[lineup.data[current].previous].previous].bullets;
			// Player shot a "good guy", decrease suspicion
				suspicion[current] = suspicion[current] - 1;
            }
        }
        
		check_Death(lineup.data[current].next,current,0);
        // Call this function recursively
        if (!isEmpty(&dice_stack)) {
			badGuys_shooting(dice_stack,pop(&dice_stack), current);
		}
    
    // If the stack is empty then return
    return;
} // End badGuys_shooting

// Function to "shoot" the players within the range specified by the dices
/*void shooting(stack dice_stack, int range, int current){
    while(isEmpty(&dice_stack) == false)
    {
		 // Randomize an integer between 1 or 2
		int position = rand()%2 + 1;
		
        // Check what is the range
        // If range of shooting is 1
        if(range == 1)
        {
            
            // If postion is 1
            if(position == 1)
            {
                // Shoot the player to the left (-1 health)
                lineup.data[lineup.data[current].next].bullets--; 
				cout << "*";
                print_player_name(lineup.data[lineup.data[current].next].name); 
				cout << " was shot!!!" << endl;
            }
            
            // If position is 2
            if(position == 2)
            {
                // Shoot the player to the right (-1 health)
                lineup.data[lineup.data[current].previous].bullets--;
				cout << "*";
                print_player_name(lineup.data[lineup.data[current].previous].name);
				cout << " was shot!!!" << endl;
            }
        }
        
        // If range of shooting is 2
        if(range == 2)
        {
            
            // If position is 1
            if(position == 1)
            {
                // Shoot the player two positions to the left (-1 health)
                lineup.data[lineup.data[lineup.data[current].next].next].bullets--;
				cout << "*";
                print_player_name(lineup.data[lineup.data[lineup.data[current].next].next].name);
				cout << " was shot!!!" << endl;
            }
            
            // if position is 2
            if(position == 2)
            {
                // Shoot the player two positions to the right (-1 health)
                lineup.data[lineup.data[lineup.data[current].previous].previous].bullets--;
				cout << "*";
                print_player_name(lineup.data[lineup.data[lineup.data[current].previous].previous].name);
				cout  << " was shot !!!" << endl;
            }
        }
        
        // Call this function recursively
        shooting(dice_stack,pop(&dice_stack), current);
    }
    
    // If the stack is empty then return
    return;
} // End Shooting */

// NAME: clear_suspicion
// INPUT PARAMETERS:int current (the index value of the player doing the shooting)
// OUTPUT: True or False (if the renegade and the sheriff are the only players
// left, return true)
// PURPOSE: Check to see if reegades have switched from good guys to bad guys and clears supicion
bool clear_suspicion(int current){
    // If the summation of the current players is equal to 4 or 7 (only sheriff and renegades)
	if (renegade_Attitude(current,current,0) == 4 || renegade_Attitude(current,current,0)  == 7){
		for(int k=1; k<8; k++){
		    // Clear the suspicion of all the players left
			suspicion[k] = 0;
		}
	}
	return true;
}

// NAME: print_playerend
// INPUT PARAMETERS: the current player structure
// OUTPUT: none
// PURPOSE: Prints the character relevant info (name, role, arrows, and bullets)
void print_playerend(struct player var_player) {
    
    // Character's name
	if (var_player.role == 0) cout << "\nDEPUTY: ";
	else if (var_player.role == 1) cout << "\nSHERIFF: ";
	else if (var_player.role == 2) cout << "\nOUTLAW: ";
	else if (var_player.role == 3) cout << "\nRENEGADE: ";
	print_player_name(var_player.name);
	// If the current player is the sheriff, print it out
	
	if (var_player.arrows)cout << "  Arrows: " <<  var_player.arrows;
	if (var_player.bullets)cout << "  Bullets: " <<  var_player.bullets;
}

// NAME: print_endgame
// INPUT PARAMETERS: current line-up, int current (players whose turn it is)
// int first (player index of the first player to enter this function)
// OUTPUT: none
// PURPOSE: Prints all the players info when a character dies
void print_endgame (struct player_queue line_up,int current, int first, bool loop) {
	// If the next character is the first one that was printed out then return
	if (current == first) {
		if (loop == false) {
			loop = true;
		}
		else return;
	}
    // Calls the print_player function to print out the character's relevant info 
	if (line_up.data[current].dead == false)
		print_playerend(line_up.data[current]);
	
	while(line_up.data[first].dead == true) {
		first = line_up.data[first].next;
	}
	
	// Call this function recursively by pointing to the next character 
	print_endgame(line_up,line_up.data[current].next,first,loop);
}

// NAME: end_game
// INPUT PARAMETERS: int current (represents the 
// index number of the player whose turn it is right now)
// OUTPUT: a boolean that become true if a winning condition has happened
// PURPOSE: to check if any winning condition has happened, if it has then
// conditio becomes true, and the function ends the game
bool end_game(int current){
	// Used to store the summation of the character's role
	int living_status = renegade_Attitude(current, current, 0);
	// If living status is equal to 1 (Sheriff)
	if(living_status == 1) {
		// Print out that the sheriff and deputy have won
		 print_endgame(lineup,current,current,false);
		cout << "\n\nSheriff/Deputy wins\n\n";
		//fclose (stdout);
		exit(0);
	}
	// If the current player is an outlaw, and the current player is the only player left
	else if( (lineup.data[current].role == 2 && lineup.data[current].next == current ) ||  (living_status <= 0))  {
		 // Print out that the outlaws have won
		 print_endgame(lineup,current,current,false);
		cout << "\n\nOutlaws win\n\n";
		//fclose (stdout);
 		exit(0);
	}
	// If the current player is an renegade, ahd the current player is the only player left
	else if(lineup.data[current].role == 3 && lineup.data[current].next == current) {
		 // Print out that the renegades have won
		  print_endgame(lineup,current,current,false);
		cout << "\n\nRenegades win\n\n";
		//fclose (stdout);
		exit(0);
	}
	return (false);
}//End end_game