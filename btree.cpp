#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iomanip>

using namespace std;

struct node {
	int val;
	node* left;
	node* right;
	node* parent;
	node(int v=0) : val(v), left(NULL), right(NULL), parent(NULL) { }
};

class btree {
private:
	node* root;
	void free_btree();
	void _free_btree(node* nd);
	void _in_order_visit(node* root);
	node* _search(node* root, int data);
	void _transplant(node* u, node* v);
	int _height(node* nd);
	void  _pretty_print(node* nd);
public:
	btree( ) : root(NULL) { }
	~btree( ) { free_btree(); }
	void insert(int data);
	void in_order();
	node* search(int data);
	int min();
	int max();
	node* successor(node* nd);
	void  delete_node(node* nd);
	void print_tree();
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
					nd->parent = p;
					break;
				} else
					p = p->left; 
			} else {
				if(p->right == NULL) {
					p->right = nd;
					nd->parent = p;
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


node* btree::successor(node* nd) {
	if(nd == NULL) return NULL;
	if(nd->right!=NULL) {
		node* r = nd->right;
		while(r->left!=NULL) 
			r = r->left;
		return r;		
	} else {
		node* p = nd->parent;
		while(p!=NULL && p->right == nd) {
			nd = p;
			p = p->parent;
		}
		return p;
	}

}


void btree::_transplant(node* u, node* v) {
	if(u == NULL) return;
	node* p = u->parent;
	if(p ==NULL)
		root = v;
	else if(p->left == u)
		p->left = v;
	else if(p->right = u)
		p->right =v;
	if(v!=NULL)
		v->parent = p;

}

int btree::_height(node* nd) {
	if(nd == NULL) 	
		return 0;
	else {
		int ht = 0;
		int ht_l = _height(nd->left);
		int ht_r = _height(nd->right);
		ht = ht_l;
		if(ht_r > ht_l)
			ht = ht_r;
		return (ht+1);
	}	

}

void btree::delete_node(node* nd) {
	if(nd == NULL) return;
	if(nd->left == NULL)
		_transplant(nd, nd->right);
	else if(nd->right == NULL)
		_transplant(nd, nd->left);
	else {
		node* y = successor(nd);
		if(y!=nd->right) {
			_transplant(y, y->right);
			y->right = nd->right;
			y->right->parent = y;
		}
		y->left = nd->left;
		y->left->parent  = y;
		_transplant(nd, y);	
	}
	delete nd;
}


void  btree::_pretty_print(node* nd){
	if(nd == NULL) return;
	int height = _height(nd);
	int num_node = (1<<height)-1;
	//cout<<"Number of Node is "<<num_node<<endl;
	int space = 1<<height;
	deque<node*> q_cur;
	deque<node*> q_nxt;
	q_cur.push_back(nd);
	int indent = space/2;
	while(height>0){
		while(!q_cur.empty()) {
			node *n =q_cur.front();
			for(int i=0; i<indent; ++i)
				cout<<" ";
			if(n!=NULL)
		   		cout<<n->val;	
			else
		 		cout<<" ";
			if(n!=NULL) 
				q_nxt.push_back(n->left);
			else
				q_nxt.push_back(NULL);
			if(n!=NULL)
				q_nxt.push_back(n->right);
			else
				q_nxt.push_back(NULL);
			q_cur.pop_front();	
		}
		indent = indent >> 1;
		--height;
		cout<<endl;
		q_cur = q_nxt;
		q_nxt.clear();
	} 				
}

void btree::print_tree() {
	cout<<"Current binary tree is"<<endl;
	_pretty_print(root);
}

void print_usage( ) {
	cout<<"|============================|"<<endl;
	cout<<"|  Please input your choice: |"<<endl;
	cout<<"| (1) insert node            |"<<endl;
	cout<<"| (2) delete node            |"<<endl;
	cout<<"| (3) exit                   |"<<endl;	
	cout<<"|============================|"<<endl<<endl;
}

int main() {
	btree bt;
	//bt.insert(5);
	//bt.insert(3);
	//bt.insert(7);
	//bt.insert(2);
	//bt.insert(4);
	//bt.insert(6);
	//bt.insert(8);
	//bt.in_order();
	//cout<<endl;
	//bt.print_tree();
	int choice;
	int val;
	node* nd;
	while(true) {
		print_usage();
		cin>>choice;
		switch(choice) {
			case 1 :  
				cin >> val;
				bt.insert(val);
				bt.print_tree();
				break;
			case 2 : 
				cin >> val;
				nd = bt.search(val);
				bt.delete_node(nd);
				bt.print_tree();
				break;					 
			case 3:
				return 1;
		}
	}
}



