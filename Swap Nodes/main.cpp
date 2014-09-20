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

void swapNode(node *root, node** prev, node** nodeSwap1, node** nodeSwap2) {
	if (root == NULL) 
		return;

	swapNode(root->left, prev, nodeSwap1, nodeSwap2);
	if ((*prev!= NULL) && (*prev) != root) {
		if ( (*prev)->data > root->data )
			if (*nodeSwap1 == NULL)
				*nodeSwap1 = *prev;
			
	}
	if  ((*prev!= NULL) && (*prev) != root) {
		if ( (*prev)->data > (root->data) )
			if (*nodeSwap1 != NULL)
			*nodeSwap2 = root;
	}

	*prev = root;
	swapNode(root->right, prev, nodeSwap1, nodeSwap2);

}

void swapValue(node* swap1, node* swap2) {
	int data = swap1->data;
	swap1->data = swap2->data;
	swap2->data = data;
}

void main() {
	
	node* swapNode1 = NULL;
	node* swapNode2 = NULL;
	node* prev = NULL;

	// case when 2 nodes are adjacent
	node* root1 = newNode(7);
	root1->left = newNode(5);
	root1->right = newNode(20);

	root1->left->left = newNode(3);
	root1->left->right = newNode(8);
	root1->right->left = newNode(15);
	root1->right->left->left = newNode(10);
	
	root1->right->right = newNode(25);


	swapNode(root1,&prev,&swapNode1,&swapNode2);
	printTreeInOrder(root1);
	printf("\n");
	
	swapValue(swapNode1,swapNode2);
	printTreeInOrder(root1);
	printf("\n");
	
	
	//printTreePreOrder(root2);
	//printf("\n");
	
}