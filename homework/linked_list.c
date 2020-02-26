#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef double VALUE;
typedef struct ListEntry_s {
  struct ListEntry_s* next;
  VALUE value;
} ListEntry;
typedef ListEntry* POINTER;

// This function takes a value, puts it in an Entry, and returns a pointer to that Entry (its index) to us.
POINTER alloc(VALUE value) {
  // Ask the OS for some memory of the correct size.
  POINTER step = (POINTER) malloc(sizeof(ListEntry));
  assert(step != NULL);

  step->next = NULL;
  step->value = value;

  return step;
}

// How do you count the items in a linked list?
int list_size(POINTER start) {
  // TODO, does nothing right now.
  POINTER temp = start;
  int count = 0;
  while (temp != NULL){
    temp =  temp->next;
    count++;
  }
  return count;
}

// How do you add an item to the end of a linked list?
void push_back(POINTER start, VALUE value) {
  // TODO, does nothing right now.
  POINTER new =  alloc(value);
  assert(new != NULL);
  POINTER temp = start;
  while(temp->next != NULL){
    temp = temp->next;
  }
  temp->next = new;
  return;
}

bool list_equals_array(POINTER list, double* array, int array_len) {
  if (list_size(list) != array_len) return false;
  // TODO, do this better!
  POINTER cur = list;
  int i = 0;
  while(cur != NULL && (i < array_len)){
   if (cur->value !=  *(array + i)){
     return false;
   }
   cur = cur->next;
   i++;
  }  
  return true;
}

// Given a value and a list, alloc a new entry and put it on the front of this list.
POINTER push_front(VALUE value, POINTER list) {
  POINTER new = alloc(value);
  assert(new != NULL);
  new->next = list;
  return new;
}

// Given the start of a list and a value, remove the list node in the list
// return 1 for successfully remove, 0 for no such value exist
// for example: 1->2->3->4->5 remove value 3
// the list becomes: 1->2->4->5
bool remove_value(POINTER start, VALUE value){
  //TODO
  POINTER cur = start;
  POINTER prev = start;
  while(cur != NULL){
    if(cur->value == value){
      prev = cur->next;
      return 1;
    } else{
      prev = cur;
      cur = cur->next;
    }
  }
  return 0;
}

// Given the start of a list, reverse the list and return the start after the reverse
// for example: 1->2->3->4->5 reverse
// the list becomes: 5->4->3->2->1
POINTER reverse_list(POINTER start){
  //TODO
  POINTER prev = NULL;
  POINTER cur = start;
  POINTER next = NULL;
  while (cur != NULL){
    next = cur->next;
    cur->next = prev;
    
    prev = cur;
    cur = next;
  }
  return start;
}

// Given a list, take its first element off and put it in the free list.
POINTER free_front(POINTER list) {
  // Don't do anything with empty lists.
  assert(list != NULL);

  // What is leftover of this list once we chop the first one off?
  POINTER leftover = list->next;

  // What is created by malloc is destroyed by free.
  free(list);

  // return the rest of this linked list.
  return leftover;
}

// This function demonstrates writing one of our linked lists to a particular file.
void fprint_list(FILE* f, POINTER start) {
  for(POINTER x = start; x != NULL; x = x->next) {
    fprintf(f, "%1.3f ", x->value);
  }
  fprintf(f, "\n");
}
// This is the difference between printf and fprintf:
void print_list(POINTER start) {
  fprint_list(stdout, start);
}

// Use test.txt as command line input
int main(int argc, char **argv) {
  assert(argv != NULL);
  assert(argc == 2);

  FILE* input = fopen(argv[1], "r");
  assert(input != NULL);

  // Create a list of [9,8,7]
  POINTER test_list = push_front(9.0, push_front(8.0, alloc(7.0)));

  // Print test_list.
  printf("Test List:\t");
  fprint_list(stdout, test_list);

  // Create a pointer to hold a list from our file.
  POINTER file_list = NULL;

  // Load up entries from a file.
  while (true) {
    double value;
    // Read a floating point value from the input file.
    int status = fscanf(input, "%lf", &value);
    if (status == EOF) break;
    if (status != 1) {
      // Be nice about errors and quit if we get the wrong file.
      fprintf(stderr, "Unable to read a value, fscanf -> %d", status);
      return -1;
    }

    // Add the value we read into the list.
    file_list = push_front(value, file_list);
  }

  // Make sure we read the things we wanted to read.
  printf("File List:\t");
  fprint_list(stdout, file_list);

  // Print test_list; show that it still works -- reading from the file should not have changed this!
  printf("Test List:\t");
  fprint_list(stdout, test_list);

  // Now test the functions we wrote:
  assert(list_size(test_list) == 3);

  // Add an item, check that size increases:
  push_back(test_list, 1.0);
  assert(list_size(test_list) == 4);

  // Now make sure the list is actually correct.
  double expected[] = {9,8,7,1};
  assert(list_equals_array(test_list, expected, 4));

  //remove an item, check correctness
  double expected_remove[] = {9,8,1};
  remove_value(test_list, 7.0);
  assert(list_equals_array(test_list, expected_remove, 3));

  double expected_remove2[] = {8,1};
  remove_value(test_list, 9.0);
  assert(list_equals_array(test_list, expected_remove2, 2));

  //reverse the list, check correctness
  push_back(test_list, 10);
  push_back(test_list, 3.14);
  double expected_reverse[] = {3.14,10,1,8};
  assert(list_equals_array(reverse_list(test_list), expected_reverse, 4));

  return 0;
}
