// Grace Gomez
// 11/3/2019

#define MAX 50

// Library for a circular queue. We can only use 50 elements.
// varq means variable queue

// Character queue
typedef struct queuec{
    char data[MAX]; //queue array
    int front;
    int rear;
};

// Interger queue
typedef struct queuei{
    int data[MAX]; //queue array
    int front;
    int rear;
};

struct queuec* create_queuec();  //to create a queue in another function call using { struct queuec* [the name of your queue] = create_queuec }
struct queuei* create_queuei();  //to create a queue in another function call using  { struct queuei* [the name of your queue] = create_queuei }
bool isEmptyqueue(queue* varq);
bool isFullqueue(queue* varq);
void enqueue (queue* varq, int add_data);
void dequeue (struct queue* varq);
void peek (queue varq[]);

bool isEmptyqueuec(struct queuec* varq){
	return (varq->rear==-1);
}

bool isEmptyqueuec(struct queuei* varq){
	return (varq->rear==-1);
}

bool isFullqueuec(struct queuec* varq){
	if ( (varq->front !=0) && (varq->rear==varq->front-1)  || ( (varq->front==0) && (varq->rear==MAX-1) ) ) {
		return ( 1==1 );
	}
	else
		return ( 0==1 );
}

bool isFullqueuei(struct queuei* varq){
	if ( (varq->front !=0) && (varq->rear==varq->front-1)  || ( (varq->front==0) && (varq->rear==MAX-1) ) ) {
		return ( 1==1 );
	}
	else
		return ( 0==1 );
}

void enqueuec (struct queuec* varq, char add_data) {
	if( isFullqueue(varq) ) 
		return;
    else if(varq->front==-1 && varq->rear==-1)
        {
        varq->front=varq->rear=0;
        varq->data[0] = add_data;
        }
    else if(varq->rear==MAX-1 && varq->front!=0)
        {
        varq->rear=0;
        varq->data[varq->rear] = add_data;
        }
    else
        {
        varq->rear++;
        varq->data[varq->rear] = add_data;
        }
}

void enqueuei (struct queuei* varq, int add_data) {
	if( isFullqueue(varq) ) 
		return;
    else if(varq->front==-1 && varq->rear==-1)
        {
        varq->front=varq->rear=0;
        varq->data[0] = add_data;
        }
    else if(varq->rear==MAX-1 && varq->front!=0)
        {
        varq->rear=0;
        varq->data[varq->rear] = add_data;
        }
    else
        {
        varq->rear++;
        varq->data[varq->rear] = add_data;
        }
}

void dequeuec (struct queuec* varq) {
	if (isEmptyqueue(varq))
		return;
	else if(varq->front!=-1 && varq->front==varq->rear) {
		varq->front=varq->rear=-1;
	}
	else {
		if(varq->front==MAX-1) {
			varq->front=0;
		}
		else {
			varq->front++;
		}
	}
}

void dequeuei (struct queuei* varq) {
	if (isEmptyqueue(varq))
		return;
	else if(varq->front!=-1 && varq->front==varq->rear) {
		varq->front=varq->rear=-1;
	}
	else {
		if(varq->front==MAX-1) {
			varq->front=0;
		}
		else {
			varq->front++;
		}
	}
}

void peekc (struct queuec* varq) {
    if(isEmptyqueue(varq))
        {
        cout <<"\n QUEUE IS EMPTY" <<endl;
        return;
        }
    else
        {
        cout << varq->data[varq->front];
		return;
        }
}

void peeki (struct queuei* varq) {
    if(isEmptyqueue(varq))
        {
        cout <<"\n QUEUE IS EMPTY" <<endl;
        return;
        }
    else
        {
        cout << varq->data[varq->front];
		return;
        }
}