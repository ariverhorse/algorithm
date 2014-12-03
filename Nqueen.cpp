#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

//check whether it is safe to place queen on (x,y) on m 
bool is_safe(int x, int y, bool** m, int size) {
	for(int j=0; j<size; ++j)
		if( j!=y && m[x][j])
			return false;

	for(int i=0; i<size; ++i)
		if( i!=x && m[i][y])
			return false; 
	for(int i=1; i<size; ++i) {
		if( x-i >=0 && y-i>=0 && m[x-i][y-i])
			return false; 
		if( x+i < size && y+i <size && m[x+i][y+i])
			return false;
		if( x+i <size && y-i>=0 && m[x+i][y-i])
			return false; 
		if( x-i >=0 && y+i <size && m[x-i][y+i])
			return false;
	}	

	return true;
}

void print_array(bool** m, int size) {
	for(int i=0; i<size; ++i) {
		for(int j=0; j<size; ++j)
			cout<<(int)m[i][j]<<" ";
		cout<<endl;
	}

	cout<<endl;
}

void _print_N_queue(int col, int size, bool** m, int* num) {
	if(col == size) {
		print_array(m, size);	
		(*num)++;
	}
	for(int i=0; i<size; ++i) {
		if(is_safe(i, col, m, size)){
			m[i][col] = true;
			_print_N_queue(col+1, size, m, num);
			m[i][col] = false;
		} 
	}
}

void print_N_queue(int size) {
	 bool** m = new bool*[size];
	 for(int i=0; i<size; ++i)
		m[i] = new bool[size]; 
	
	 for(int i=0; i<size; ++i)
		for(int j=0; j<size; ++j)
			m[i][j] = false;

	 int solution = 0;
	 _print_N_queue(0, size, m, &solution);
	 cout<<"Total solution number is "<<solution<<endl;
}


int main(int argc, char** argv) {
	print_N_queue(atoi(argv[1]));
}
