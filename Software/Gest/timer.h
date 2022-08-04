//timer.h
#ifndef TIMER_H
#define TIMER_H

/* ~~~~~~~~~~ INCLUDES ~~~~~~~~~~ */
/***** GENERAL *****/
#include "config.h"

/* ~~~~~~~~~~ STRUCTS ~~~~~~~~~~ */
struct task_timer_t{
  //Refernce time in ms from core starting
  unsigned long ref = 0;
  //Offset duration from reference time 
  unsigned long dur = 100;

  //Initialize timer reference and duration to 'input'
  void timerInit(unsigned long input){
    dur = input;
    ref = millis();
  }

  //Update timer reference to current time 
  void refUpdate(){
    ref = millis();
  }

  int bump(){
    if(ref + dur <= millis()){
      refUpdate();
      return 1;
    } else {
      return 0;
    }
  }
  
} t1, t2, t3, t4;

void allTimersInit();

/*
 * Add linked list and dynamic timer adding/removing functionality 
 */

struct node {
  struct task_timer_t* timer;
  struct node* next;
};

node* head = new node();

void push();




#endif
