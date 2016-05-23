// File:        ccqueue.cpp
// Author:      Jonathan M. Loewen
// Date:        January 24th, 2016
// Description: Implementation of a complaint queue for CMPT 225 Assignment 2

#include "ccqueue.h"
#include <exception>
#include <iostream>
using namespace std;

//Coded on January 24th, 2016.
//Final comments and annotations on January 30th, 2016.
//Fixed Header Comments on February 1st.
//Excepton Handling added February 1st.

//Constructor for a CCQueue() object.
CCQueue::CCQueue()
{
	//initialize maxticketid to 0, create new linked list of tickets.
	maxticketid = 0;
	tickets = *(new DLinkedList<Ticket>());
}
    
// enqueues a new ticket at the back of the ticket queue and returns true
// ticketid is assigned automatically as 1+maxticketid if enqueueing is possible
// does not enqueue and returns false if either parameter is empty string
// POST:  new ticket with supplied parameters is added to back of tickets,
//        maxticketid is incremented
// PARAM: customer and complaint fields to pass to Ticket constructor
bool CCQueue::Add(string customer, string complaint)
{
	//create a new ticket and add it to the 'queue'.
	Ticket newTick = *new Ticket(maxticketid + 1, customer, complaint);

	//check for the customer name and complaint lengths to ensure validity.
	if (customer.length() == 0 || complaint.length() == 0)
	{
		return false;
	}
	tickets.InsertBack(newTick);
	maxticketid++;
	return true;
}


// removes and returns an item from the front of the ticket queue
// throws a logic_error if the ticket queue is empty
// POST:  first item of the ticket queue is removed
Ticket CCQueue::Service()
{
	Ticket tick;
	if (tickets.Size() > 0)
	{
		tick  = tickets.RemoveAt(0);

		if (tick.GetID() <= maxticketid && tick.GetID() >= 0)
		{
			return tick;
		}
	}
	//This version requires the Driver to handle exceptions from Service.  Unless they are handled, this will not work.
	throw logic_error("Tried to remove a ticket from an empty list");
}

// moves an item towards the front of the queue by 1 position and returns true
// returns false if supplied index is 0 (first item) or outside the list boundaries
// POST:  DLinkedList items at position and position-1 swap spots in the list
// PARAM: initial index of item to move up
bool CCQueue::MoveUp(int index)
{
	//Move an item forward in the list.
	//Note that this does not have the same issues as MoveDown because decrementing the list does not affect the front of the list.
	try
	{
		if (index >= 1 && tickets.Size() >=2 && index < tickets.Size())
		{
			tickets.InsertAt(tickets.RemoveAt(index), index - 1);
			return true;
		}
		return false;
	}
	catch (logic_error)
	{
		cout << "Tried to move a ticket in an empty list." << endl;
		return false; //we have been given an invalid index if we are here.  return false.
	}
	
	
}

// moves an item towards the back of the queue by 1 position and returns true
// returns false if supplied index is the last item or outside the list boundaries
// POST:  DLinkedList items at position and position+1 swap spots in the list
// PARAM: initial index of item to move down
bool CCQueue::MoveDown(int index)
{
	try
	{
		//if the index is within valid boundaries, enter.
		if (index < tickets.Size() - 1 && tickets.Size() >= 2)
		{
			tickets.InsertAt(tickets.RemoveAt(index), index + 1);
			return true;
		}
		return false;//we have been given invalid parameters.  Return false.
	}
	catch(logic_error)
	{
		cout << "Tried to move a ticket on an empty list." <<endl;
		return false;//we have been given invalid parameters.  Return false.
	}
}

    // ACCESSORS
    
// returns the number of tickets
//Pre: A valid CCQueue.  Post: Returns the number of tickets in the 'queue'.
int CCQueue::Size() const
{
	return tickets.Size();
}
