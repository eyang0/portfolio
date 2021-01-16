#include "rem_dup_lib.h"
#include <sstream>
#include <iostream>
#include <string>

using namespace std;


void removeConsecutive(Item* head)
{
	//handles if list is empty, and if we have reached the last Item
	if(head == NULL || head->next == NULL)
	{
		return;
	}
	//if the next value is a duplicate
	else if(head->val == head->next->val)
	{
		Item* temp = head->next->next;
		delete head->next;
		head->next = temp;

		//run it again on this head to check for more consecutive duplicates
		removeConsecutive(head);
	}
	else
	{
		removeConsecutive(head->next);
	}
}


Item* concatenate(Item* head1, Item* head2)
{
	//if first list is empty, or if we have reached the end of first list
	if(head1 == NULL)
	{
		//if second list is empty, or if we have reached the end of second list
		if(head2 == NULL)
		{
			return NULL;
		}
		else
		{
			//recursively creating each item from second list as the next item
			return new Item(head2->val, concatenate(head1, head2->next));
		}
	}
	else
	{
		//recursively creating each item from first list as the next item
		return new Item(head1->val, concatenate(head1->next, head2));
	}
}




//HELPER FUNCTIONS

//deallocates List
void destructList(Item* head)
{
	if(head == NULL)
	{
		return;
	}
	else
	{
		Item* temp = head;
		head = head->next;
		delete temp;
		destructList(head);
	}
}


//reads in list from string
void read_to_List(Item*& head, string line)
{
	//if line is empty, set head to NULL
	if(line.empty())
 	{
 		head = NULL;
 	}
 	else
 	{
 		stringstream ss(line);
 		int x;
 		ss >> x;
 		head = new Item(x, NULL); //make the first Item
		Item* curr_Item = head;

 		while(ss >> x)
 		{
 			//create next Item and update current Item's next pointer
 			curr_Item->next = new Item(x, NULL);
 			curr_Item = curr_Item->next;
 		}
 	}
}



