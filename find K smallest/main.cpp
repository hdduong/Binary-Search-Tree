#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	node* left;
	node* right;
};

node* newNode(int data) {
	node* aNode = (node*)malloc(sizeof(node));
	aNode->data = data;
	aNode->left = aNode->right = NULL;
	return aNode;
}

void printTreePreOrder(node *root) {
	if (root == NULL)
		return;
	printf("%d ",root->data);
	printTreePreOrder(root->left);
	printTreePreOrder(root->right);
}

node* insertNode(node* root, int data) {
	if (root == NULL)
		return newNode(data);

	if (root->data > data) {
		root->left = insertNode(root->left,data);
	}
	else if (root->data < data) {
		root->right = insertNode(root->right,data);
	}

	return root;
}

node* printKSmallest(node *root, int* currentK, int *k) {
	if (root == NULL)
		return NULL;

	node* tmp = NULL;
	tmp = printKSmallest(root->left,currentK,k);

	if (tmp == NULL) {
		(*currentK)++;
		if (*currentK == *k) //found
			return root;
	}
	else {
		// tmp is the node
		return tmp;
	}
	if (tmp == NULL)
		tmp = printKSmallest(root->right,currentK,k);
	return tmp;
}

void main() {
	node* root = NULL;
	root = insertNode(root,20);
	root = insertNode(root, 8);
	root = insertNode(root, 22);
	root = insertNode(root, 4);
	root = insertNode(root, 12);
	root= insertNode(root, 10);
	root = insertNode(root, 14);
	printTreePreOrder(root);
	printf("\n");

	node* tmp = NULL;
	int currentK = 0;
	int k = 7;
	tmp = printKSmallest(root, &currentK, &k);
	if (tmp!=NULL) {
		printf("%d \n", tmp->data);
	}
	
}