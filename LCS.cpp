#include <iostream>
#include <string>
#include <vector>

using namespace std;


class lcs {
private:
	string _x;
	string _y;

	//| - \ --
	enum DIR {UP, LEFT, DIA, NA};		
	vector<vector<DIR> > dir;
	vector<vector<int> > len;	
	
	void _init();

public:
	lcs(string x, string y) : _x(x), _y(y) { _init(); }
	~lcs() { }
	string get_lcs();
};


void lcs::_init() {
	int x_len = _x.length();
	int y_len = _y.length();
	for(int i =0; i<x_len; ++i)  {
		vector<int> len_entry;
		for(int j=0; j<y_len; ++j) 
			len_entry.push_back(0);
		len.push_back(len_entry);
	}

	for(int i =0; i<x_len; ++i)  {
		vector<lcs::DIR> dir_entry;
		for(int j=0; j<y_len; ++j) 
			dir_entry.push_back(NA);
		dir.push_back(dir_entry);
	}
}

string lcs::get_lcs() {

	int x_len = _x.length();
	int y_len = _y.length();

	for(int i=0; i<x_len; ++i)  {
		for(int j=0; j<y_len; ++j) {
			if(i==0 && j==0) {
				len[i][j] = (_x[i]==_y[j])? 1   : 0;
				dir[i][j] = (_x[i]==_y[j])? DIA : NA; 
			} else if(i==0) {
				len[i][j] = (_x[i]==_y[j])? 1: len[i][j-1];
				dir[i][j] = (_x[i]==_y[j])? DIA : LEFT; 
			} else if(j==0) {
				len[i][j] = (_x[i]==_y[j])? 1: len[i-1][j];
				dir[i][j] = (_x[i]==_y[j])? DIA : UP; 

			} else { 	
				if(_x[i] == _y[j]) {
					len[i][j] = len[i-1][j-1]+1;
					dir[i][j] = DIA;
				} else if(len[i-1][j] > len[i][j-1]) {
					len[i][j] = len[i-1][j];
					dir[i][j] = UP;
				} else {
					len[i][j] = len[i][j-1];
					dir[i][j] = LEFT;
				}	 	
			}
		}
	}

	cout<<"Matched LENGTH = "<<len[x_len-1][y_len-1]<<endl;

	for(int i=0; i<x_len; ++i) { 
		for(int j=0; j<y_len; ++j) {
			if(dir[i][j]==UP)
				cout<<"| ";
			else if(dir[i][j]==LEFT)
				cout<<"- ";
			else if(dir[i][j]==DIA)
				cout<<"\\ ";
			else if(dir[i][j]==NA)
				cout<<"* ";
			else 
				cout<<"? ";	

		}
		cout<<endl;
	}
	int x = x_len-1;
	int y = y_len-1;
	string str;
	while(true) {
		if(dir[x][y] == DIA) {
			str.insert(0,1,_x[x]);
			if(x==0 || y==0) break;
			--x;
			--y;
		} else if(dir[x][y]==LEFT) {
			if(y>0)	
			     --y;
			else
			     break; 
		} else if(dir[x][y]==UP) {
			if(x>0) 
				--x;
			else
				break;
		} else 
			break;
	} 
	return str;	
}

int main() {
	string str1 ;
	string str2 ;
	while(true) {
		cout<<"Input string 1: "<<endl;
		cin >> str1;
		cout<<"Input string 2: "<<endl;
		cin >> str2;
		lcs l(str1, str2);
		cout<<"Longest Common sequence is:"<<endl;
		cout<<l.get_lcs()<<endl;
	}
}
