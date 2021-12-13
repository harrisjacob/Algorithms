#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


int flashCount = 0;



void printBoard(int a[], int len){

	for(int i=0; i<len*len; i++){
		if(!(i%10) && i!=0){
			std::cout << std::endl;
		}
 
		std::cout << a[i];
	}

	std::cout << std::endl << std::endl;

}


void flash(int a[], int r, int c, int len){
	flashCount++;
	a[r*len+c] = 0;

	for(int i=-1; i<2; i++){
		for(int j=-1; j<2; j++){


			if(i==0 && j==0) continue;

			int newRow = r+i;
			int newCol = c+j;


			if(	newRow>=0  && newRow<len && newCol>=0 && newCol<len){

				int loc = newRow*len+newCol;

				if(!a[loc]) continue;

				a[loc]++;

				if(a[loc]>9) flash(a, newRow, newCol, len);
			}

		}
	}

}


int main(int argc, char** argv){

	std::string filename = argv[1];
	std::ifstream in;
	in.open(filename);
	if(!in.is_open()){
		std::cerr << "Can't open file\n";
		in.close();
		return 1;
	}

	std::string line, input;

	int length=10;

	int current[length*length];
	int row = 0;


	while(!in.eof()){
		
		std::getline(in, line);
		std::stringstream ss(line);
		ss >> input;
		for(int col=0; col<length; col++){
			current[row*length + col] = input[col]-'0';
		}
		row++;
	}

	int steps = 100;

	for(int step = 0; step<steps; step++){

		//Increment
		for(int row=0; row<length; row++){
			for(int col=0; col<length; col++){
				current[row*length+col]++;
			}
		}


		//Flash
		for(int row=0; row<length; row++){
			for(int col=0; col<length; col++){
				if(current[row*length+col] == 10){
					flash(current, row, col, length);
				}
			}
		}

	}


	std::cout << "Flash count: " << flashCount << std::endl;


	in.close();

	return 0;
}