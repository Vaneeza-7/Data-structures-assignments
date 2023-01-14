//linked list class for lru
#pragma once
#pragma once
#include<iostream>
using namespace std;

template<class T1>
class node
{
private:
	T1 data;

public:
	node<T1>* next;
	node(T1 data)
	{
		this->data = data;
		next = NULL;
	}

	node()
	{
		this->data = '\0';
		next = NULL;
	}
	void setdata(T1 d) {
		data = d;
	}

	T1 getData()
	{
		return data;
	}

};

template<class T1>
class Queue
{
public:
	node<T1>* rear;
	node<T1>* front;
	int size=0;
	Queue()
	{
		rear = front = NULL;
		size = 0;
	}

	bool isEmpty()
	{
		if (front == NULL)
			return true;
		else
			return false;
	}

	void enqueue(T1 data)
	{
		size++;
		node<T1>* temp = new node<T1>(data);
		if (isEmpty())
		{
			front = rear = temp;
		}
		else
			rear->next = temp;
		    rear = temp;

	}

	void dequeue()
	{
		T1 val;
		node<T1>* temp = new node<T1>();
		if (!isEmpty())
		{
			size--;
			val = front->getData();
			temp = front;
			front = front->next;
			delete temp;
		}
		//return val;

	}

	int getsize()
	{
		return size;
	}

	T1 isfront()
	{
		return front->getData();
	}

	//void print() {
	//	node<T1>* temp;
	//	temp = front;
	//	while (temp)
	//	{
	//		cout << "The data of Queue member is : " << temp->getData() << endl;
	//		//cout << "The id of Queue member is : " << temp->getID() << endl;
	//		temp = temp->next;
	//	}

	//}

	bool contains(T1 x)
	{
		bool find = false;
		node<T1>* temp;
		temp = front;
		while (temp)
		{
			if (temp->getData() == x)
			{
				find = true;
				break;
			}
			temp = temp->next;
		}
		return find;
	}

};