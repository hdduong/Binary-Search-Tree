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

int treeSize(node *root) {
	if (root == NULL) return 0;
	return (1 + treeSize(root->left) + treeSize(root->right));
}

void inOrderArray(node *root, int *arr, int *k) {
	if (root == NULL) return;
	inOrderArray(root->left, arr,k);
	
	arr[*k] = root->data;
	(*k)++;

	inOrderArray(root->right, arr,k);
}
// Complexity 0(n) since each element process 1;
int largestConSeq(int arr[], int size) {
	int i = 0;
	int j = 0;
	int maxValue = 0;

	j = i + 1;
	while( (j < size) && (i < size)) {
		if (arr[j-1] < arr[j]) {
			j++;
		}
		else {
			int tmpValue = j - i;
			if (tmpValue > maxValue) {
				maxValue= tmpValue;
			}
			i = j;
			j = i + 1;
		}
	}

	return (maxValue > (j - i) )? maxValue : (j-i);
}


int largestBST(node *root) {
	int n = treeSize(root);
	int* arr = (int*)malloc(n * sizeof(int));
	int k = 0;
	
	inOrderArray(root,arr,&k);

	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}

	printf("\n");
	return largestConSeq(arr,n);

}


void main() {
	node* root = newNode(50);
	root->left = newNode(30);
	root->right = newNode(60);
	root->left->left = newNode(5);
	root->left->right = newNode(20);
	root->right = newNode(60);
	root->right->left = newNode(45);
	root->right->right = newNode(70);
	root->right->right->left = newNode(65);
	root->right->right->right = newNode(80);
	printTreePreOrder(root);
	printf("\n");

	node* tmp = NULL;
	int currentK = 0;
	
	//int size = treeSize(root);
	//printf("%d \n", size);

	//int arr[] = {5, 30, 20, 50, 45,60, 65, 70, 80};
	//int size = 9;
	//int maxValue = largestConSeq(arr,9);

	int maxValue = largestBST(root);

	printf("%d \n", maxValue);
}