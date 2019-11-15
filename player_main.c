#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <iostream>
#include <fstream> 
#include <string.h>

#define MAX 50

using namespace std;

#include "stacks.h"
//#include "queue.h"
#include "player.h"

struct stack* arrows;
struct player_queue lineup;

#include "dice22.h"

void check_Death(int current, int first);
void death (int current);
void shooting(struct stack dice_stack,int range, int current);
void check_Death(int current, int first);
int renegade_Attitude(int current, int first, int characterRole);
void damage_AllPlayers(int current, int first);
void turn(int current);
bool end_game(int current);


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
struct stack dice_sheriff(int current, bool* gatlin, bool* dynamite, int* beer);
struct stack dice_deputy(int current, bool* gatlin, bool* dynamite, int* beer);
struct stack dice_outlaw(int current, bool* gatlin, bool* dynamite, int* beer);
bool save_the_sheriff();
bool pull_arrow(int current);
void fill_arrows();
void indian_attack(int current, int start); )*/

int main(int argc, char **argv)
{
	srand(time(0));
	int players = (rand()%5+4);
	lineup = create_line_up(players);
	struct player_queue debugg = lineup;
	arrows = create_stack();
	print_recursive(lineup,lineup.front,lineup.front);
	//print_recursive(lineup,lineup.front,lineup.front);
	turn(lineup.front);
	return 0;
}
// Jose Sosa
// 11/13/19
// Turn function


void death (int current){
	if (lineup.data[current].bullets == 0)
	
		// makes it so that next and previous will skip the dead player 
		lineup.data[lineup.data[current].next].previous == lineup.data[current].previous;
		lineup.data[lineup.data[current].previous].next == lineup.data[current].next;
		
		//sets the player to dead
		lineup.data[current].dead = true;
		
		end_game(lineup.data[current].previous);
}


// Function that simulates every turn, calling dices function depending of the role of the current player, and after the dices have been
// roled takes the correct action (increase health, shoot someone, checks arrows, and check if anyone has died). After this is done, it points 
// to the next player whose turn it is. 

