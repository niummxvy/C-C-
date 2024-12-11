#include <stdio.h>
#include <stdlib.h>

struct node{
	double data;
	struct node *left;
	struct node *right;
};
typedef struct node Node;

void insert(Node *node, double num){
	if(num > node->data){
		if(node->right == NULL){
			node->right = (Node*)malloc(sizeof(Node));
			node = node->right;
			node->left = NULL;
			node->right = NULL;
			node->data = num; 
		}
		else insert(node->right, num);
	}
	else if(num <= node->data){
		if(node->left == NULL){
			node->left = (Node*)malloc(sizeof(Node));
			node = node->left;
			node->left = NULL;
			node->right = NULL;
			node->data = num; 
		}
		else insert(node->left, num);
	}
}

void post(Node *node){
	if(node == NULL) return;
	post(node->left);
	post(node->right);
	printf("%.0lf ", node->data);
}

int main(){
	double num;
	Node *root = (Node*)malloc(sizeof(Node));
	root->left = NULL;
	root->right = NULL;
	scanf("%lf", &num);
	root->data = num;
	while(scanf("%lf", &num) != EOF){
		insert(root, num);
	}
	post(root);
	return 0;
} 
