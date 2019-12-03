/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
Stack library that works together with the main program

Author: Grace Gomez
Team members: Jerel Navarrette
              Jose Sosa
* * * * * * * * * * * * * * * * * * * * * * * * * * * */

// Stack structure  
typedef struct {
    // Data stored on the stack (Global Max = 20)
	int data[MAX];
	// Int that represents the top of the stack
	int top;
} stack;

// NAME: isFull
// INPUT PARAMETERS: stack variable
// OUTPUT: true or false (if the data on the stack is equal to top then return true)
// PURPOSE: To check if a stack is full
bool isFull(stack* varst){
    // If the stack has reached the top
	if (sizeof(varst->data) == varst->top)
	// Return true
		return (1 == 1);
	else
	// Otherwise return false
		return (1 == 0);
} // End isFull

// NAME: peek
// INPUT PARAMETERS: stack variable
// OUTPUT: int value equal to the data on top of stack
// PURPOSE: To check the data on the value on top of stack
int peek(stack* varst) {
    // Return the data stored on the top of the stack 
	return varst->data[varst->top];
} // End peek

// NAME: push
// INPUT PARAMETERS: int newelem(data to be "pushed" on the stack variable)
// stack variable
// OUTPUT: none
// PURPOSE: To "push" a new element on the stack 
void push(int newelem, stack* varst) {
    // Check if the stack is full
	if(isFull(varst)) {
	    // If yes, print out that the stack is full
		cout<< endl  <<"STACK OVERFLOW" << endl;
	}
	else {
	    // Else, increment the top integer by one
		varst->top++;
		// Add the new element at the top of the stack
		varst->data[varst->top] = newelem; 
	}
} // End push

// NAME: isEmpty
// INPUT PARAMETERS: stack variable
// OUTPUT: true or false (If the top marker is equal to -1, return false)
// PURPOSE: To check if the stack is empty
bool isEmpty(stack* varst) {
    // If top integer is -1
	if (varst->top <= -1)
	    // Return true
		return (1 == 1);
	else
	    // Else, return false
		return (0==1);
} // End is Empty

// NAME: pop
// INPUT PARAMETERS: stack variable
// OUTPUT: int value equal to the data on top of stack
// PURPOSE: To "Pop" or take out the element on top of the stack
int pop(stack *varst) {
    // Used to store temporary value
	int temp;
	// If the stack is empty
	if(isEmpty(varst)) {
	    // Print out that the stack is empty
		cout<< endl  <<"STACK EMPTY" << endl;
		// Return the value (-1 because it is empty)
		return -1;
	}
	else {
	    // Else, store the data on top of the stack into temp variable
		temp = varst->data[varst->top]; // grace;
		// Reduce the number of elements of the stack by on 
		varst->top = varst->top-1;
	}
	// Return the value that was on top of the stack 
	return temp;
} // End pop

// NAME: create_stack
// INPUT PARAMETERS:
// OUTPUT: stack variable 
// PURPOSE: This functions creates a stack 
stack* create_stack() {
    // Allocate the memory space for this stack
	stack* temp_stack = (stack*)malloc(sizeof(stack));
	// Set the top to -1 (Empty stack)
	temp_stack->top = -1;
	// Fill the memory of the stack 
	memset(temp_stack->data, 0, sizeof(temp_stack->data));
	//Return the stack that was created
	return temp_stack;
} // End create_stack