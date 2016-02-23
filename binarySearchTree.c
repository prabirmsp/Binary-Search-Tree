 /***************************************************
  * Binary Search Tree Dictionary
  *
  * Prabir Pradhan
  * CSC-301, Ursula Wolz
  * 
  *
  *
  *****************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/time.h>

#define BUFFER_SIZE 64

typedef struct node {
  char * key;
  int value;
  struct node *left;
  struct node *right;
} node;

// add_word - adds the word to the tree (increment value by 1)
node * add_word(node * tree, char * key);

// insert - returns the pointer to the tree with the key-value pair inserted 
node * insert(node * tree, char * key, int value);

// delete
node * delete(node * tree, char * key);

// search - returns the value at the key, or -1 if key is not found
int search(node * tree, char * key);

// print in order
void print_tree(node * tree);

// find the word with the highest occurance (value)
node * find_max_value(node * tree);


// helpers
void print_helper(node * cur);
void find_max_helper(node * cur, node ** max);
void time_print(struct timeval start, struct timeval end);

void tolowercase(char * s) {
  for (int i = 0; i < strlen(s); i++) {
    s[i] = tolower(s[i]);
  }
}

int main(int argc, char **argv) {
  struct timeval start, end;

  if (argc != 5) {
    printf("Wrong arguments.\nUsage: program textfile.txt get_word insert_word delete_word\n");
    return 0;
  }

  char * filename = argv[1];
 
  FILE * input = fopen(filename, "r");

  char buffer [BUFFER_SIZE];

  node * tree = NULL;

  clock_t begin, endd;
  double time_spent;


  // insert all 
  begin = clock();
  gettimeofday(&start, NULL);

  while(fscanf(input, "%s", buffer) != EOF) {

    char * word = malloc((strlen(buffer) + 1) * sizeof(char));
    if (word == NULL) {
      printf("Memory Error.\n");
      return 1;
    }
  
    strcpy(word, buffer);
    tolowercase(word);
    tree = add_word(tree, word);
  }
  endd = clock();
  gettimeofday(&end, NULL);
  time_spent = ((double) (endd - begin)) / CLOCKS_PER_SEC;
  time_spent *= 1000000;
  printf("Tree created. Time taken: %f * 10^(-6) secs.\n", time_spent);
  time_print(start, end);

  // search
  gettimeofday(&start, NULL);
  int s = search(tree, argv[2]);
  gettimeofday(&end, NULL);
  printf("Search for: (%s, %d)\n", argv[2], s);
  time_print(start, end);

  // insert one
  gettimeofday(&start, NULL);
  tree = add_word(tree, argv[3]);
  gettimeofday(&end, NULL);
  printf("Insert: %s\n", argv[3]);
  time_print(start, end);

  // delete

  gettimeofday(&start, NULL);
  tree = delete(tree, argv[4]);
  gettimeofday(&end, NULL);
  printf("Delete word: %s\n", argv[4]);
  time_print(start, end);

  // max
  begin = clock();
  gettimeofday(&start, NULL);
  node * max = find_max_value(tree);
  gettimeofday(&end, NULL);
  endd = clock();
  time_spent = ((double) (endd - begin)) / CLOCKS_PER_SEC;
  time_spent *= 1000000;
  printf("Max: (%s, %d). Time taken: %f * 10^(-6) secs\n", 
         max->key, max->value, time_spent);
  time_print(start, end);

  //print_tree(tree);

  return 0;
}

void time_print(struct timeval start, struct timeval end) {
  int u_sec = ((end.tv_sec - start.tv_sec)*1000000L
           +end.tv_usec) - start.tv_usec;
  printf("Time in microseconds: %d microseconds ", u_sec);
  printf("(%f ms)\n\n", u_sec/1000.0);
}


node *new_node(char * key, int value) {
  // create new node
  node * new_node = malloc(sizeof(node));
  // check allocated memory
  if (new_node == NULL) {
    printf("Malloc Error\n");
    return NULL;
  }
  // add the key/values
  new_node->key = key;
  new_node->value = value;
  new_node->left = NULL;
  new_node->right = NULL;

  return new_node;
}


node *add_word(node * cur, char * key){

  if (cur == NULL) // base case
    return new_node(key, 1);

  if (strcmp(key, cur->key) == 0) // increment value if word found in tree
    (cur->value)++;
  else if (strcmp(key, cur->key) < 0)
    cur->left = add_word(cur->left, key);
  else 
    cur->right = add_word(cur->right, key);
  return cur;
}


node *insert(node * cur, char * key, int value) {

  if (cur == NULL) // base case
    return new_node(key, value);

  if (strcmp(key, cur->key) == 0) // update value if there is already a value with the same key
    cur->value = value;
  else if (strcmp(key, cur->key) < 0)
    cur->left = insert(cur->left, key, value);
  else 
    cur->right = insert(cur->right, key, value);
  return cur;
}


node *next_inorder(node *cur) {
  if (cur->left == NULL)
    return cur;
  return next_inorder(cur->left);
}


node *delete(node *cur, char * key) {
  if (cur == NULL)
    return cur;
  if (strcmp(key, cur->key) < 0)
    cur->left = delete(cur->left, key);
  else if (strcmp(key, cur->key) > 0)
    cur->right = delete(cur->right, key);
  else {
    if (cur->left == NULL && cur->right == NULL) {      // has no children
      free(cur);
      cur = NULL;
    }
    else if (cur->left == NULL && cur->right != NULL) { // has right child only
      node * old_node = cur;
      cur = cur->right;
      free(old_node);
      cur = NULL;
    }
    else if (cur->left != NULL && cur->right == NULL) { // has left child only
      node * old_node = cur;
      cur = cur->left;
      free(old_node);
      cur = NULL;
    }
    else {                                              // has left and right children
      node *next = next_inorder(cur->right);
      cur->key = next->key;
      cur->value = next->value;
      cur->right = delete(cur->right, next->key);
    }
  }
  return cur;
}


int search(node *cur, char * key) {
  if (cur == NULL) 
    return -1;
  else if (strcmp(key, cur->key) < 0)
    return search(cur->left, key);
  else if (strcmp(key, cur->key) > 0)
    return search(cur->right, key);
  else 
    return cur->value;
}


node * find_max_value(node * tree) {
  node * max = tree;
  find_max_helper(tree, &max);
  return max;
}

void find_max_helper(node * cur, node ** max) {
  if (cur == NULL)
    return;
  find_max_helper(cur->left, max);
  if (cur->value > (*max)->value)
    *max = cur;
  find_max_helper(cur->right, max);
}



void print_tree(node * tree) {
  printf("Printing tree... ");
  print_helper(tree);
  printf("\n");
}

void print_helper(node *cur) {
  if (cur == NULL)
    return;
  print_helper(cur->left);
  printf("(%s, %d) ", cur->key, cur->value);
  print_helper(cur->right);
}
