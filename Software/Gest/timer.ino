//timer.c
#include "timer.h"

void allTimersInit() {
  // use timer linked list by calling push(&head)
  // access the timer created by calling locateTimer()
  
  //flex timer, 100ms
  node* t1_node = push(&head);
  t1_node->timer->timerInit(100);
  
  //accel timer, 100ms
  node* t2_node = push(&head);
  t2_node->timer->timerInit(100);
  
  //BLE timer, 10ms
  node* t3_node = push(&head);
  t3_node->timer->timerInit(10);
  
  //Battery timer, 5s
  node* t4_node = push(&head);
  t4_node->timer->timerInit(5000);
  
}

struct node* push(node** head_ref){
  task_timer_t* new_timer = new task_timer_t();
  node* new_node = new node();
  new_node->timer = new_timer;
  new_node->next = *head_ref;
  *head_ref = new_node;
  return new_node;
}

struct node* locateTimer(node** head_ref, int n){
    int len = 0, i;
    struct node* temp = head;
 
    // count the number of nodes in Linked List
    while (temp != NULL) {
        temp = temp->next;
        len++;
    }
 
    // check if value of n is not
    // more than length of the linked list
    if (len < n)
        return NULL;
 
    temp = head;
 
    // get the (len-n)th node from the beginning
    for (i = 1; i < len - n; i++)
        temp = temp->next;
 
    return temp;
}
