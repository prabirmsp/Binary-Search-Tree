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

// search - returns the value at the key, or -1 if key is not found
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
  tree = insert(tree, 9, 13);
  tree = insert(tree, 1, 0);
  tree = insert(tree, 3, 0);
  print_tree(tree);

  int val = search(tree, 9);
  printf("search 9: %d\n", val);

  val = search(tree, 99);
  printf("search 99: %d\n", val);

  tree = delete(tree, 5);
  print_tree(tree);

  tree = delete(tree, 3);
  print_tree(tree);

  for (int i = 0; i < 10000; i++) {
    tree = insert(tree, rand() % 10000, 0);
  }

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



node *insert(node * cur, int key, int value) {

  if (cur == NULL) // base case
    return new_node(key, value);

  if (key == cur->key) // update value if there is already a value with the same key
    cur->value = value;
  else if (key < cur->key)
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


node *delete(node *cur, int key) {
  if (cur == NULL)
    return cur;
  if (key < cur->key)
    cur->left = delete(cur->left, key);
  else if (key > cur->key)
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


int search(node *cur, int key) {
  if (cur == NULL) 
    return -1;
  else if (key < cur->key)
    return search(cur->left, key);
  else if(key > cur->key)
    return search(cur->right, key);
  else 
    return cur->value;
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
