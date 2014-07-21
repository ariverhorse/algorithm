#include <iostream>
#include <vector>

using namespace std;

struct node {
	int val;
	node* left;
	node* right;
	node(int v=0) : val(v), left(NULL), right(NULL) { }
};

class btree {
private:
	node* root;
	void free_btree();
	void _free_btree(node* nd);
	void _in_order_visit(node* root);
	node* _search(node* root, int data);
public:
	btree( ) : root(NULL) { }
	~btree( ) { free_btree(); }
	void insert(int data);
	void in_order();
	node* search(int data);
	int min();
	int max();
};

node* btree::_search(node* root, int data) {
	if(root == NULL)
		return NULL;
	else if(root->val == data)
		return root;
	else if(data < root->val)
		return _search(root->left, data);
	else 
		return _search(root->right, data);
}

node* btree::search(int data) {
	return _search(root, data);
}

void btree::_free_btree(node* nd) {
	if(nd==NULL) return;
	node* left  = nd->left;
	node* right = nd->right;
	delete nd;
	_free_btree(left);
	_free_btree(right);
}

void btree::free_btree() {
	_free_btree(root);
}

void btree::insert(int data) {
	node* nd = new node(data);
	node* p = root;
	if(p==NULL) 
		root = nd;
	else {
		while(p!=NULL) {
			if(data<=p->val) {
				if(p->left == NULL) {
					p->left = nd;
					break;
				} else
					p = p->left; 
			} else {
				if(p->right == NULL) {
					p->right = nd;
					break;
				} else
					p = p->right;
			}	

		}
	}	
}

void btree::_in_order_visit(node* root) {
	if(root == NULL) 
		return;
	else {
		_in_order_visit(root->left);
		cout<<root->val<<" "<<endl;
		_in_order_visit(root->right);
	}

}


void btree::in_order() {
	_in_order_visit(root);
}

int btree::min() {
	node* p = root;
	if(p ==NULL) return -1;
	while(p->left!=NULL)
		p = p->left;
	return p->val;	
}

int btree::max() {
	node* p = root;
	if(p==NULL) return -1;
	while(p->right!=NULL)
		p = p->right;
	return p->val;
}

int main() {
	btree bt;
	bt.insert(7);
	bt.insert(6);
	bt.insert(8);
	bt.insert(3);
	bt.insert(9);
	bt.insert(0);
	bt.insert(5);
	bt.in_order();
	cout<<bt.min()<<" "<<bt.max()<<endl;
}



