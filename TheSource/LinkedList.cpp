#include "LinkedList.h"
#include <iostream>
#include <string>

LinkedList::LinkedList()
{
}

LinkedList::~LinkedList()
{
	// free resources from the free store
	while (head)
	{
		auto current = head;
		head = head->m_next;
		delete(current);
	}
}

void LinkedList::Execute()
{
	for (int i = 0; i < 20; i++) {
		addNode(&head, i);
	}
	printList(head);
	head = reverseList(head);
	printList(head);
}

node_t* LinkedList::createNode(int value)
{
	auto newNode = new node_t();
	if (newNode)
	{
		newNode->m_value = value;
		newNode->m_next = nullptr;
	}
	return newNode;
}

void LinkedList::addNode(node_t** list, int value)
{
	if (!*list)
	{
		*list = createNode(value);
		return;
	}
	node_t* listPtr = *list;
	while (listPtr->m_next)
	{
		listPtr = listPtr->m_next;
	}
	listPtr->m_next = createNode(value);
}

void LinkedList::printList(node_t* list)
{
	while (list)
	{
		std::cout << ("%d  ", list->m_value) << std::endl;
		list = list->m_next;
	}
}

node_t* LinkedList::reverseList(node_t* head)
{
	node_t* cursor = nullptr;
	node_t* next;
	while (head)
	{
		next = head->m_next;
		head->m_next = cursor;
		cursor = head;
		head = next;
	}
	return cursor;
}
