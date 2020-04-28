#include <stdlib.h>
#include <stdio.h>

 struct TreeNode {
	 int val;
	 struct TreeNode *left;
	 struct TreeNode *right;
 };

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize){
	if (preorderSize <= 0) return NULL;
	struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	root->val = preorder[0];
	int index = 0;
	while (index < inorderSize && inorder[index] != preorder[0]) ++index;
	root->left = buildTree (preorder + 1, index, inorder, index);
	root->right = buildTree (preorder + 1 + index, preorderSize - index - 1, inorder + index + 1, preorderSize - index - 1);
	return root;
}

void MorrisInOrder (struct TreeNode *root) {
	struct TreeNode *cur = root;
	while (cur) {
		if (cur->left) {
			struct TreeNode *temp = cur->left;
			while (temp->right && temp->right != cur) {
				temp = temp->right;
			}
			if (temp->right) {
				temp->right = NULL;
				printf("%5d", cur->val);
				cur = cur->right;
			} else {
				temp->right = cur;
				cur = cur->left;
			}
		} else {
			printf("%5d", cur->val);
			cur = cur->right;
		}
	}
}

void MorrisPreOrder (struct TreeNode *root) {
	struct TreeNode *cur = root;
	while (cur) {
		if (cur->left) {
			struct TreeNode *temp = cur->left;
			while (temp->right && temp->right != cur) {
				temp = temp->right;
			}
			if (temp->right) {
				temp->right = NULL;
				cur = cur->right;
			} else {
				printf("%5d", cur->val);
				temp->right = cur;
				cur = cur->left;
			}
		} else {
			printf("%5d", cur->val);
			cur = cur->right;
		}
	}
}

void reversePrint (struct TreeNode *root) {
	if (root->right == NULL) {
		printf("%5d", root->val);
		return;
	}
	struct TreeNode *p = NULL, *q = root, *r = root->right;
	q->right = p;
	while (r) {
		p = q;
		q = r;
		r = r->right;
		q->right = p;
	}
	p = NULL;
	r = q->right;
	q->right = p;
	printf("%5d", q->val);
	while (r) {
		p = q;
		q = r;
		r = r->right;
		q->right = p;
		printf("%5d", q->val);
	}
}

void MorrisPostOrder (struct TreeNode *root) {
	struct TreeNode *dummy = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	dummy->left = root;
	dummy->right = NULL;
	struct TreeNode *cur = dummy;
	while (cur) {
		if (cur->left) {
			struct TreeNode *temp = cur->left;
			while (temp->right && temp->right != cur) {
				temp = temp->right;
			}
			if (temp->right) {
				temp->right = NULL;
				reversePrint (cur->left);
				cur = cur->right;
			} else {
				temp->right = cur;
				cur = cur->left;
			}
		} else {
			cur = cur->right;
		}
	}
	free(dummy);
}

int main(int argc, char const *argv[])
{
	int preorder[] = {6, 2, 1, 4, 3, 5, 7, 9, 8}, preorderSize = 9;
	int inorder[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}, inorderSize = 9;
	int postorder[] = {1, 3, 5, 4, 2, 8, 9, 7, 6}, postorderSize = 9;
	struct TreeNode *root = buildTree (preorder, preorderSize, inorder, inorderSize);
	void (*printTree) (struct TreeNode *) = MorrisPostOrder;
	(*printTree) (root);
	printf("\n");

	return 0;
}