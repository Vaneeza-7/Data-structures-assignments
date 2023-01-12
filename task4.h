#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/imgcodecs.hpp>
#include <iostream>
#include <stdio.h>
#include"task3.h"

using namespace cv;
using namespace std;

template <class T>
class node
{
public:
	T data;
	node* next;

	node()
	{
		data = 0;
		next = NULL;
	}

	node(T d, node* n)
	{
		data = d;
		next = n;
	}

	node(T d)
	{
		data = d;
	}

	void setData(T d)
	{
		data = d;
	}

	void setNext(node* n)
	{
		next = n;
	}

	T getData()
	{
		return data;
	}

	node* getNext()
	{
		return next;
	}

};

template <class T>
class SLinkedList {

public:

	node<T>* head;


	SLinkedList()
	{
		head = NULL;
	}

	void insert(T d)
	{
		//if the head is null then the new node is head. else find the end of the list and insert node there.

		node<T>* n = new node<T>(d);
		n->next = NULL;
		if (head == NULL)
		{
			head = n;
		}
		else
		{
			node<T>* temp = head;

			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = n;
		}

	}

	bool isEmpty()
	{
		if (head == NULL)
			return true;
		else return false;
	}

	void insertAtHead(T d)
	{
		node<T>* n = new node<T>(d);
		n->next = head;
		head = n;
	}

	void InsertAtIndex(T d, int index)
	{
		/*if (index < 0)
			return NULL;*/

		node<T>* temp = head;
		int currIndex = 1;
		while (temp && index > currIndex)
		{
			temp = temp->next;
			currIndex++;
		}
		/*if (index > 0 && temp == NULL) return NULL;*/

		node<T>* n = new node<T>(d);

		if (index == 0)
		{
			n->next = head;
			head = n;
		}
		else
		{
			n->next = temp->next;
			temp->next = n;
		}
	}

	T search(int index)
	{
		int currIndex = 1;
		node<T>* temp = head;
		while (temp->next != NULL && index > currIndex)
		{
			if (currIndex == index)
				return temp->data;
			else
				temp = temp->next;
			currIndex++;
		}
	}

	void update(int index, T d)
	{
		int currIndex = 0;
		node<T>* temp = head;
		while (temp->next != NULL)
		{
			if (currIndex == index)
				temp->setData(d);
			else
				temp = temp->next;
			currIndex++;
		}
	}

	void remove(T d)
	{
		//int currIndex = 1;
		node<T>* temp = head;
		while (temp->next != NULL /*&& index > currIndex*/)
		{
			if (temp->data == d)
			{
				node<T>* deletedNode = temp->next;
				temp->next = temp->next->next;
				delete deletedNode;
			}
			else
				temp = temp->next;
			//currIndex++;
		}
	}

	void print()
	{
		node<T>* temp = head;
		while (temp)
		{
			cout << temp->getData() << " ";
			temp = temp->next;
		}
	}

};



void rlc(Mat img)
{
    int cols = img.cols;
    int rows = img.rows;


    int** Image = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        Image[i] = new int[cols];
    }

	int** temp = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		temp[i] = new int[cols];
	}
    //int x;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            Image[i][j] = (int)img.at<uchar>(i, j);

        }
    }

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			temp[i][j] = 0;

		}
	}

	int start, end, col;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (Image[i][j] == 255 && Image[i][j-1]==0)
			{
				start = j;
				temp[i][j] = start;
			}
			if (Image[i][j] == 0 && Image[i][j - 1] == 255)
			{
				end = j-1;
				temp[i][j] = j-1;
			}
			
			if (Image[i][j] == 255 && Image[i][j - 1] == 255)
			{
				continue;
			}

			col = j;
		}
		temp[i][col] = -1;
	}

	SLinkedList<int> s;
	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (temp[i][j] != 0)
				s.insert(temp[i][j]);

		}
	}

	s.print();
}