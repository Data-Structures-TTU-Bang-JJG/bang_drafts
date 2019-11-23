// Function used by the "good guys" to "shoot" the "bad guys" within the range specified by the dices
void goodGuys_shooting(struct stack dice_stack, int range, int current){
    while(isEmpty(&dice_stack) == false)
    {
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
                cout << "The player to the left was shot!!!" << endl;
            }
            
            // Else if the suspicion of the player on the right is lower than 
            // the one on the left
            else if(suspicion[lineup.data[current].next] >= suspicion[lineup.data[current].previous])
            {
                // Shoot the player to the right (-1 health)
                lineup.data[lineup.data[current].previous].bullets--;
                cout << "The player to the right was shot!!!" << endl;
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
                cout << "The player two positions to the left was shot!!!" << endl;
            }
            
            // If the suspicion of the player two spaces to the right is lower than
            // the one two spaces to the left
            else if(suspicion[lineup.data[lineup.data[current].next].next] >= suspicion[lineup.data[lineup.data[current].previous].previous])
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

// Function used by the "bad guys" to "shoot" the "good guys" within the range specified by the dices
void badGuys_shooting(struct stack dice_stack, int range, int current){
    while(isEmpty(&dice_stack) == false)
    {
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
                cout << "The player to the left was shot!!!" << endl;
            }
            
            // Else if the suspicion of the player on the right is higher than 
            // the one on the left
            else if(suspicion[lineup.data[current].next] <= suspicion[lineup.data[current].previous])
            {
                // Shoot the player to the right (-1 health)
                lineup.data[lineup.data[current].previous].bullets--;
                cout << "The player to the right was shot!!!" << endl;
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
                cout << "The player two positions to the left was shot!!!" << endl;
            }
            
            // If the suspicion of the player two spaces to the right is higher than
            // the one two spaces to the left
            else if(suspicion[lineup.data[lineup.data[current].next].next] <= suspicion[lineup.data[lineup.data[current].previous].previous])
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