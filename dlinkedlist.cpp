// File:        dlinkedlist.cpp
// Author:      Jonathan M. Loewen
// Date:        January 24th, 2016
// Description: Implementation of a customer complaint Linked List class for CMPT 225 Assignment 2


//Principal coding January 24th, 2016
//Final bugfixing and annotations on January 30th, 2016.
//Fixed Header Comments on February 1st.
//Excepton Handling added February 1st.

#ifdef _DLINKEDLIST_H_
#include <exception>
using namespace std;


//Constructor for our Linked List Template.
template <class T>
DLinkedList<T>::DLinkedList()
{
	size = 0;
	front = NULL;
	back = NULL;
}

//Constructor for the Linked List - produces a Deep Copy from the received Linked List.
template <class T>
DLinkedList<T>::DLinkedList(const DLinkedList<T>& ll)
{
	//copy the list.
	CopyList(ll);
}

//CopyList makes 'this' object an identical but separate copy of the values in ll.
//Pre: A Linked List to copy from.  Post: A Deep Copy has been created of received LL 'll'.
template <class T>
void DLinkedList<T>::CopyList(const DLinkedList<T>& ll)
{
	//if the initial list is not empty, delete its contents.
	if (!IsEmpty())
	{
		DeleteList();
	}
	//assign size - this must be done post-delete to prevent errors.
	size = ll.Size();

	//if ll is not empty, enter
	if (!ll.IsEmpty())
	{
		//curNode is a pointer to the node prior to the node being modified.
		Node<T>* curNode = ll.front;
		
		//Temp is a pointer to the data 'T' in ll that we are copying.
		Node<T>* temp = ll.front;
		
		//iterate ll's Size times.
		for (int i = 0; i < Size(); i++)
		{
			//1. make new node for data.
			//2. proceed list into proper position.
			//3. insert node into list.

			//new node is the new node created to be inserted into this.
			Node<T>* newNode = new Node<T>(temp->data);
			//if we're at iteration 0, the front pointer points to the new node.
			if (i == 0)
			{
				front = newNode;
			}

			//curNode points to the newly created node; newnode points backwards to curNode.
			curNode->next = newNode;
			newNode->prev = curNode;

			//pointer assignments have completed - iterate the curnode and temp pointers.
			curNode = newNode;
			temp = temp->next;
		}

		//curNode will now point towards the last node - set Back to this node.
		back = curNode;
	}
	else
	{
		//the user should be able to validly copy an empty list object - but with nothing to copy, all that happens is that front and back become null.
		front = NULL;
		back = NULL;
	}
}

// destructor - all it does is call the DeleteList() function.
//Pre: This List must exist.  Post: 'this''s data is freed from memory.
template <class T>
DLinkedList<T>::~DLinkedList()
{
	DeleteList();
}

//The de-facto delete function - deletes a linked list by iteratively destroying each node.
//Pre: This list must exist.  Post: This's data is freed from memory.
template <class T>
void DLinkedList<T>::DeleteList()
{
	//create a pointer to the front of the linked list.
	Node<T>* tempdel = front;
	//while this pointer is not NULL, iterate over the list.
	//while (tempdel != NULL)
	//{
	for(int i = 0; i < Size(); i++)
	{
		//iterate front - there's no reason to maintain front anymore.
		front = front->next;
		//delete the node at tempdel.
		delete tempdel;
		//move tempdel to the new front - no reason to remove next or prev, they get deleted at the same time.
		tempdel = front;
	}
	//}
	//assign front and back to NULL - probably unnecessary, but I just want to be sure that we leave nothing behind.
	front = NULL;
	back = NULL;
}

// Inserts an item at the front of the list
// POST:  List contains item at position 0
// PARAM: item = item to be inserted
template <class T>
void DLinkedList<T>::InsertFront(T item)
{
	//newVal is the node that we will pre-pend to our linked list.
	Node<T>* newVal = new Node<T>(item);
	
	//if we already have values in te list, enter.
	if (Size() > 0)
	{
		//assign newval's next pointer to the current front, Assign front's previous to newval, and point front to newval.
		newVal->next = front;
		front->prev = newVal;
		front = newVal;
	}
	//otherwise, this is the first value in the list.
	else
	{
		//point front and back to our new node.
		front = newVal;
		back = newVal;
	}
	//iterate Size.
	size++;
}

