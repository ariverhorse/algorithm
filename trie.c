#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _trie_node {
	char ch;
	int  val;
	struct _trie_node* left;
	struct _trie_node* mid;		
	struct _trie_node* right;
}trie_node;


trie_node* root = NULL;


trie_node* search_node(trie_node* nd, const char* str, int idx, int len) {
	if(nd==NULL) return NULL;
	char c = str[idx];
	if(c < nd->ch)  return search_node(nd->left, str, idx, len);
	else if(c> nd->ch) return search_node(nd->right, str, idx, len);
	else if(idx < len-1)
			return search_node(nd->mid, str, idx+1, len);
	else  
		return  nd;
}

trie_node* search_trie(const char* str) {
	int len = strlen(str);
	return search_node(root, str, 0, len);
}

void insert_node(trie_node** nd, const char* str, int idx, int len) {
	char c = str[idx];
	if(*nd == NULL) {
		trie_node *t = (trie_node*) malloc(sizeof(trie_node));
		t->ch = c;
		t->val = (idx == len-1)? 1 : 0;
		t->left = NULL;
		t->mid  = NULL;
		t->right = NULL;	
		*nd = t;
		//printf("Insert node (%d):  %c  %d \n", idx, c, t->val);
	}
	if( c < (*nd)->ch) 
		insert_node(&((*nd)->left), str, idx, len);
	else if( c > (*nd)->ch) 
		insert_node(&((*nd)->right), str, idx, len);
	else if (c == (*nd)->ch){
		if(idx < len-1) 
			insert_node(&((*nd)->mid), str, idx+1, len);
		else
			(*nd)->val = 1;
	}	
}

void insert_trie(const char* str) {
	int len = strlen(str);
	insert_node(&root, str, 0, len);
}


void print_all_prefix(trie_node* nd, char* str) {
	if(nd==NULL) {
		return;
	} 
	char newstr[100];
	int len = strlen(str);
	strcpy(newstr, str);
	newstr[len] = nd->ch;
	newstr[len+1]='\0';
	if(nd->val ==1) {
		printf("%s\n", newstr);	
	}
	print_all_prefix(nd->left, str);
	print_all_prefix(nd->mid, newstr);
	print_all_prefix(nd->right, str);
}

int main() {
	char str0[] = "she";
	char str1[] = "shells";
	char str2[] = "sea";
	char str3[] = "shy";
	char* strs[]= {"she", "shells", "sea", "shy", "sears", "pyt", "peng", "pyq", "pengh", "should", "show" };
	int size=sizeof(strs)/sizeof(char*);
	int i =0;
	for(i=0; i<size; i++) {
		insert_trie(strs[i]);
		printf("insert %s\n", strs[i]);
	}	

	printf("\n");
	
	while(1) {
		char pre[100];
		printf("Please input the prefix: ");
		scanf("%s", pre);
		trie_node* f = search_trie(pre);
		if(f==NULL) {
			printf("Do not have this prefix\n");
			continue;
		}	
		if(f->val == 1)
			printf("%s\n", pre);
		print_all_prefix(f->mid,pre);
	}
}
