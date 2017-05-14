#pragma once

// The linked list to be created will be of the most basic type. There will be a head pointer and the last node will have the m_next member variable set to NULL.
typedef struct node_t node_t;
struct node_t
{
	int     m_value;
	node_t* m_next;
};

class LinkedList
{
public:
	LinkedList();
	~LinkedList();

	void Execute();
	
private:
	node_t* head = nullptr;

	node_t* createNode(int value);
	void addNode(node_t** list, int value);
	void printList(node_t* list);
	node_t* reverseList(node_t* head);
};

