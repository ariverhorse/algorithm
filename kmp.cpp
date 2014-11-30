#include <iostream>
#include <string>
#include <vector>

using namespace std;

class kmp {
private:
	static kmp* instance;
	kmp() { };
public:
	static void match(string& line, string& pattern);
	static kmp* get_instance() {
		instance = new kmp;
		return instance;	
	}
};

kmp* kmp::instance = NULL;


void kmp::match(string& line, string& pattern) {
	int pattern_size = pattern.size();
	int line_size    = line.size();
	
	//Init PI
	vector<int>  PI(pattern_size, 0);

	//Compute PI
	int k = 0;
	for(int q=1; q<pattern_size; ++q) {
		while(pattern[q] != pattern[k]) 	
			k = PI[k];
		if(pattern[q] == pattern[k])
			k = k+1;
		PI[q] = k;
		//cout<<PI[q]<<endl;
	}

	int q = 0;
	for(int i=0; i<line_size; ++i) {
		while(q>0 && pattern[q]!=line[i])
			q = PI[q]-1;
		if(pattern[q] == line[i])
			q = q+1;

		if(q == pattern_size) {
			cout<<"Match at "<<i-pattern_size+1<<endl;
			q = 0;
			//break;	
		}
	}	
		
}

int main() {
	kmp* instance = kmp::get_instance();
	string line("xxabacaxxxxabacayyyyabaca");
	string pattern("abaca");
	cout<<"Line is:  "<<line<<endl;
	cout<<"Pattern is: "<<pattern<<endl;
	instance->match(line, pattern);

}

