//Started 3/11/2024 by Ethan Larson
/*Shunting Yard algorithm, recieve infix notation (single digit integers), reconstruct in postfix notation, solve

What  

*/
#include <iostream>
#include <stack>
using namespace std;
void createStack(char input[20]);

struct Node {
  char data;
  Node* lnode;
  Node* rnode;
  Node* next;
};
/*      L - O - R
	    |
	    N
*/
/*struct Stack {// O - N - NN - NNN
  Node* node;
  Stack* next;
};

struct Queue {// O - N - NN - NNN
  Node* node;
  Queue* next;
};
*/
void createTree(char input[20]);
void printTreeBackwards(Node* last);
void createLinkedList(Node* tail, int data);
char operators[20];
char input[20];
char tree[40];

int main() {

  cout << "Initializing..." << endl;
  cout << "Type in your equation in Infix notation, only using + - * / ( )  ^ without spaces." << endl;

  cin.getline(input, 20);
  cout << input << endl;
  // cout << "Converting to Linked Nodes..." << endl;
  //createLinkedList(NULL, 0);
  cout << "Creating tree..." << endl;
  createTree(input);
  return 0;
}

void createTree(char input[20]) {
  Node* lastNum = NULL; //Queue
  Node* lastOp = NULL; // Operator Stack
  for (int i = 0; i < 20; i++) {
    
    //cout << input[i];

    if (input[i] == '0'||input[i] == '1'||input[i] == '2'||input[i] == '3'||input[i] == '4'||input[i] == '5'||input[i] == '6'||input[i] == '7'||input[i] == '8'||input[i] == '9') {
      cout << input[i] << endl; //debug
      Node* node = new Node;
      node -> data = input[i];
      node -> next = lastNum;
      lastNum = node;
    }

    else if (input[i] == '+'||input[i] == '-'||input[i] == '*'||input[i] == '/'||input[i] == '^') {
      cout << input[i] << endl; //debug
      if (lastOp == NULL) {
	Node* node = new Node;
	node -> data = input[i];
	node -> next = NULL;
	lastOp = node;
      }
      else {
	while (!(lastOp == NULL||lastOp->data == '(')) {
	  Node* node = new Node;
	  Node* nextOp = lastOp->next;
	  node = lastOp;
	  node -> next = lastNum;

	  lastNum = node;
	  lastOp = nextOp;
	  
	}
	Node* node1 = new Node;
	node1 -> data = input[i];
	node1 -> next = lastOp;
	lastOp = node1;
      }
    } 

    else if (input[i] == '(') {
      cout << input[i] << endl; //debug
      Node* node = new Node;
      node -> data = input[i];
      node -> next = lastOp;
      lastOp = node;
    }

    else if (input[i] == ')') {
      cout << input[i] << endl; //debug
      while  (lastOp->data != '(') {
	Node* nextOp = lastOp->next;
	Node* node = new Node;
	node = lastOp;

	lastOp = nextOp;
      }
      lastOp = NULL;
    }

    else {
      cout << "is not valid" << endl;
    }
    
  }
  while (lastOp != NULL) {
          Node* node = new Node;
          Node* nextOp = lastOp->next;
          node = lastOp;
          node -> next = lastNum;

          lastNum = node;
          lastOp = nextOp;

        }

  cout << endl << "Completed" << endl;
  printTreeBackwards(lastNum);
  
  return;
}

void printTreeBackwards(Node* last) {
  cout << last->data;
  if (last->next != NULL) {
    printTreeBackwards(last->next);
  }
  else {
    cout << endl << "End of queue.";
  }
}

void createLinkedList(Node* tail, int data) {//converts char input array into Node* queue input
  if (tail == NULL) {

    tail = new Node();

    tail->data = input[0];

    createLinkedList(tail, 1);
    
  }
  else {
    Node* top = new Node();
    top->next = tail;
    top->data = input[data];
    createLinkedList(top, data++);
  }
}

/*
//The following functions are adapted from geeksforgeeks.org tutorials
void enqueue(Node* head, Node* node)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    cout << item << " enqueued to queue\n";
}
Node* dequeue(Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
    return item;
*/
