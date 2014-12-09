#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <fstream>

using namespace std;

struct node {
	char  _c;
	float _f;
	node* _l;
	node* _r;
	node(char c, float f, node* l, node* r) : _c(c), _f(f), _l(l), _r(r) { }
	bool is_leaf() { return _l==NULL && _r ==NULL;  }
};

class compare_node {
public:
	bool operator()(node* n1, node* n2) {
		return n1->_f > n2->_f;
	}
};




class huffman {
public:
	huffman(std::map<char, float>& freq);
	~huffman() { };
	string compress(string& str);
	string decompress(string& str);
	string get_encode(char c) {
		if(dic.find(c) == dic.end()) {
			cout<<"Error! cannot find encoding for "<<c<<endl;
			exit(1);
		}
		//cout<<c<<" "<<dic[c]<<endl;
		return dic[c];	
	}
public:
	static const int R = 256;
private:
	void build_tree();
	void populate_dic();
	void _populate_dic(node* nd, string prefix);
	float freq[R];
	bool  valid[R];
	node* root;	
	map<char, string> dic;
};

huffman::huffman(std::map<char, float>& f) {
	for(int i=0; i<R; ++i)
		valid[i] = false;
	map<char,float>::iterator iter = f.begin();
	while(iter!=f.end()) {	
		freq[iter->first] = iter->second;
		valid[iter->first] = true;
		++iter;
	}
	build_tree();	
}

void huffman::build_tree() {
	vector<node*> minq;
	for(int i=0; i<R; ++i) {
		if(valid[i]) {
			node* nd = new node(i, freq[i], NULL, NULL);
			minq.push_back(nd);
		}	
	}	
	make_heap(minq.begin(), minq.end(), compare_node());
	while(minq.size()>=2) {
		pop_heap(minq.begin(), minq.end(), compare_node());
		node* l = minq.back();
		minq.pop_back();
		pop_heap(minq.begin(), minq.end(), compare_node());
		node* r = minq.back();
		minq.pop_back();
		node* new_node = new node(0, l->_f+r->_f, l, r);
		minq.push_back(new_node);
		push_heap(minq.begin(), minq.end(), compare_node());	
	}
	root = minq[0];
	
	populate_dic();	

	//map<char, string>::iterator iter = dic.begin();
	//while(iter!=dic.end()) {	
	//	cout<<(char)(iter->first)<<"->"<<iter->second<<endl;
	//	++iter;
	//}
}

void huffman::_populate_dic(node* nd, string prefix) {
	if(nd->is_leaf()) {
		dic.insert(make_pair<char, string>(nd->_c, prefix));		
		return;
	} else {
		string lprefix = prefix + "0";
		_populate_dic(nd->_l, lprefix);
		string rprefix = prefix + "1";
		_populate_dic(nd->_r, rprefix);	
	}
}
 
void huffman::populate_dic() {
	string prefix ="";
	_populate_dic(root, prefix);	
}

string huffman::compress(string& str) {
	string rc = "";
	for(int i=0;i<str.size(); ++i) {
		rc+=get_encode(str[i]);	
	}
	return rc;	
}

string huffman::decompress(string& str) {
	int i = 0;
	string result = "";
	node* nd = root;
	while(i<str.size()) {
	    if(nd->is_leaf()) {
		result +=nd->_c;
		nd = root;	
		--i;
	    } else {
		if(str[i] == '1') 
			nd = nd->_r;
		else 
			nd = nd->_l;
	    }
	    ++i;	
	}
	return result;
}

int main(int argc, char** argv) {
	ifstream in(argv[1]);
	if(!in.good()) {
		cout<<"Error! cannot open file "<<argv[1]<<endl;
		exit(1);
	}
	int char_array[256];
	map<char, float> freq;
	for(int i=0; i<256; ++i) 
		char_array[i] = 0;
	char c;
	int total = 0;
	while(in.get(c)) {
		char_array[c]++;	
		total++;
	}	

	for(int i=0; i<256; ++i) {	
		if(char_array[i]>0) {
			//cout<<i<<" "<<(float)char_array[i]/(float)total<<endl;
			freq.insert(make_pair<char, float>(i, (float)char_array[i]/(float)total));
		}
	}
	in.close();

	huffman hf(freq);
	ifstream in1(argv[1]);
	if(!in1.good()) {
		cout<<"Error! cannot open file "<<argv[1]<<endl;
		exit(1);
	}

	string strs ="";
	int numofbits = 0;
	while(in1.get(c)) {
		string encode = hf.get_encode(c);	
		strs+=encode;	
		numofbits += encode.size();
	}

	in1.close();	


	cout<<"Total number of bits is "<<numofbits<<endl;
	cout<<"sizeof(int) = "<<sizeof(int)<<endl;
	
	ofstream out1(argv[2]);
	out1.write((char*)&numofbits, sizeof(int));
	char buf = 0;
	int i = 0;
	int j = 0;
	while(i<numofbits) {
		if(j == 8)
			j = 0;
		if(strs[i] == '1')	
			buf = buf<<1 + 1;
		else
			buf = buf<<1;
	
		++i; 
		++j;
		if(j==8) {
			out1.write(&buf, sizeof(char));
		} 
	}			

	//pading	
	if(j<8) {
		int num = 8 - j;	
		buf = buf<<num;
		out1.write(&buf, sizeof(char));
	}
	out1.close();			

	cout<<"Before compress..."<<endl;
	cout<<strs<<endl;
	cout<<"after decompress..."<<endl;
	cout<<hf.decompress(strs)<<endl;	
}
