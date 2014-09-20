#include <stdio.h>
#include <stdlib.h>
#include <stack> //using bult in stack C++

using namespace std;

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


bool pairGivenSum(node* root, int sum) {
	if (root == NULL) return false;

	stack<node*> inOrder;
	stack<node*> reverseOrder;

	node* travel1 = root;
	node* travel2 = root;

	while(travel1 != NULL) {
		inOrder.push(travel1);
		travel1 = travel1->left;
	}

	while(travel2 != NULL) {
		reverseOrder.push(travel2);
		travel2 = travel2->right;
	}

	while( (!inOrder.empty()) && (!reverseOrder.empty()) && (inOrder.top() != reverseOrder.top()) ) {
		int inOrderValue = inOrder.top()->data;
		int reverseOrderValue = reverseOrder.top()->data;

		if (inOrderValue + reverseOrderValue == sum) {
			return true;
		}

		else if (inOrderValue + reverseOrderValue > sum) { //advanced reverse order
			node* tmp = reverseOrder.top();
			reverseOrder.pop();

			if(tmp->left != NULL) {
				reverseOrder.push(tmp->left);
				tmp = tmp->left;
			}

		}
		else if (inOrderValue + reverseOrderValue < sum) { //advanced order
			node* tmp = inOrder.top();
			inOrder.pop();

			if(tmp->right != NULL) {
				inOrder.push(tmp->right);
				tmp = tmp->right;
			}

		}
	}


	return false;

}

void main() {
	
	node* root1 = newNode(15);
	root1->left = newNode(10);
	root1->right = newNode(20);
	root1->left->left = newNode(8);
	root1->left->right = newNode(12);
	root1->right->left = newNode(16);
	root1->right->right = newNode(25);

	printTreeInOrder(root1);
	printf("\n");

	int sum = 33;
	bool hasPair = pairGivenSum(root1, sum);
	printf("%s\n",(hasPair)?"true":"false");
	

	
	
}