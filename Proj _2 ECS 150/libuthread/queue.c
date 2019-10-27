#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "queue.h"


struct Node {
  void *data;
  struct Node* nextNode;
};

struct queue {
  struct Node* front;
  struct Node* rear;
  int size;
};

queue_t queue_create(void)
{
  queue_t queue = (queue_t)malloc(sizeof(queue_t));
  queue->front = NULL;
  queue->rear = NULL;
  queue->size = 0;
  return queue;
}

int queue_destroy(queue_t queue)
{
  if (!(queue->front == NULL && queue->rear == NULL) || !queue) {
    return -1;
  } else {
    free(queue);
    return 0;
  }
}

int queue_enqueue(queue_t queue, void *data)
{
  struct Node* tempNode = (struct Node*)malloc(sizeof(struct Node*));
  if (!tempNode) {
    return -1;
  }
  tempNode->data = data;
  tempNode->nextNode = NULL;
  if (queue->front == NULL && queue->rear == NULL) { //if the list is empty
    queue->front = tempNode;
    queue->rear = tempNode;
  }
  queue->rear->nextNode = tempNode;
  queue->rear = tempNode;
  queue->size++;
  return 0;
}

int queue_dequeue(queue_t queue, void **data)
{
  struct Node* tempNode = queue->front;
  if (queue->front == NULL || data == NULL)
    return -1;
  if (queue->front == queue->rear) {
    queue->front = NULL;
    queue->rear = NULL;
  } else {
    queue->front = queue->front->nextNode;
  }
  *data = tempNode->data;
  free(tempNode);
  queue->size--;
  return 0;
}



int queue_iterate(queue_t queue, queue_func_t func, void *arg, void **data)
{
  int funcFlag = 0;
  if(!queue || !func){
    return -1;
  }

  struct Node* tempNode = queue->front;
  while (tempNode != NULL) {
    funcFlag = func(tempNode->data, arg);
    if (funcFlag == 1) {
      if (data != NULL) {
        *data = tempNode->data;
        break;
      }
    }
    tempNode = tempNode->nextNode;
  }

  return 0;
}

/*
 * queue_delete - Delete data item
 * Find in queue @queue, the first (ie oldest) item equal to @data and delete
 * this item->
 * Return: -1 if @queue or @data are NULL, of if @data was not found in the
 * queue-> 0 if @data was found and deleted from @queue->
 */
int queue_delete(queue_t queue, void *data){

  struct Node* tempNode = queue->front;
  struct Node* prevNode;

  // base case: if the head has the Data
  if (tempNode != NULL && tempNode->data == data) {
    queue->front = tempNode->nextNode;
    free(tempNode);
    return 0;
  }

  while (tempNode != NULL && tempNode->data != data) {
    prevNode = tempNode;
    tempNode = tempNode->nextNode;
  }

  if (tempNode == NULL) {
    return -1;
  }

  // Unlink the node from the list
  prevNode->nextNode = tempNode->nextNode;
  free(tempNode);
  queue->size--;

  return 0;
}

int queue_length(queue_t queue)
{
  if(!queue)
    return -1;
  return queue->size;
}
