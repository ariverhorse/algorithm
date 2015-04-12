#include <iostream>

using namespace std;

enum color_t {RED, BLACK};

struct tnode {
	int     val;
	color_t color;
	tnode* left;
	tnode* right;
	tnode* parent;
	tnode(int v, color_t c) : val(v), color(c), left(NULL), right(NULL), parent(NULL)  { }
	void show() { cout<<"NODE: val="<<val<<" color="<<color<<endl; }
};

static tnode* nil = new tnode(0, BLACK); 

//(1) each node is either red or black
//(2) root is black
//(3) leaf NIL is black
//(4) if a node is red, both of children are black
//(5) black node for every path is the same
class rbtree {
public:
	rbtree():root(nil)  { } 	
	void insert(int val);
	void visit(); 
private:
	void _visit(tnode* root);
	void _rb_insert_fixup(tnode* z);
private:
	tnode* root;	
};

void rbtree::_rb_insert_fixup(tnode* z) {



}


void rbtree::insert(int val) {
	tnode* z = new tnode(val, RED);
	tnode* x = root;
	tnode* y = nil;
	while(x!=nil) {
		y = x;
		if(z->val < x->val)
			x = x->left;
		else 
			x = x->right;
	}	
	z->parent = y;
	if(y == nil)
		root = z;
	else if(z->val < y->val)
		y->left = z;
	else
		y->right= z;
	z->left  = nil;
	z->right = nil;
	_rb_insert_fixup(z);
}

void rbtree::_visit(tnode* root) {
	if(root==nil)
		return;
	else {
		_visit(root->left);
		root->show();
		_visit(root->right);
	}	
}

void rbtree::visit() {
	_visit(root);	
}

int main() {
	rbtree rbt;
	for(int i=0; i<100; ++i)
		rbt.insert(i);
	rbt.visit();		
}
