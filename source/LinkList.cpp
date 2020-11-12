#include <iostream>
#include<bits/stdc++.h>

using namespace std;

typedef struct node {
	int data;
	struct node* next;
}node;

void inItList(node*& head, node*& tail) {
	head = new node;
	if (!head) exit(1);
	tail = head;
	tail->next = NULL;
}

void tailInsert(node*& head, node*& tail, int dataIn) {
	node* p = new node;
	p->next = NULL;
	p->data = dataIn;
	tail->next = p;
	tail = p;
}

void headInsert(node*& head, node*& tail, int dataIn) {
	node* p = new node;
	p->data = dataIn;
	p->next = head->next;
	if (head->next == NULL) tail = p;
	head->next = p;
}

void incrementalInsert(node*& head, node*& tail, int dataIn) {
	if (head->next == NULL) {
		tailInsert(head, tail, dataIn);
		return;
	}
	if (head->next->data >= dataIn) {
		headInsert(head, tail, dataIn);
		return;
	}
	node* p, * tmp = new node;
	tmp->data = dataIn;
	p = head->next;
	while (p->next != NULL) {
		if (p->data <= dataIn && p->next->data >= dataIn) {
			tmp->next = p->next;
			p->next = tmp;
			return;
		}
		p = p->next;
	}
	tailInsert(head, tail, dataIn);
}

void deleteEven(node*& head) {
	node* p = head, * tmp;
	while (true){
		if (p->next == NULL) return;
		if (!(p->next->data & 1)) {
			tmp = p->next;
			p->next = p->next->next;
			delete(tmp);
		}
		else p = p->next;
	}
}

void printList(node* p) {//from head->next to tail
	p = p->next;
	while (true){
		cout << p->data << " ";
		if (p->next == NULL) return;
		p = p->next;
	}
}
