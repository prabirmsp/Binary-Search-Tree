#import <stdio.h>
#import "binarySearchTree.c"

int main() {

	const char * filename = "sample.txt";

	FILE * input = fopen(filename, "r");

	char * buffer = char[sizeof(char) * 64];

	node * tree = NULL;

	while((buffer = fscanf(input, "%s", buffer)) != EOF) {

		char * word = char[strlen(buffer) + 1];
		strcpy(word, buffer);
		tree = insert(tree, key, value);
	}


	return 0;
}