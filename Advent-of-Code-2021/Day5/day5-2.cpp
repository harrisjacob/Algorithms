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


		//Duplicate code to partially eliminate branching in loop 
		if(x1==x2){
			if(y1 > y2) std::swap(y1,y2);
			for(int i=y1; i<=y2; i++){
				if(!xMap[x1].count(i)){
					xMap[x1][i] = 0;
				}else if(xMap[x1][i]==1){
					intersections++;
				}

				xMap[x1][i] += 1;
			}

		}else if(y1==y2){

			if(x1 > x2) std::swap(x1, x2);
			for(int i=x1; i<=x2; i++){
				if(!xMap[i].count(y1)){
					xMap[i][y1] = 0;
				}else if(xMap[i][y1]==1){
					intersections++;
				}

				xMap[i][y1] += 1;
			}

		}else{

			if(x1 > x2){
				std::swap(x1, x2);
				std::swap(y1, y2);
			}

			if(y1 < y2){

				for(int i=0; i<=x2-x1; i++){
					if(!xMap[x1+i].count(y1+i)){
						xMap[x1+i][y1+i] = 0;
					}else if(xMap[x1+i][y1+i]==1){
						intersections++;
					}

					xMap[x1+i][y1+i] += 1;
				}


			}else{

				for(int i=0; i<=x2-x1; i++){
					if(!xMap[x1+i].count(y1-i)){
						xMap[x1+i][y1-i] = 0;
					}else if(xMap[x1+i][y1-i]==1){
						intersections++;
					}

					xMap[x1+i][y1-i] += 1;
				}

			}


		}





	}

	std::cout << "Intersections: " << intersections << std::endl;

	in.close();

	return 0;
}