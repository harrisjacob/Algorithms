#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>


int checkChar(char canChar, char stkChar){

	switch(canChar){
		case ')':
			if(stkChar != '(') return 3;
			break;
		case ']':
			if(stkChar != '[') return 57;
			break;
		case '}':
			if(stkChar != '{') return 1197;
			break;
		case '>':
			if(stkChar != '<') return 25137;
			break;
	}

	return 0;

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

	unsigned long score = 0;
	while(!in.eof()){

		std::getline(in, line);
		if(line.empty()) continue;
		std::stringstream ss(line);
		ss >> input;

		std::stack<char> stk;
		for(char c: input){

			if(c=='[' || c=='(' || c=='{' || c=='<') stk.push(c);
			else{
				score+=checkChar(c, stk.top());
				stk.pop();
			}			
			
		}


	}
	std::cout << "Score: " << score << std::endl;



	in.close();

	return 0;
}