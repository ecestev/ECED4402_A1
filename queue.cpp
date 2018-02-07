/*
 * File: queue.cpp
 * Author: Stephen Sampson
 * Original Date: 9/23/2017
 * Revised Date: 9/27/2017
 * Purpose: This file contains the structure of the queue class used
 * to create TX and RX buffer objects.
 */

#include "queue.h"

/* Constructor - Initialize Object Vars */
queue::queue(int sz) : data(new char[sz]) {
    max = sz;
    items = 0;
    insloc = 0;
    remloc = 0;
}

/* Destructor */
queue::~queue(){
    delete [] data;
}

/* Member function to insert item at tail of queue*/
void queue::enqueue(char val) {
    if(items!=max){
        data[insloc] = val;
        items++;
        insloc++;
        if(insloc>=(max-1))
            insloc = 0;
    }
}

/* Member function to remove item at head of queue*/
char queue::dequeue(void) {
        char temp = data[remloc];
        items--;
        remloc++;
         if(remloc>=(max-1))
            remloc = 0;
        return temp;
}

/* Member function to check if queue is empty */
bool queue::empty(void) const {
    return (items == 0);
}
