#include <iostream>

using namespace std;


struct Node{
	int data;
	Node *next;
};

void addNode(Node* &head, int n);
void printList(Node* &head);
void removeNode(Node* &head, int n);

int main(){
	
	Node* head = NULL;
	int n = 4;
	int i = 5;
	
	addNode(head, 4);
	addNode(head, 5);
	addNode(head, 6);
	addNode(head, 7);
	addNode(head, 8);
	
	printList(head);
	
	removeNode(head, 7);
	printList(head);

	
	removeNode(head, 8);
	printList(head);	
	
	removeNode(head, 4);
	printList(head);

//	printList(head);
}

void addNode(Node* &head, int n){
	Node* newnode = new Node;
	newnode->data = n;
	newnode->next = NULL;
	
	if (!head){
		head = newnode;	
		return;
		
	}
	Node* current = head;
	while (current->next){
		current = current->next;

	}
	current->next = newnode;	
	
}

void printList(Node* &head){
	
	if (!head)
		return;
	
	Node* current = head;	
	while (current){
		cout << current->data << " " ;
		current = current->next;
	}
	
	cout << endl;
}

void removeNode(Node* &head, int n){
	
	//checks if head exists
	if (!head)
		return;
		
	//checks for if n is the head
	while (head->data == n){
		Node* newHead = head->next;
		delete head;
		cout << "deleted old Head " << endl;
		head = newHead;
	}
	
	//If n is somewhere else in the list
	Node* current = head;
	Node* prev = current;
	while (current){
		if (current->data == n){
			Node* t = current;
			current = current->next;
			delete t;
			cout << "deleted " << n << endl;
			prev->next = current;
			prev = current;
		} else{
			prev = current;
			current = current->next;
		}
		
		
	}
}
