#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
  int key;
  int value;
  struct Node *left;
  struct Node *right;
} Node;



// insert
void insert(Node ** tree, int key, int value);

// delete
void delete(Node * tree, int key);

// search
int search(Node * tree, int key);

// print in order
void print_tree(Node * tree);

void print_helper(Node * cur);

int main() {

  Node * tree = NULL;

  insert(&tree, 5, 0);
  insert(&tree, 4, 0);
  insert(&tree, 8, 0);
  insert(&tree, 2, 0);
  insert(&tree, 5, 0);
  insert(&tree, 7, 0);
  insert(&tree, 9, 0);
  insert(&tree, 1, 0);
  insert(&tree, 3, 0);
  
  print_tree(tree);

}


void insert(Node ** tree, int key, int value) {
  printf("inserting... %d\n", key);
  Node *cur = *tree;

  while (cur != NULL) {

    if (cur->key == key) {
      // update the value
      cur->value = value;
      return;
    } else if (cur->key < key) { 
      printf("%d", cur->key);
      // go to left subtree
      cur = cur->left;
    } else {
      printf("%d", cur->key);
      // go to the right subtree
      cur = cur->right;
    }
  }  

  // create new node
  Node * new_node = malloc(sizeof(Node));
  // check allocated memory
  if (new_node == NULL) {
    printf("Malloc Error\n");
    return;
  }
  
  // add the key/values
  new_node->key = key;
  new_node->value = value;
  new_node->left = NULL;
  new_node->right = NULL;

  cur = new_node;
}


void print_tree(Node * tree) {
  printf("Printing tree... ");
  print_helper(tree);
  printf("\n");
}

void print_helper(Node *cur) {
  if (cur == NULL)
    return;
  print_helper(cur->left);
  printf("%d ", cur->key);
  print_helper(cur->right);
}
