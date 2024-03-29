  
typedef struct {
	int data[MAX];
	int top;
} stack;


bool isFull(stack* varst){
	if (sizeof(varst->data) == varst->top)
		return (1 == 1);
	else 
		return (1 == 0);
}

void push(int newelem, stack* varst) {
	if(isFull(varst)) {
		cout<< endl  <<"STACK OVERFLOW" << endl;
	}
	else {
		varst->data[varst->top] = newelem; 
		varst->top++;
	}
}

bool isEmpty(stack* varst) {
	if (varst->top <= -1)
		return (1 == 1);
	else
		return (0==1);
}

int pop(stack* varst) {
	int temp;
	if(isEmpty(varst)) {
		cout<< endl  <<"STACK EMPTY" << endl; 
		return -1;
	}
	else {
		temp = varst->data[varst->top-1];
		varst->data[varst->top-1] = '\0';
		varst->top = varst->top-1;
	}
	return temp;
}

stack* create_stack() {
	stack base;
	stack* temp_stack = &base; //= (stack*)malloc(sizeof(stack*));
	temp_stack->top = -1;
	memset(temp_stack->data, 0, sizeof(temp_stack->data));
	return temp_stack;
}
