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

void printTreeInOrder(node *root) {
	if (root == NULL)
		return;
	printTreeInOrder(root->left);
	printf("%d ",root->data);
	printTreeInOrder(root->right);
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

int findNexBiggerItem(int arr[], int size, int start) {
	int k = start;
	for (int i = start; i < size; i++) {
		if (arr[i] > arr[start])
			return i;
	}
	return INT_MIN;
}

node *buldBSTPreOrder(int arr[], int size, int start, int end) {

	if (start > end) return NULL;

	if (start == end) return newNode(arr[start]);

	node* root = newNode(arr[start]);

	int k = findNexBiggerItem(arr,size,start + 1); //next item of root

	root->left = buldBSTPreOrder(arr,size,start+1,k-1);
	root->right = buldBSTPreOrder(arr,size,k,end);


	return root;
}

void main() {
	int array[6] = {10,5,1,7,40,50};
	int start = 0;
	int end = 5;
	int size = 6;

	node* root = NULL;
	root = buldBSTPreOrder(array, size,start,end);
	printTreePreOrder(root);
	printf("\n");
}