void turn(int current){

    bool gatling = false;      // Initialize gatling boolean as false
    bool dynamite = false;     // Initialize dynamite boolean as false
    int beer = 0;              // Initialize beer int as 0
    
	struct player_queue temp = lineup;
	
    // Reset number of dices to 5 for the current player
    lineup.data[current].dice = 5;
    
    // As long as there are players in the player queue
    while(!end_game(current))
    {
		
        // Announce whose turn it is (Print out info)
        cout << "Current turn:" << endl;
        print_player(lineup.data[current]);
        
        // Check players role to call the correct dice function
        // if the current player is the sherriff
        if(lineup.data[current].role == 1)
        {
            // Call correct dice function according to the player's role
            struct stack dice_stack = dice_sheriff(current, &gatling, &dynamite, &beer);
			
			// Announce the results once all the dices had been rolled
			// If player got three dynamites
			if(dynamite == true)
			{
				// Reduce player's life by one
				lineup.data[current].bullets--;
				// Print it out
				cout << "You rolled three dynamites!!! You lost one life point" << endl;
			}
			
			else
			{
				// If player got three gatlin guns
				if(gatling == true)
				{
					// Call function to damage everyone (-1 health)
					damage_AllPlayers(lineup.data[current].next, current);
					cout << "You rolled three Gatlin Guns!!! Shoot everyone once" << endl;
				
					// Push number of arrows players has back into the stack
					for(int i = 0; i <= lineup.data[current].arrows; i++)
					{
						// Push arrow back into stack
						push(1, arrows);
					}
				
					// Dispose of any arrows character has
					lineup.data[current].arrows = 0;
					cout << "Your arrows were dropped!!!" << endl;
					
					// Check if player has any beer that he kept
					if(beer == 0)
					{
						cout << "You don't have any beer!!!" << endl;
					}
					
					else
					{
						// Else if player kept beer 
						for(int i = 0; i <= beer; i++)
						{
							// Increase their life by the number of beers they kept
							lineup.data[current].bullets++;
						}
						
						//Print it out
						cout << "You have " << beer << " beers!!! Your life will increase by " << beer << endl;
					}
					
					// Check if the dice stack is empty (to shoot player to the right or the left)
					if(isEmpty(&dice_stack) == false)
					{
						// Call shooting function
						shooting(dice_stack, pop(&dice_stack), current);
					}
					
					else
					{
						// Else if no shooting happens, print it out
						cout << "No one was shot!!!" << endl;
					}
		
				}
				
				// If player did not get gatling gun
				else
				{
					// Anounce if you have any arrows
					if(lineup.data[current].arrows > 0)
					{
						cout << "You got " << lineup.data[current].arrows << " arrows!!!" << endl;
					}
					
					else
					{
						// Else if you do not have any print it out
						cout << "You did not get any arrows this turn!!!" << endl;
					}
					
					// Check if the dice stack is empty (to shoot player to the right or the left)
					if(isEmpty(&dice_stack) == false)
					{
						// Call shooting function
						shooting(dice_stack,pop(&dice_stack), current);
					}
					
					else
					{
						// Else if no shooting happens, print it out
						cout << "No one was shot!!!" << endl;
					}
					
					// Check if player has any beer that he kept
					if(beer == 0)
					{
						cout << "You don't have any beer!!!" << endl;
					}
					
					else
					{
						// Else if player kept beer 
						for(int i = 0; i <= beer; i++)
						{
							// Increase their life by the number of beers they kept
							lineup.data[current].bullets++;
						}
						
						//Print it out
						cout << "You have " << beer << " beers!!! Your life will increase by " << beer << endl;
					}
				}
			}
			// Check if anyone is dead, and change that status if needed
			check_Death(current, current);
			
			 end_game(current);
			
			// Announce the turn has finished
			cout << "The turn has ended!!!" << endl;
        }
        
        // if the current player is a deputy
        else if(lineup.data[current].role == 0)
        {
            // Call correct dice function according to the player's role
            struct stack dice_stack = dice_deputy(current, &gatling, &dynamite, &beer);
            {
                // Announce the results once all the dices had been rolled
                // If player got three dynamites
                if(dynamite == true)
                {
                    // Reduce player's life by one
                    lineup.data[current].bullets--;
                    // Print it out
                    cout << "You rolled three dynamites!!! You lost one life point" << endl;
                }
                
                else
                {
                    // If player got three gatlin guns
                    if(gatling == true)
                    {
                        // Call function to damage everyone (-1 health)
                        damage_AllPlayers(lineup.data[current].next, current);
                        cout << "You rolled three Gatlin Guns!!! Shoot everyone once" << endl;
                    
                        // Push number of arrows players has back into the stack
                        for(int i = 0; i <= lineup.data[current].arrows; i++)
                        {
                            // Push arrow back into stack
                            push(1, arrows);
                        }
                    
                        // Dispose of any arrows character has
                        lineup.data[current].arrows = 0;
                        cout << "Your arrows were dropped!!!" << endl;
                        
                        // Check if player has any beer that he kept
                        if(beer == 0)
                        {
                            cout << "You don't have any beer!!!" << endl;
                        }
                        
                        else
                        {
                            // Else if player kept beer 
                            for(int i = 0; i <= beer; i++)
                            {
                                // Increase their life by the number of beers they kept
                                lineup.data[current].bullets++;
                            }
                            
                            //Print it out
                            cout << "You have " << beer << " beers!!! Your life will increase by " << beer << endl;
                        }
                        
                        // Check if the dice stack is empty (to shoot player to the right or the left)
                        if(isEmpty(&dice_stack) == false)
                        {
                            // Call shooting function
                            shooting(dice_stack,pop(&dice_stack), current);
                        }
                        
                        else
                        {
                            // Else if no shooting happens, print it out
                            cout << "No one was shot!!!" << endl;
                        }
			
                    }
                    
                    // If player did not get gatling gun
                    else
                    {
                        // Anounce if you have any arrows
                        if(lineup.data[current].arrows > 0)
                        {
                            cout << "You got " << lineup.data[current].arrows << " arrows!!!" << endl;
                        }
                        
                        else
                        {
                            // Else if you do not have any print it out
                            cout << "You did not get any arrows this turn!!!" << endl;
                        }
                        
                        // Check if the dice stack is empty (to shoot player to the right or the left)
                        if(isEmpty(&dice_stack) == false)
                        {
                            // Call shooting function
                            shooting(dice_stack,pop(&dice_stack), current);
                        }
                        
                        else
                        {
                            // Else if no shooting happens, print it out
                            cout << "No one was shot!!!" << endl;
                        }
                        
                        // Check if player has any beer that he kept
                        if(beer == 0)
                        {
                            cout << "You don't have any beer!!!" << endl;
                        }
                        
                        else
                        {
                            // Else if player kept beer 
                            for(int i = 0; i <= beer; i++)
                            {
                                // Increase their life by the number of beers they kept
                                lineup.data[current].bullets++;
                            }
                            
                            //Print it out
                            cout << "You have " << beer << " beers!!! Your life will increase by " << beer << endl;
                        }
                    }
                }
                // Check if anyone is dead, and change that status if needed
                check_Death(current, current);
                
                end_game(current);
                
                // Announce the turn has finished
                cout << "The turn has ended!!!" << endl;
            }
        }
        
        // if the current player is an outlaw
        else if(lineup.data[current].role == 2)
        {
            // Call correct dice function according to the player's role
            struct stack dice_stack = dice_outlaw(current, &gatling, &dynamite, &beer);
            {
                // Announce the results once all the dices had been rolled
                // If player got three dynamites
                if(dynamite == true)
                {
                    // Reduce player's life by one
                    lineup.data[current].bullets--;
                    // Print it out
                    cout << "You rolled three dynamites!!! You lost one life point" << endl;
                }
                
                else
                {
                    // If player got three gatlin guns
                    if(gatling == true)
                    {
                        // Call function to damage everyone (-1 health)
                        damage_AllPlayers(lineup.data[current].next, current);
                        cout << "You rolled three Gatlin Guns!!! Shoot everyone once" << endl;
                    
                        // Push number of arrows players has back into the stack
                        for(int i = 0; i <= lineup.data[current].arrows; i++)
                        {
                            // Push arrow back into stack
                            push(1, arrows);
                        }
                    
                        // Dispose of any arrows character has
                        lineup.data[current].arrows = 0;
                        cout << "Your arrows were dropped!!!" << endl;
                        
                        // Check if player has any beer that he kept
                        if(beer == 0)
                        {
                            cout << "You don't have any beer!!!" << endl;
                        }
                        
                        else
                        {
                            // Else if player kept beer 
                            for(int i = 0; i <= beer; i++)
                            {
                                // Increase their life by the number of beers they kept
                                lineup.data[current].bullets++;
                            }
                            
                            //Print it out
                            cout << "You have " << beer << " beers!!! Your life will increase by " << beer << endl;
                        }
                        
                        // Check if the dice stack is empty (to shoot player to the right or the left)
                        if(isEmpty(&dice_stack) == false)
                        {
                            // Call shooting function
                            shooting(dice_stack,pop(&dice_stack), current);
                        }
                        
                        else
                        {
                            // Else if no shooting happens, print it out
                            cout << "No one was shot!!!" << endl;
                        }
			
                    }
                    
                    // If player did not get gatling gun
                    else
                    {
                        // Anounce if you have any arrows
                        if(lineup.data[current].arrows > 0)
                        {
                            cout << "You got " << lineup.data[current].arrows << " arrows!!!" << endl;
                        }
                        
                        else
                        {
                            // Else if you do not have any print it out
                            cout << "You did not get any arrows this turn!!!" << endl;
                        }
                        
                        // Check if the dice stack is empty (to shoot player to the right or the left)
                        if(isEmpty(&dice_stack) == false)
                        {
                            // Call shooting function
                            shooting(dice_stack,pop(&dice_stack), current);
                        }
                        
                        else
                        {
                            // Else if no shooting happens, print it out
                            cout << "No one was shot!!!" << endl;
                        }
                        
                        // Check if player has any beer that he kept
                        if(beer == 0)
                        {
                            cout << "You don't have any beer!!!" << endl;
                        }
                        
                        else
                        {
                            // Else if player kept beer 
                            for(int i = 0; i <= beer; i++)
                            {
                                // Increase their life by the number of beers they kept
                                lineup.data[current].bullets++;
                            }
                            
                            //Print it out
                            cout << "You have " << beer << " beers!!! Your life will increase by " << beer << endl;
                        }
                    }
                }
                // Check if anyone is dead, and change that status if needed
                check_Death(current, current);
                
                end_game(current);
                
                // Announce the turn has finished
                cout << "The turn has ended!!!" << endl;
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
                struct stack dice_stack = dice_outlaw(current, &gatling, &dynamite, &beer);
                {
                    // Announce the results once all the dices had been rolled
                    // If player got three dynamites
                    if(dynamite == true)
                    {
                        // Reduce player's life by one
                        lineup.data[current].bullets--;
                        // Print it out
                        cout << "You rolled three dynamites!!! You lost one life point" << endl;
                    }
                
                    else
                    {
                        // If player got three gatlin guns
                        if(gatling == true)
                        {
                            // Call function to damage everyone (-1 health)
                            damage_AllPlayers(lineup.data[current].next, current);
                            cout << "You rolled three Gatlin Guns!!! Shoot everyone once" << endl;
                    
                            // Push number of arrows players has back into the stack
                            for(int i = 0; i <= lineup.data[current].arrows; i++)
                            {
                                // Push arrow back into stack
                                push(1, arrows);
                            }
                    
                            // Dispose of any arrows character has
                            lineup.data[current].arrows = 0;
                            cout << "Your arrows were dropped!!!" << endl;
                        
                            // Check if player has any beer that he kept
                            if(beer == 0)
                            {
                                cout << "You don't have any beer!!!" << endl;
                            }
                        
                            else
                            {
                                // Else if player kept beer 
                                for(int i = 0; i <= beer; i++)
                                {
                                    // Increase their life by the number of beers they kept
                                    lineup.data[current].bullets++;
                                }
                            
                                // Print it out
                                cout << "You have " << beer << " beers!!! Your life will increase by " << beer << endl;
                            }
                        
                            // Check if the dice stack is empty (to shoot player to the right or the left)
                            if(isEmpty(&dice_stack) == false)
                            {
                                // Call shooting function
                                shooting(dice_stack,pop(&dice_stack), current);
                            }
                        
                            else
                            {
                                // Else if no shooting happens, print it out
                                cout << "No one was shot!!!" << endl;
                            }
			
                        }
                    
                        // If player did not get gatling gun
                        else
                        {
                            // Anounce if you have any arrows
                            if(lineup.data[current].arrows > 0)
                            {
                                cout << "You got " << lineup.data[current].arrows << " arrows!!!" << endl;
                            }
                        
                            else
                            {
                                // Else if you do not have any print it out
                                cout << "You did not get any arrows this turn!!!" << endl;
                            }
                        
                          // Check if the dice stack is empty (to shoot player to the right or the left)
                            if(isEmpty(&dice_stack) == false)
                            {
                                // Call shooting function
                                shooting(dice_stack,pop(&dice_stack),current);
                            }
                        
                            else
                            {
                                // Else if no shooting happens, print it out
                                cout << "No one was shot!!!" << endl;
                            }
                        
                            // Check if player has any beer that he kept
                            if(beer == 0)
                          {
                                cout << "You don't have any beer!!!" << endl;
                            }
                        
                            else
                            {
                                // Else if player kept beer 
                                for(int i = 0; i <= beer; i++)
                                {
                                    // Increase their life by the number of beers they kept
                                    lineup.data[current].bullets++;
                                }
                            
                                // Print it out
                                cout << "You have " << beer << " beers!!! Your life will increase by " << beer << endl;
                            }
                        }
                    }
                    // Check if anyone is dead, and change that status if needed
                    check_Death(current, current);
                
                    end_game(current);

                    // Announce the turn has finished
                    cout << "The turn has ended!!!" << endl;
                }
            }
            
            // Else the renegade will act as a deputy (Renegade must protect the sherriff)
            else
            {
                // Call correct dice function according to the player's role
                struct stack dice_stack = dice_deputy(current, &gatling, &dynamite, &beer);
                {
                    // Announce the results once all the dices had been rolled
                    // If player got three dynamites
                    if(dynamite == true)
                    {
                        // Reduce player's life by one
                        lineup.data[current].bullets--;
                        // Print it out
                        cout << "You rolled three dynamites!!! You lost one life point" << endl;
                    }
                
                    else
                    {
                        // If player got three gatlin guns
                        if(gatling == true)
                        {
                            // Call function to damage everyone (-1 health)
                            damage_AllPlayers(lineup.data[current].next, current);
                            cout << "You rolled three Gatlin Guns!!! Shoot everyone once" << endl;
                    
                            // Push number of arrows players has back into the stack
                            for(int i = 0; i <= lineup.data[current].arrows; i++)
                            {
                                // Push arrow back into stack
                                push(1, arrows);
                           }
                    
                           // Dispose of any arrows character has
                            lineup.data[current].arrows = 0;
                            cout << "Your arrows were dropped!!!" << endl;
                        
                            // Check if player has any beer that he kept
                            if(beer == 0)
                            {
                                cout << "You don't have any beer!!!" << endl;
                            }
                        
                            else
                            {
                                // Else if player kept beer 
                                for(int i = 0; i <= beer; i++)
                                {
                                    // Increase their life by the number of beers they kept
                                    lineup.data[current].bullets++;
                                }
                            
                                // Print it out
                                cout << "You have " << beer << " beers!!! Your life will increase by " << beer << endl;
                            }
                        
                            // Check if the dice stack is empty (to shoot player to the right or the left)
                            if(isEmpty(&dice_stack) == false)
                            {
                                // Call shooting function
                                shooting(dice_stack,pop(&dice_stack), current);
                            }
                        
                            else
                            {
                                // Else if no shooting happens, print it out
                                cout << "No one was shot!!!" << endl;
                            }
			
                        }
                    
                        // If player did not get gatling gun
                        else
                        {
                            // Anounce if you have any arrows
                            if(lineup.data[current].arrows > 0)
                            {
                                cout << "You got " << lineup.data[current].arrows << " arrows!!!" << endl;
                            }
                        
                            else
                            {
                                // Else if you do not have any print it out
                                cout << "You did not get any arrows this turn!!!" << endl;
                            }
                        
                            // Check if the dice stack is empty (to shoot player to the right or the left)
                            if(isEmpty(&dice_stack) == false)
                            {
                               // Call shooting function
                                shooting(dice_stack,pop(&dice_stack), current);
                            }
                        
                            else
                            {
                                // Else if no shooting happens, print it out
                                cout << "No one was shot!!!" << endl;
                            }
                        
                            // Check if player has any beer that he kept
                            if(beer == 0)
                            {
                                cout << "You don't have any beer!!!" << endl;
                            }
                        
                            else
                            {
                                // Else if player kept beer 
                                for(int i = 0; i <= beer; i++)
                                {
                                    // Increase their life by the number of beers they kept
                                    lineup.data[current].bullets++;
                                }
                            
                                //Print it out
                                cout << "You have " << beer << " beers!!! Your life will increase by " << beer << endl;
                            }
                        }
                    }
                    // Check if anyone is dead, and change that status if needed
                    check_Death(current, current);
                
						
						end_game(current);

                
                    // Announce the turn has finished
                    cout << "The turn has ended!!!" << endl;
                }
           }
        }
    }
    
	
    // Point to the next player whose turn it is
    turn(lineup.data[current].next);
	
} // End turn