// Inserts an item at the back of the list
// POST:  List contains item at back
// PARAM: item = item to be inserted
template <class T>
void DLinkedList<T>::InsertBack(T item)
{
	//create the node that will be appended.
	Node<T>* newVal = new Node<T>(item);

	//if size is greater than 0, we already have items in our list.
	if (Size() > 0)
	{
		//assign back's next value to our new node, our new node's previous to back, and make the back pointer newval.
		back->next = newVal;
		newVal->prev = back;	
		back = newVal;
	}
	//otherwise, we're working with a previously empty list.
	else
	{
		//point back and front to newval.
		back = newVal;
		front = newVal;
	}
	//iterate size.
	size++;
}

// Inserts an item in position p (0-indexed)
// Throws exception for invalid index
// PRE:   0 <= p <= size
// POST:  List contains item at position p
// PARAM: item = item to be inserted, p = position where item will be inserted
template <class T>
void DLinkedList<T>::InsertAt(T item, int p)
{
	//if the user wants to insert at 0, just call insertfront instead.
	if (p == 0)
	{
		InsertFront(item);	
	}
	//if the user wants to insert at Size() (the back), just call insertback.
	else if (p == Size())
	{
		InsertBack(item);
	}
	else if (p < 0 || p > Size())
	{
		throw std::out_of_range("Invalid value sent to InsertAt");
	}
	else
	{
		//otherwise, it's neither front nor back, meaning there are >=3 values, and it's one of the middle values.

		//newVal is the new node to be inserted.
		Node<T>* newVal = new Node<T>(item);

		//nextNode is a pointer to the node that will be after newVal.
		Node<T>* nextNode = front;
		//iterate nextNode into position p.
		for (int i = 0; i < p; i++)
		{
			nextNode = nextNode->next;
		}

		//prevNode is a pointer to the node that precedes newVal.
		Node<T>* prevNode = nextNode->prev;

		//point newVal to nextNode, and nextNode to newVal.
		newVal->next = nextNode;
		nextNode->prev = newVal;

		//point prevNode to newVal, and newVal to prevNode.
		prevNode->next = newVal;
		newVal->prev = prevNode;

		//iterate size.
		size++;
	}
}

// Removes and returns an item from position p (0-indexed)
// Throws exception if list is empty or index invalid
// PRE:   0 <= p <= size
// POST:  Item is removed from list
// PARAM: p = position from where item will be removed
template <class T>
T DLinkedList<T>::RemoveAt(int p)
{
	//retval is the node returned to the caller.
	Node<T>* retval;
	try
	{
		//if p is a valid index, enter.
		if (p < size && p >= 0)
		{
			//if p is 0, we can just remove the front and call it a day.
			if (p == 0)
			{
				//point retval to front.
				retval = front;
				//if size is greater than 1, enter.
				if (Size() > 1)
				{
					//tempVal is the next value - this will become our new front.
					Node<T>* tempVal = front->next;
					//decouple tempVal from the front.
					tempVal->prev = NULL;
					//reassign front
					front = tempVal;
					//de-link front from next.
					retval->next = NULL;
				}
				else
				{
					//This is the last value being removed.  NULL out front and back - just for completion's sake.
					front = NULL;
					back = NULL;
				}
			}
			//if p is size-1, we're removing the end value.
			else if (p == Size() - 1)
			{
				//p cannot be 0 in this case - we already checked that above.  So we can safely just cut off the tail.
				//point the return value pointer to the back.
				retval = back;
				//create a pointer to the 2nd last node.  NULL out that node's next, and NULL out the last node's prev.
				Node<T>* tempVal = back->prev;
				tempVal->next = NULL;
				retval->prev = NULL;
				//assign back to the new back, the previously 2nd last node.
				back = tempVal;
			}
			//This is all other cases (contrary to popular belief, 'if you aint first, you're last' is not necessarily true.  You could be second, third, hell, you could even be fourth)
			else
			{
				retval = front;
				//the node to be returned is neither the front of the LL or the back of the LL.

				//first, we must proceed to the node.  Do this using a for loop.
				//index we want is p - so we want to loop p times.  Note that this will never have to cover for the case of 0 or size.
				for (int i = 0; i < p; i++)
				{
					retval = retval->next;
				}

				//point the values surrounding retval at each other.
				Node<T>* prevVal = retval->prev;
				prevVal->next = retval->next;
				Node<T>* nextVal = retval->next;
				nextVal->prev = prevVal;

				//decouple retval from these nodes.
				retval->next = NULL;
				retval->prev = NULL;
			}
			size--;
			return retval->data;
		}
		throw out_of_range("Invalid Index");
	}
	catch(out_of_range)
	{
		cout << "Tried to remove item from an empty list." << endl;
		throw out_of_range("Invalid Index");
		//return front->data;
	}
}

