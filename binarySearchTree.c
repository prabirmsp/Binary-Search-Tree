#include <stdio.h>


typedef struct node {
  int key;
  int value;
  node* left;
  node* right;
} node;

typedef node ** bst;


// insert
void insert(bst tree, int key, int value);

// delete
void delete(bst tree, int key);

// search
int search(bst tree, int key);

int main() {
  

}


void insert(bst tree, int key, int value) {

{
  // create new node
  node * new_node = malloc(sizeof(node));
  // check allocated memory
  if (first == NULL) {
    printf("Malloc Error\n");
    return;
  }
  // add the key/values
  new_node->key = key;
  new_node->value = value;

  if (tree == NULL) { // tree is empty
    tree = &new_node;
  } else { // tree is not empty
    node cur = *tree;

    while (cur != NULL) {
      

    }



  }
}
