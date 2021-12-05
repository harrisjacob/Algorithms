#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, char** argv){

	std::string filename = argv[1];
	std::ifstream in;
	in.open(filename);
	if(!in.is_open()){
		std::cerr << "Can't open file\n";
		in.close();
		return 1;
	}

	int xpos = 0;
	int ypos = 0;

	int aim = 0;

	std::string input;
	int dist;
	std::string line;

	while(!in.eof()){
		std::getline(in, line);
		
		if(line.empty()) continue;

		std::istringstream iss(line.c_str());

		iss >> input >> dist;

		if(!input.compare("forward")){
			xpos += dist;
			ypos += dist*aim;
		}else if(!input.compare("down")){
			aim += dist;
		}else if(!input.compare("up")){
			aim -= dist;
		}else{
			break;
		}


	}


	std::cout << xpos*ypos << std::endl;
	in.close();
	return 0;
}