#include <assert.h>
#include <stdlib.h>

#include "queue.h"

/**
 * Struct to define a queue
 * back: Index of the last element in the queue
 * front: Index of the first element in the queue
 * size: Number of elements in the queue
 * capacity: Maximum number of elements the queue can hold
 * data: Pointer to the array that holds the elements of the queue
 */
struct queue{
  unsigned int back;
  unsigned int front;
  unsigned int size;
  unsigned int capacity;
  long *data;
};

/** 
 * Construct a new empty queue.
 *
 * Returns a pointer to a newly created queue.
 * Return NULL on error
 */
queue_t *queue_new(unsigned int capacity) {
  // Allocate memory for the queue structure
  queue_t *q = (queue_t *) malloc(sizeof(queue_t));
  if (!q) return NULL;

  // Allocate memory for the array that holds the elements of the queue
  q->data = (long *) malloc(capacity * sizeof(long));
  if (!q->data) {
    // If allocation fails, deallocate memory for the queue structure and return NULL
    free(q);
    return NULL;
  }

  // Initialize the back, front, size and capacity variables
  q->back = 0;
  q->front = 0;
  q->size = 0;
  q->capacity = capacity;

  // Return the pointer to the newly created queue
  return q;
}

/**
 * Check if the queue is empty
 *
 * Returns 1 if the queue is empty, 0 otherwise
 */
int queue_empty(queue_t *q) {
  // Ensure the queue is not NULL
  assert(q != NULL);

  // Return whether the size of the queue is 0
  return (q->size == 0);
}

/**
 * Check if the queue is full
 *
 * Returns 1 if the queue is full, 0 otherwise
 */
int queue_full(queue_t *q) {
  // Ensure the queue is not NULL
  assert(q != NULL);

  // Return whether the size of the queue is equal to its capacity
  return (q->size == q->capacity);
}

/**
 * Add an item to the back of the queue
 */
void queue_enqueue(queue_t *q, long item) {
  // Ensure the queue is not NULL and not full
  assert(q != NULL);
  assert(!queue_full(q));

  // Add the item to the data array at the back index
  q->data[q->back] = item;

  // Increment the back index with wraparound
  q->back = (q->back + 1) % q->capacity;

  // Increment the size of the queue
  q->size++;
}

/**
 * Remove and return the item at the front of the queue
 *
 * Returns the removed item
 * Dequeue an item.
 *
 * Returns the item at the front of the queue and removes an item from the 
 * queue.
 *
 * Note: Removing from an empty queue is an undefined behavior (i.e., it could 
 * crash the program)
 */
long queue_dequeue(queue_t *q) {
  assert(q != NULL);
  assert(!queue_empty(q));

  long item = q->data[q->front];
  q->front = (q->front + 1) % q->capacity;
  q->size--;

  return item;
}

/** 
 * Queue size.
 *
 * Queries the current size of a queue (valid size must be >= 0).
 */
unsigned int queue_size(queue_t *q) {
  // Ensure the queue is not NULL and not full
  assert(q != NULL);

  return q->size;
}

/** 
 * Remove the queue and all of its elements from memory.
 *
 */
void queue_delete(queue_t* q) {
  // Ensure the queue is not NULL and not full
  assert(q != NULL);

  free(q->data);
  free(q);
}
