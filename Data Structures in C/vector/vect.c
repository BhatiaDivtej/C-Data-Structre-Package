/**
 * Vector implementation.
 *
 * This code implements a growable array, also known as a vector. The functions provided in the code allow you to create a new vector, delete a vector, get an element from the vector, set an element in the vector, add an element to the vector, remove the last element from the vector, get the size of the vector and get the current capacity of the vector.
 * 
 * Do not change any of the structs.
 * 
 * The initial capacity and the vector's growth factor are expressed in terms of the configuration constants in vect.h.
 */
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "vect.h"

/**
 * Main data structure for the vector.
 * 
 * This structure holds the actual data of the vector, the size of the vector (number of items currently in the vector), and the capacity of the vector (maximum number of items the vector can hold before growing).
 */
struct vect {
  char **data;             /* Array containing the actual data. */
  unsigned int size;       /* Number of items currently in the vector. */
  unsigned int capacity;   /* Maximum number of items the vector can hold before growing. */
};

/**
 * Construct a new empty vector.
 * 
 * This function creates a new vector and returns a pointer to it. The size of the vector is set to 0 and the capacity is set to VECT_INITIAL_CAPACITY, which is defined in vect.h. The data array is also allocated memory.
 */
vect_t *vect_new() {
  vect_t *v = (vect_t *)malloc(sizeof(vect_t));
  v->size = 0;
  v->capacity = VECT_INITIAL_CAPACITY;
  v->data = (char **)malloc(v->capacity * sizeof(char *));
  return v;
}

/**
 * Delete the vector, freeing all memory it occupies.
 * 
 * This function deletes a vector, freeing all memory it occupies. It first frees the memory occupied by each element in the data array, then frees the memory occupied by the data array and finally frees the memory occupied by the vector itself.
 */
void vect_delete(vect_t *v) {
  assert(v != NULL);
  for (unsigned int i = 0; i < v->size; i++) {
    free(v->data[i]);
  }
  free(v->data);
  free(v);
}

/**
 * Get the element at the given index.
 * 
 * This function returns the element at the given index in the vector. It checks if the vector and the index are valid and returns the element if they are.
 */
const char *vect_get(vect_t *v, unsigned int idx) {
  assert(v != NULL);
  assert(idx < v->size);
  return v->data[idx];
}

/** Get a copy of the element at the given index. The caller is responsible
 *  for freeing the memory occupied by the copy. */
char *vect_get_copy(vect_t *v, unsigned int idx) {
  assert(v != NULL);
  assert(idx < v->size);
  char *copy = (char *)malloc((strlen(v->data[idx]) + 1) * sizeof(char));
  strcpy(copy, v->data[idx]);
  return copy;
}



/** Set the element at the given index. */
void vect_set(vect_t *v, unsigned int idx, const char *elt) {
  assert(v != NULL);
  assert(idx < v->size);
  free(v->data[idx]);
  v->data[idx] = (char *)malloc((strlen(elt) + 1) * sizeof(char));
  strcpy(v->data[idx], elt);
}


/** Add an element to the back of the vector. */
void vect_add(vect_t *v, const char *elt) {
  assert(v != NULL);
  if (v->size == v->capacity) {
    v->capacity *= VECT_GROWTH_FACTOR;
    v->data = (char **)realloc(v->data, v->capacity * sizeof(char *));
  }
  v->data[v->size] = (char *)malloc((strlen(elt) + 1) * sizeof(char));
  strcpy(v->data[v->size], elt);
  v->size++;
}

/** Remove the last element from the vector. */
void vect_remove_last(vect_t *v) {
  assert(v != NULL);
  assert(v->size > 0);
  v->size--;
  free(v->data[v->size]);
}

/** The number of items currently in the vector. */

unsigned int vect_size(vect_t *v) {
  assert(v != NULL);
  return v->size;
}

/** The maximum number of items the vector can hold before it has to grow. */
unsigned int vect_current_capacity(vect_t *v) {
  assert(v != NULL);
  return v->capacity;
}

