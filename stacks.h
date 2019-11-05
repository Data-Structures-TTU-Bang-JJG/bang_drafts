struct stack {
	int data[MAX];
	int top;
};


bool isFull(struct stack* varst){
	if (sizeof(varst->data) == varst->top)
		return (1 == 1);
	else 
		return (1 == 0);
}

void push(int newelem, struct stack* varst) {
	if(isFull(varst)) {
		cout<< endl  <<"STACK OVERFLOW" << endl;
		exit(0);
	}
	else {
		varst->data[varst->top] = newelem; 
		varst->top++;
	}
}

bool isEmpty(struct stack* varst) {
	if (varst->top == 0)
		return (1 == 1);
	else
		return (0==1);
}

int pop(struct stack* varst) {
	int temp;
	if(isEmpty(varst)) {
		cout<< endl  <<"STACK EMPTY" << endl; 
		exit(0);
	}
	else {
		temp = varst->data[varst->top-1];
		varst->data[varst->top-1] = '\0';
		varst->top = varst->top-1;
	}
	return temp;
}

struct stack* create_stack() {
	struct stack* temp_stack = (struct stack*)malloc(sizeof(struct stack*));
	temp_stack->top = 0;
	memset(temp_stack->data, 0, sizeof(temp_stack->data));
	return temp_stack;
}