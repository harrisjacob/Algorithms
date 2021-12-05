#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>







int main(int argc, char** argv){

	std::string filename = argv[1];
	std::ifstream in;
	in.open(filename);
	if(!in.is_open()){
		std::cerr << "Can't open file\n";
		in.close();
		return 1;
	}


	std::string line, point, coord;
	std::string firstPoint, garbage, secondPoint;
	int x1, y1, x2, y2;

	std::unordered_map<int, std::unordered_map<int, int>> xMap;
	//x coordinate -> map<y-coordinate> -> intersection count

	int intersections = 0;

	while(!in.eof()){
		std::getline(in, line);
		if(line.empty()) continue;

		std::stringstream ss(line);
		ss >> firstPoint >> garbage >> secondPoint;

		std::stringstream ps(firstPoint);
		std::getline(ps, coord, ',');
		y1 = stoi(coord);

		std::getline(ps, coord, ',');
		x1 = stoi(coord);
		ps.clear();

		ps.str(secondPoint);
		std::getline(ps, coord, ',');
		y2 = stoi(coord);

		std::getline(ps, coord, ',');
		x2 = stoi(coord);


		if(x1!=x2 && y1!=y2) continue;

		if(x1 > x2){
			std::swap(x1, x2);
			std::swap(y1, y2);
		}


		//Duplicate code to partially eliminate branching in loop
		if(y1 > y2){
			for(int i=x1; i<=x2; i++){
				for(int j=y1; j>=y2; j--){
					if(!xMap[i].count(j)){
						xMap[i][j] = 0;
					}else if(xMap[i][j]==1){
						intersections++;
					}

					xMap[i][j] += 1;

				}
			}

		}else{
			for(int i=x1; i<=x2; i++){
				for(int j=y1; j<=y2; j++){

					if(!xMap[i].count(j)){
						xMap[i][j] = 0;
					}else if(xMap[i][j]==1){
						intersections++;
					}

					xMap[i][j] += 1;
				}
			}
		}

	}

	std::cout << "Intersections: " << intersections << std::endl;

	in.close();

	return 0;
}