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

void printTree(node *root) {
	if (root == NULL)
		return;
	printf("%d ",root->data);
	printTree(root->left);
	printTree(root->right);
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

node* searchNode(node* root, int data) {
	if (root->data == data)
		return root;

	if (root->data < data)
		return searchNode(root->right, data);

	if (root->data > data)
		return searchNode(root->left,data);

	return NULL; //nothing found
}

node* findParentNode(node* root, node* findNode) {
	if (root->data == findNode->data)
		return NULL;

	if ( (root->left != NULL) && (root->left == findNode))
		return root;
	
	if ( (root->right != NULL) && (root->right == findNode))
		return root;
	
	if (root->data < findNode->data)
		return findParentNode(root->right, findNode);

	if (root->data > findNode->data)
		return findParentNode(root->left,findNode);

	return NULL; //nothing found

}

node* indorderSuccessor(node* root) {
	// with assume that root has 2 kids
	// most left of right kid

	node* leftNode = root->right;
	node* parentLeftNode = root;

	while(leftNode->left != NULL) {
		parentLeftNode = leftNode;
		leftNode= leftNode->left;
	}

	if (leftNode == root->right) { //only 1 kid
		leftNode->left = root->left;
		root->left = NULL;
		root->right = NULL;
		free(root);
		root = leftNode;
	}
	else if (leftNode != root->right) {
		parentLeftNode->left = NULL;		
		leftNode->left = root->left;
		leftNode->right = root->right;
		root->left = NULL;
		root->right= NULL;
		free(root);
		root = leftNode;
	}
	return root;
}

void deleteNode(node** root, int data) {
	node* nodeDelete = NULL;
	nodeDelete = searchNode(*root, data);
	
	node* parentDeletNode = NULL;
	parentDeletNode = findParentNode(*root,nodeDelete);

	if ( (nodeDelete->left == NULL) && (nodeDelete->right == NULL) ) {
		if (parentDeletNode->left == nodeDelete)
			parentDeletNode->left = NULL;
		if (parentDeletNode->right == nodeDelete)
			parentDeletNode->right = NULL;

		free(nodeDelete);
		nodeDelete = NULL;

		return;
	}

	if ((nodeDelete->left != NULL) && (nodeDelete->right == NULL)) {
		nodeDelete->data = nodeDelete->left->data;
		free(nodeDelete->left);
		nodeDelete->left = NULL;
		return;
	}
	
	if ((nodeDelete->left != NULL) && (nodeDelete->right != NULL)) {
		bool isLeftChild = false;
		bool isRightChild = false;

		if (parentDeletNode != NULL) {
			if(parentDeletNode->left == nodeDelete)
				isLeftChild = true;
			else if(parentDeletNode->right == nodeDelete)
				isRightChild = true;

		}

		nodeDelete = indorderSuccessor(nodeDelete);
		if (parentDeletNode != NULL) {
			if(isLeftChild)
				parentDeletNode->left = nodeDelete;
			else if (isRightChild)
				parentDeletNode->right = nodeDelete;
		}
		else {
			//root
			*root = nodeDelete;
		}
		return;
	}

}


void main() {
	node* root = NULL;
	root = insertNode(root,50);
	root = insertNode(root, 30);
	root = insertNode(root, 70);
	root = insertNode(root, 20);
	root = insertNode(root, 40);
	root= insertNode(root, 60);
	root = insertNode(root, 80);
	printTree(root);
	printf("\n");

	node* nodeSearch = NULL;
	nodeSearch = searchNode(root,20);
	if (nodeSearch!= NULL) {
		printf("%d \n", nodeSearch->data);
	} else if (nodeSearch == NULL){
		printf("Not found\n");
	}
	
	node *parentNode = NULL;
	parentNode = findParentNode(root,nodeSearch);
	if (parentNode!= NULL) {
		printf("%d \n", parentNode->data);
	} else if (parentNode == NULL){
		printf("Not found\n");
	}
	
	
	deleteNode(&root, 20);
	printTree(root);
	printf("\n");
	

	/*
	deleteNode(&root, 30);
	printTree(root);
	printf("\n");
	*/

	/*
	deleteNode(&root, 50);
	printTree(root);
	printf("\n");
	*/
}