// Function to traverse the current circular player queue and reduce the health of 
// everyone by one (except the player that got gatling gun)
void damage_AllPlayers(int current, int first){
    // Reduce the life of the current player by one
    lineup.data[current].bullets--;
    
    // If the next character is the first 
    if(lineup.data[current].next == first)
    {
        // Return
        return;
    }
    
    // Call this function recursively by pointing to the next character
    damage_AllPlayers(lineup.data[current].next, first);
} // End damage_AllPlayers


// Function that traverses the current circular player queue and adds up all the 
// character's role. This is to check if the sherriff is the only player alive
int renegade_Attitude(int current, int first, int characterRoleSum){
    // The  value will be equal to the summation of the character's role so far 
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


// Function to traverse the current circular player queue and depending of the health of
// the player, they will change the "dead" status
void check_Death(int current, int first){
    // If the life of the current player is equal or less than 0
    if(lineup.data[current].bullets <= 0)
    {
        // Change the status of player to "dead"
        //lineup.data[current].dead == true;
		death(current);
	}
    
    // If the next character is the first 
    if(lineup.data[current].next == first)
    {
        // Return
        return;
    }
    
    check_Death(lineup.data[current].next, first);
}  // End check_Death


// Function to "shoot" the players within the range specified by the dices
void shooting(struct stack dice_stack, int range, int current){
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
                cout << "The player to the left was shot!!!" << endl;
            }
            
            // If position is 2
            if(position == 2)
            {
                // Shoot the player to the right (-1 health)
                lineup.data[lineup.data[current].previous].bullets--;
                cout << "The player to the right was shot!!!" << endl;
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
                cout << "The player two positions to the left was shot!!!" << endl;
            }
            
            // if position is 2
            if(position == 2)
            {
                // Shoot the player two positions to the right (-1 health)
                lineup.data[lineup.data[lineup.data[current].previous].previous].bullets--;
                cout << "The player two positions to the right was shot !!!" << endl;
            }
        }
        
        // Call this function recursively
        shooting(dice_stack,pop(&dice_stack), current);
    }
    
    // If the stack is empty then return
    return;
} // End Shooting

bool end_game(int current){  //begining of function to check to see if the game should end
	int living_status = renegade_Attitude(current, current, 0);  //using renegade_Attitude to add role variables
	if(living_status == 1) {  //checks the sum of the roles, since deputy=0 and sherriff=1 
		cout << "Sheriff/Deputy wins";         //if the living_status=1 only the sherrif and deputy can be alive
		exit(0);  
	}
	else if(lineup.data[current].role == 2 && lineup.data[current].next == current) { //checks the list to see if list has only outlaws
		cout << "Outlaws win";
		exit(0);
	}
	else if(lineup.data[current].role == 3 && lineup.data[current].next == current) { //checks the list to see if list has only renegades
		cout << "Renegades win";
		exit(0);
	}
	return (false);
}




