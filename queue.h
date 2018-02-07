/*
 * File: queue.h
 * Author: Stephen Sampson
 * Original Date: 9/23/2017
 * Revised Date: 9/27/2017
 * Purpose: This file contains the structure of the queue class used
 * to create TX and RX buffer objects.
 */

#pragma once

class queue {
private:
    int max;    // maximum size of the queue
    int items;  // number of items in the queue
    int insloc; // next location to insert
    int remloc; // next location to remove
    char* data; // vector holding the queue of items
public:
    queue(int sz);                      // constructor, max = sz
    ~queue();                           // destructor
    void enqueue(char UART_RX_CHAR);    // put the char onto the queue
    char dequeue(void);                 // get char at the head of the queue
    bool empty(void) const;             // check for empty queue
};



