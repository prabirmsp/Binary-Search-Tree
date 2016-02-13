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


typedef struct node {
  int key;
  int value;
  struct node *left;
  struct node *right;
} node;



// insert - returns the pointer to the tree with the key-value pair inserted 
node * insert(node * tree, int key, int value);

// delete
node *delete(node * tree, int key);

// search
int search(node * tree, int key);

// print in order
void print_tree(node * tree);

void print_helper(node * cur);

int main() {

  node * tree = NULL;

  tree = insert(tree, 5, 0);
  tree = insert(tree, 4, 0);
  tree = insert(tree, 8, 0);
  tree = insert(tree, 2, 0);
  tree = insert(tree, 7, 0);
  tree = insert(tree, 9, 0);
  tree = insert(tree, 1, 0);
  tree = insert(tree, 3, 0);
  print_tree(tree);

  tree = delete(tree, 5);
  print_tree(tree);

  tree = delete(tree, 3);
  print_tree(tree);

  return 0;
}


node *new_node(int key, int value) {
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



node *insert(node * node, int key, int value) {

  if (node == NULL) // base case
    return new_node(key, value);

  if (key == node->key) // update value if there is already a value with the same key
    node->value = value;
  else if (key < node->key)
    node->left = insert(node->left, key, value);
  else 
    node->right = insert(node->right, key, value);
  return node;
}


node *next_inorder(node *node) {
  if (node->left == NULL)
    return node;
  return next_inorder(node->left);
}


node *delete(node *node, int key) {
  if (node == NULL)
    return node;
  if (key < node->key)
    node->left = delete(node->left, key);
  else if (key > node->key)
    node->right = delete(node->right, key);
  else {
    if (node->left == NULL && node->right == NULL) {      // has no children
      free(node);
      node == NULL;
    }
    else if (node->left == NULL && node->right != NULL) { // has right child only
      node *old_node = node;
      node = node->right;
      free(old_node);
    }
    else if (node->left != NULL && node->right == NULL) { // has left child only
      node *old_node = node;
      node = node->left;
      free(old_node);
    }
    else {                                              // has left and right children
      node *next = next_inorder(node->right);
      node->key = next->key;
      node->value = next->value;
      node->right = delete(node->right, next->key);
    }
  }
  return node;
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
  printf("%d ", cur->key);
  print_helper(cur->right);
}
