//Consider a row of n coins of value v1...vn, where n is even.  we play
//a game against an opponent by alternating turns. In each turn, a player selects either 
//the first or last coin from the row. removes it from the row permanently, and receives
//the value of the coin. Determin the maximun possible amount of money that we can definitely win if 
//we move first.

// V(i, j) = max( vi + min(V(i+2, j), V(i+1, j-1)),
//                vj + min(V(i+1, j-1), V(i, j-2)))
// v(i,i) = 0;
// v(i, i+1) =  max(v(i), v(i+1))
#include <iostream>
#include <vector>

#define max(x, y) ((x)<(y) ? (y) : (x) )
#define min(x, y) ((x)<(y) ? (x) : (y) )

using namespace std;


int coin_value(const vector<int>& coins) {
	int size = coins.size();
	if(size%2!=0) {
		cout<<"Error!  The number of coins must be even!"<<endl;
		return 0;
	}

	vector<vector<int> > value;	
	for(int i=0; i<size; i++) {
		vector<int> v(size, 0);
		value.push_back(v);
	}
	
	for(int k=0; k<size; ++k) {
		for(int i=0; i<size-k; ++i) {	
			int j =  i+k;
			if(j == i) 
				value[i][j] =  0;
			else if(j == i+1)
				value[i][j] =  max((coins[i]), (coins[j]));
			else {
				int x = min((value[i+2][j]), (value[i+1][j-1]));
				int y = min((value[i+1][j-1]), (value[i][j-2]));
				int xx = coins[i] + x;
				int yy = coins[j] + y;
				value[i][j] = max((xx), (yy));	
			}		
		}
	}

	return value[0][size-1];
}


int main() {
    vector<int> coins;
    int v;
    while(cin>>v) {
	coins.push_back(v);
    }
    cout<<"max value is: "<< coin_value(coins)<<endl;

}

