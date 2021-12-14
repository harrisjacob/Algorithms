#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>
#include <vector>

struct Point{
	int x;
	int y;
};

struct Limits{
	int xMin;
	int xMax;
	int yMin;
	int yMax;
};

void printPlane(std::vector<std::vector<int>>& plane, Limits& l){
	for(int row=l.yMin; row<l.yMax+1; row++){
		for(int col=l.xMin; col<l.xMax+1; col++){
			


			std::cout<<((plane[row][col])?'X':' ');
		}
		std::cout << std::endl;
	}

}

void inputPoints(std::vector<std::vector<int>>& plane, std::vector<Point>& points){
	for(auto& p: points){
		plane[p.y][p.x] = 1;
	}
}


void foldPaper(std::vector<std::vector<int>>& plane, Limits& lim, bool dir, int val){

	if(dir){ //y fold
		for(int y=1; y<lim.yMax-val+1; y++){
			for(int col=lim.xMin; col<lim.xMax+1; col++){
				if(plane[val+y][col]) 
					plane[val-y][col] = 1;
			}
		}

		lim.yMax = val - 1;


	}else{ // x fold
		for(int row=lim.yMin; row<lim.yMax+1; row++){
			for(int x=1; x<lim.xMax-val+1; x++){
				if(plane[row][val+x])
					plane[row][val-x] = 1;
			}
		}

		lim.xMax = val - 1;
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
	std::string readX, readY;

	Limits lim;
	lim.xMin = INT_MAX;
	lim.xMax = INT_MIN;
	lim.yMin = INT_MAX;
	lim.yMax = INT_MIN;

	std::vector<Point> points;

	while(std::getline(in, line)){

		//Remove carraige return character from files that contain it
		std::stringstream ss(line);
		std::getline(ss, input,'\r');
		if(input.empty()) break;
		std::stringstream sp(input);

		std::getline(sp, readX, ',');
		std::getline(sp, readY, ',');


		int x = stoi(readX);
		int y = stoi(readY);


		Point p;
		p.x = x;
		p.y = y;

		points.push_back(p);

		lim.xMin = std::min(lim.xMin, x);
		lim.xMax = std::max(lim.xMax, x);
		lim.yMin = std::min(lim.yMin, y);
		lim.yMax = std::max(lim.yMax, y);
	}


	//Generate paper
	std::vector<std::vector<int>> plane;
	for(int i=0; i<lim.yMax+1; i++){
		std::vector<int> v(lim.xMax+1, 0);
		plane.push_back(v);
	}

	//Read in points
	inputPoints(plane, points);
	std::string fold, along, data;

	//Read in fold instructions
	while(getline(in, line)){

		std::stringstream ss(line);
		std::getline(ss, input,'\r');
		if(input.empty()) break;
		std::stringstream sp(input);

		sp >> fold >> along >> data;
		bool direction = (data[0] == 'y');

		std::string value = data.substr(data.find('=')+1, std::string::npos);
		foldPaper(plane, lim, direction, stoi(value));

	}

	printPlane(plane, lim);

	in.close();

	return 0;
}