// Removes duplicates from the list, preserving existing order of remaining items.
// The first occurrence of any duplicate (relative to the front of the list)
//   is the one which remains.
// We have not yet learned about efficiency so you may implement this in any way
//   as long as the resulting list satisfies the requirement above.
// PRE:   List may or may not contain duplicates.
// POST:  List contains no duplicates, front and back point to the appropriate nodes
// PARAM: 
template <class T>
void DLinkedList<T>::RemoveDuplicates()
{
	//enter if there's a possibility of duplicates.
	if (Size() > 1)
	{
		//start at the end of the list and iteratively remove duplicates.
		for (int i = Size() - 1; i >= 0; i--)
		{
			//Remove the current node and capture it within tempNode.
			Node<T>* tempNode = new Node<T>(RemoveAt(i));

			//if the removed node's ticket is not in the linked list already, insert the node into the linked list.
			if (!Contains(tempNode->data))
			{
				InsertAt(tempNode->data, i);
			}
		}
	}
}

// ACCESSORS

// Returns size of list from 'size'.
template <class T>
int DLinkedList<T>::Size() const
{
	return size;
}

// Returns whether or not the list is empty
template <class T>
bool DLinkedList<T>::IsEmpty() const
{
	//if the size is greater than 0, the list isnt empty.
	if (size > 0)
	{
		return false;
	}
	return true;
}

// Returns existence of an item.
//Pre: List must exist, needs an Item to search for.
//Post: Returns a true/false value of whether or not the item is in the linked list.
template <class T>
bool DLinkedList<T>::Contains(T item) const
{
	//check if front or item are null - if either are null, the item cant possibly exist in the list.  Return false.
	if (front == NULL || item == NULL)
	{
		return false;
	}
	//if the front's item is the item, return true.  If the back's item is the item, return true.
	else if (front->data == item)
	{
		return true;
	}
	else if (back->data == item)
	{
		return true;
	}
	//At this poin, if size is 2 or less, the item is not in the list (as it would be at the front or back).  return false.
	else if (Size() <= 2)
	{
		return false;
	}
	//there are 3+ items in the list.  Start at index 1 (since we've already checked 0).
	//for (T* curVal = front->next; curVal->next != NULL; curVal = curVal->next)
	for (Node<T>* curVal = front->next; curVal->next != NULL; curVal = curVal->next)
	{
		//if value is found, return true.
		if (curVal->data == item)
		{
			return true;
		}
	}
	//otherwise, return false.
	return false;
}

// Returns item at index (0-indexed)
// Throws exception for invalid index
//Pre: List must exist.  Post: Returns the item at the designated Node.
template <class T>
T DLinkedList<T>::ElementAt(int p) const
{
	//if p is out of range, throw an exception.
	if (p < 0 || p >= Size())
	{
		//exception
		throw std::out_of_range("OOR in ElementAt");	
	}
	else
	{
		//create a pointer to the front, and iterate this into position p.
		Node<T> *curVal = front;
		for (int i = 0; i < p; i++)
		{
			curVal = curVal->next;
		}
		//return a pointer to the Ticket at value p.
		return curVal->data;
	}
}

// OVERLOADED OPERATORS

// overloaded assignment operator
// must work in the following cases:
// list2 = list1 -> general case
// list2 = list2 -> should do nothing
//Pre: both this and ll must exist.  Post: Returns a linked list equal to 'll'.
template <class T>
DLinkedList<T>& DLinkedList<T>::operator=(const DLinkedList<T>& ll)
{
	//if the address of 'this' is the same as the address of 'll', they are the same value.  Return 'this'.
	if (this == &ll)
	{
		return *this;
	}
	//create a new parameterized DLinkedList object with 'll' as the parameter.  Return this list to the caller.
	DLinkedList<T> *tempList = new DLinkedList<T>(ll);
	return *tempList;
}
#endif