#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <queue>

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
	bool corrupted;
	std::priority_queue<unsigned long> maxQ;
	std::priority_queue<unsigned long, std::vector<unsigned long>, std::greater<unsigned long>> minQ;

	unsigned long score;
	while(!in.eof()){

		std::getline(in, line);
		if(line.empty()) continue;
		std::stringstream ss(line);
		ss >> input;

		score = 0;
		std::stack<char> stk;
		corrupted = false;

		for(char c: input){

			if(c=='[' || c=='(' || c=='{' || c=='<') stk.push(c);
			else{

				if( c == ')' && stk.top() != '(') corrupted = true;
				else if( c==']' && stk.top() != '[') corrupted = true;
				else if( c=='}' && stk.top() != '{') corrupted = true;
				else if( c=='>' && stk.top() != '<') corrupted = true;
				stk.pop();
			}

			if(corrupted) break;
		}

		if(corrupted) continue;

		char t;
		while(!stk.empty()){
			score *= 5;
			t = stk.top(); stk.pop();
			switch(t){
				case '(':
					score += 1;
					break;
				case '[':
					score += 2;
					break;
				case '{':
					score += 3;
					break;
				case '<':
					score += 4;
					break;
			}

		}

		
		if(!minQ.empty() && score > minQ.top()){
			minQ.push(score);
		}else{
			maxQ.push(score);
		}

		if(minQ.size() > maxQ.size() +1){
			maxQ.push(minQ.top());
			minQ.pop();
		}

		if(maxQ.size() > minQ.size() +1){
			minQ.push(maxQ.top());
			maxQ.pop();
		}

	}
	
	std::cout << "Median score is: " << ((minQ.size() > maxQ.size()) ? minQ.top() : maxQ.top()) << std::endl;


	in.close();

	return 0;
}