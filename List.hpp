#ifndef LIST_H
#define LIST_H

#include <iostream>
using namespace std;

/** Allow the use of different data type */
template<class T>

/** @class List
  * ADT list - Pointer-based implementation */
class List
{
	public:
	/** Default constructor with initialization */
	List() : size(0),head(NULL),back(NULL) {}

    /** Check whether the list is empty */
	bool isEmpty()
    {
        if(size == 0)
            return true;
        else
            return false;
    }

    /** @return number of items in list */
    int getSize()
    {
        return size;
    }

    /** @param data to push back into the list */
    void push_back(const T& newItem)
    {
        ListNode *cur = new ListNode();
        cur->item = newItem;

        if(head == NULL)
        {
            head = cur;
            back = head;
            size++;
        }
        else
        {
            back->next = cur;
            back = cur;
            size++;
        }
    }

    /** @return retrieve data according to index */
    T getItem(int index)
    {
        ListNode *cur = find(index);
        return (cur->item);
    }

    /** @param delete all the data start from the index */
    void partial_delete(int index)
    {
        back = find(index);
        back->next = NULL;
        size = index;
    }

    /** Sort the available move in ascending order */
    void bubbleSort()
    {
        int tempSize = size;
        int index = 1;
        ListNode *prev = find(index);
        ListNode *cur = find(index+1);

        while(tempSize != 1 && size != 0)
        {
            T temp;

            for(int i=1; i<tempSize; i++)
            {
                if((prev->item).getDistance() >= (cur->item).getDistance() )
                {
                    temp = cur->item;
                    cur->item = prev->item;
                    prev->item = temp;
                }
                prev = find(i);
                cur = find(i+1);
            }

            tempSize--;
        }
    }

    /** Filter the move */
    void chooseBest()
    {
        if(size != 0)
        {
            int i;
            ListNode *first = find(1);

            for(i=2; i<=size; i++)
            {
                ListNode *cur = find(i);

                if((first->item).getDistance() != (cur->item).getDistance())
                {
                    break;
                }
            }

            partial_delete(i-1);
        }
    }

	private:
	/** A node on the list */
	struct ListNode
    {
        /** A data item on the list */
        T item;
        /** Pointer to next node */
        ListNode *next;
    };

    /** Number of items in list */
    int size;
    /** Pointer to linked-list */
    ListNode *head;
    ListNode *back;
    /** Locates a specified node on the linked-list
        @return a pointer to the index-th node */
	ListNode *find(int index) const
	{
        if ( (index < 1) || (index > size) )
            return NULL;
        else
        {
            ListNode *cur = head;
            for (int skip = 1; skip < index; ++skip)
                cur = cur->next;
            return cur;
        }
    }
};

#endif
