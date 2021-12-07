#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>


int main(int argc, char** argv){

	std::string filename = argv[1];
	std::ifstream in;
	in.open(filename);
	if(!in.is_open()){
		std::cerr << "Can't open file\n";
		in.close();
		return 1;
	}


	//Find the median element using two priorty queues
	std::string line;
	std::priority_queue<int> maxQ;
	std::priority_queue<int, std::vector<int>, std::greater<int>> minQ;
	int newVal;

	while(!in.eof()){
		std::getline(in, line, ',');
		newVal = stoi(line);

		if(!minQ.empty() && newVal > minQ.top()){
			minQ.push(newVal);
		}else{
			maxQ.push(newVal);
		}


		if(maxQ.size() > minQ.size() + 1){
			minQ.push(maxQ.top());
			maxQ.pop();
		}

		if(minQ.size() > maxQ.size() + 1){
			maxQ.push(minQ.top());
			minQ.pop();
		}

	}

	int fuelLocation = maxQ.top();

	//If the count of numbers is odd the median is trivial
	//If the count is even, any integer between the two median elements will provide the same answer
	std::cout << "Most efficient fuel location: " << fuelLocation << std::endl;

	int totalFuel = 0;
	while(!maxQ.empty()){
		totalFuel += (maxQ.top() > fuelLocation) ? maxQ.top()-fuelLocation : fuelLocation - maxQ.top();
		maxQ.pop();
	}


	while(!minQ.empty()){
		totalFuel += (minQ.top() > fuelLocation) ? minQ.top()-fuelLocation : fuelLocation - minQ.top();
		minQ.pop();
	}

	std::cout << "This consumes " << totalFuel << " units of fuel" << std::endl;


	in.close();

	return 0;
}