#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

//gcc -Wall -Werror -o test2 uthread.c context.c preempt.c queue.c

#include "context.h"
#include "preempt.h"
#include "queue.h"
#include "uthread.h"


typedef struct {
  uthread_t tid;
  uthread_ctx_t* context;
  enum State{ready, running, blocked, zombie}state;
  void* stack;
}TCB;

static int thread_Number = 0;
queue_t ready_queue, blocked_queue, zombie_queue,  running_queue;
TCB* running_thread;


void uthread_yield(void)
{
  TCB* future_thread;
  TCB* currently_active;
  queue_dequeue(ready_queue, (void**)&future_thread);
  queue_dequeue(running_queue, (void**)&currently_active);
  if (currently_active->state == running){
    currently_active->state = ready;
  }
  if(currently_active->state != zombie && currently_active->state != blocked){
    queue_enqueue(ready_queue, currently_active);
  }
  //queue_dequeue(ready_queue, void(**)&temp_thread);
  queue_enqueue(running_queue, future_thread);
  running_thread = future_thread;
  uthread_ctx_switch(currently_active->context, future_thread->context);
}

uthread_t uthread_self(void)
{
  return running_thread->tid;
}

int uthread_create(uthread_func_t func, void *arg)
{

  if(thread_Number == 0){ // Main thread is tid of 0 and is always running
    TCB *thread_0 =(TCB*)malloc(sizeof(TCB));
    // we need a queue


    ready_queue = queue_create();
    running_queue = queue_create();
    blocked_queue = queue_create();
    zombie_queue = queue_create();
    //Error check this malloc
    thread_0->tid = thread_Number;
    thread_0->context = malloc(sizeof(uthread_ctx_t));
    thread_0->stack = NULL;
    thread_0->state = running;
    getcontext(thread_0->context);
    running_thread = thread_0;
    queue_enqueue(running_queue, thread_0);
  }
  thread_Number++;
  //Else we create a thread which we call the TCB
  TCB* new_thread = (TCB*)malloc(sizeof(TCB));
  new_thread->tid = thread_Number;
  new_thread->context = malloc(sizeof(uthread_ctx_t));
  new_thread->stack = uthread_ctx_alloc_stack();
  //State is ready to run
  new_thread->state = ready;
  uthread_ctx_init( new_thread->context, new_thread->stack, func, arg);
  // add this to a queue
  queue_enqueue(ready_queue, new_thread);
  return new_thread->tid;
}

void uthread_exit(int retval)
{
  running_thread->state = zombie;
  // uthread_ctx_bootstrap(running_thread, retval);
  // Only do this if running thread has no parent thread
//  queue_enqueue(zombie_queue,running_thread);
//  else{
//    we enqueue the parent thread
//  }

}

int uthread_join(uthread_t tid, int *retval)
{ while(1){
  uthread_yield();
  if(queue_length(ready_queue) == 0){
    break;
  }
}

  /* TODO Phase 2 */
  /* TODO Phase 3 */
  return 0;
}
