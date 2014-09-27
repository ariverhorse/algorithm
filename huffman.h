#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <string>

class huffman_code {
public:
	huffman_code(std::map<char, float>& freq);
	~huffman_code() { };
private:
	struct {
		char  c;
		float freq;
		struct node* left;
		struct node* right;
	}node;
	node* root;
	void init(std::map<char, float>& freq);
	std::map<char, std::string>  code;
};

huffman_code::huffman_code(std::map<char, float>& freq) {
	root = NULL;
	init(freq);
}


huffman_code::init(std::map<char, float>& freq) {


}

