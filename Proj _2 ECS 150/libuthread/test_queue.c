#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "queue.h"
#include "queue.c"

static int inc_item(void *data, void *arg)
{
    int *a = (int*)data;
    int inc = (int)(long)arg;

    *a += inc;

    return 0;
}

/* Callback function that finds a certain item according to its value */
static int find_item(void *data, void *arg)
{
    int *a = (int*)data;
    int match = (int)(long)arg;

    if (*a == match)
        return 1;

    return 0;
}

void test_iterator(void)
{
    queue_t q;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int i;
    int *ptr;

    /* Initialize the queue and enqueue items */
    q = queue_create();
    for (i = 0; i < sizeof(data) / sizeof(data[0]); i++)
        queue_enqueue(q, &data[i]);

    /* Add value '1' to every item of the queue */
    queue_iterate(q, inc_item, (void*)1, NULL);
    assert(data[0] == 2);

    struct Node* temp = q->front;
    while (temp != NULL) {
      printf("%d ", *(int*)temp->data);
      temp = temp->nextNode;
    }
    printf("\n");


    /* Find and get the item which is equal to value '5' */
    ptr = NULL;
    queue_iterate(q, find_item, (void*)5, (void**)&ptr);
    assert(ptr != NULL);
    assert(*ptr == 5);
    assert(ptr == &data[3]);
}

void test_length(void) {
  queue_t q;
  q = queue_create();
  int intArr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for(int i = 0; i < 10; i++) {
    queue_enqueue(q, &intArr[i]);
  }
  int qSize = queue_length(q);
  assert(qSize == 10);
}

void test_create(void)
{
    queue_t q;

    q = queue_create();
    assert(q != NULL);
}

void test_destroy(void)
{
  int flag;
  queue_t emptyQ = queue_create();
  flag = queue_destroy(emptyQ);
  assert(flag == 0);
}


 void test_delete(void)
 {
   int intArr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   queue_t qInt = queue_create();

   for(int i = 0; i < 10; i++) {
     queue_enqueue(qInt, &intArr[i]);
   }

   struct Node* temp = qInt->front;
   while (temp != NULL) {
     printf("%d ", *(int*)temp->data);
     temp = temp->nextNode;
   }
   printf("\n");

   queue_delete(qInt, &intArr[3]);

   assert(intArr[3] == 5);

   // temp = qInt->front;
   // while (temp != NULL) {
   //   printf("%d ", *(int*)temp->data);
   //   temp = temp->nextNode;
   // }
   // printf("\n");

 }

void test_queue_simple(void)
{
    //queue_t q;
    //int data = 3
    //int *ptr;
    int intArr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    char charArr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    queue_t qInt = queue_create();
    queue_t qChar = queue_create();

    for(int i = 0; i < 10; i++) {
      queue_enqueue(qInt, &intArr[i]);
    }
    for(int i = 0; i < 10; i++) {
      queue_enqueue(qChar, &charArr[i]);
    }

    // struct Node* temp = qInt->front;
    // while (temp != NULL) {
    //   printf("%d ", *(int*)temp->data);
    //   temp = temp->nextNode;
    // }
    // printf("\n");
    //
    // temp = qChar->front;
    // while (temp != NULL) {
    //   printf("%c ", *(char*)temp->data);
    //   temp = temp->nextNode;
    // }
    // printf("\n, removing data...");
    // for(int i = 0; i < 10; i++) {
    //   queue_dequeue(qInt, (void**)&ptr);
    // }
    // temp = qInt->front;
    // assert(temp == NULL);

}


int main(int argc, char *argv[]) {
  test_create();
  // test_queue_simple();
  // test_delete();
  // test_iterator();
  test_length();
  test_destroy();
  return 0;
}
