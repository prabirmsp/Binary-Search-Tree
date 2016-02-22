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

int main(int argc, char **argv) {

  if (argc != 2) {
    printf("Wrong arguments. (Eample: program textfile.txt\n");
    return 0;
  }

  char * filename = argv[1];
 
  FILE * input = fopen(filename, "r");

  char buffer [BUFFER_SIZE];

  node * tree = NULL;

  clock_t begin, end;
  double time_spent;

  begin = clock();
  while(fscanf(input, "%s", buffer) != EOF) {

    char * word = malloc((strlen(buffer) + 1) * sizeof(char));
    if (word == NULL) {
      printf("Memory Error.\n");
      return 1;
    }
  
    strcpy(word, buffer);
    tree = add_word(tree, word);
  }
  end = clock();
  time_spent = ((double) (end - begin)) / CLOCKS_PER_SEC;
  time_spent *= 1000000000;
  printf("Tree created. Time taken: %.16f * 10^(-9) secs.\n", time_spent);
  
  begin = clock();
  node * max = find_max_value(tree);
  end = clock();
  time_spent = ((double) (end - begin)) / CLOCKS_PER_SEC;
  time_spent *= 1000000000;
  printf("Max: (%s, %d). Time taken: %.16f * 10^(-9) secs\n", 
         max->key, max->value, time_spent);

  //print_tree(tree);

  return 0;
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
