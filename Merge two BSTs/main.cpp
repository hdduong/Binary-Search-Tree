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

// 0(m+n) complexity
// 0(logn + logm) spaces
void mergeBST(node *root1, node* root2) {
	
	if ((root1 == NULL) && (root2 == NULL)) return;

	if ((root1 == NULL) && (root2!=NULL))
	{
		//printTreeInOrder(root2);
		return;
	}
	
	if ((root1 != NULL) && (root2==NULL))
	{
		//printTreeInOrder(root1);
		return;
	}

	if (root1->data > root2->data) {
		mergeBST(root1->left, root2);
	}
	else if (root1->data < root2->data) {
		mergeBST(root1, root2->left);
	}

	if (root1->data < root2->data) {
		printf("%d ", root1->data);
		mergeBST(root1->right, root2);
	}
	else if (root2->data < root1->data) {
		printf("%d ", root2->data);
		mergeBST(root1, root2->right);
	}




	
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

void main() {
	//node* root1 = newNode(3);
	//root1->left = newNode(1);
	//root1->right = newNode(5);
	//
	//node* root2 = newNode(4);
	//root2->left = newNode(2);
	//root2->right = newNode(6);
	
	node* root1 = newNode(8);
	root1->left = newNode(2);
	root1->right = newNode(10);
	root1->left->left = newNode(1);
	
	node* root2 = newNode(5);
	root2->left = newNode(3);
	root2->left->left = newNode(0);

	mergeBST(root1, root2);
	printf("\n");

	
	//printTreePreOrder(root2);
	//printf("\n");
	
}