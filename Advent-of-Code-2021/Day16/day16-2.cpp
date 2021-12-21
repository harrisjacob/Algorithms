#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

long parsePacket(std::string&, int&);

std::string getLine(std::ifstream& in){
	std::string s;
	std::getline(in, s);
	if(!in.good() || s.empty()) return s;
	std::stringstream ss(s);
	std::getline(ss, s, '\r');
	if(!in.good()) return s;
	return s;
}

//Convert binary from substring
long rstob(std::string& s, int& offset, int len){
	long r = 0;
	for(char c: s.substr(offset, len)){
		r= r<<1;
		r += (c=='0') ? 0 : 1;
	}
	offset += len;
	return r;
}

//Packet is a literal, return its value
long parseLiteral(std::string& binary, int& offset){
	
	long r = 0;
	long result;
	long mask = ~(16);
	while((result = rstob(binary, offset, 5)) > 15){ //While bit 5 (higest bit) is 0
		r = r << 4;
		r |= (result & mask);
	}

	r = r << 4;
	r |= result;

	return r;

}

//Packet is an operator, resolve its subpackets and execute the operation, returning the result
long operatorPacket(std::string& binary, int& offset, int op){
	
	long result=-1;
	std::vector<long> arguments;

	if(rstob(binary, offset, 1)){

		int subpacket_count = rstob(binary, offset, 11);
		for(int i=0; i<subpacket_count; i++){
			arguments.push_back(parsePacket(binary, offset));
		}

	}else{

		int total_length = rstob(binary, offset, 15);
		int preOffset = offset;
		while(offset-preOffset < total_length){
			arguments.push_back(parsePacket(binary, offset));
		}

	}

	switch(op){
		case 0:
			//sum
			result = 0;
			for(long i:arguments) result+=i;
			break;
		case 1:
			//product
			result = 1;
			for(long i:arguments) result*=i;
			break;
		case 2:
			//Minimum
			result = arguments[0];
			for(long i:arguments) result = std::min(result, i);
			break;
		case 3:
			//Maximum
			result = arguments[0];
			for(long i:arguments) result = std::max(result, i);
			break;
		case 5:
			//Greater than
			result = arguments[0] > arguments[1];
			break;
		case 6:
			//Less than
			result = arguments[0] < arguments[1]; 
			break;
		case 7:
			//Equal to
			result = arguments[0] == arguments[1];
			break;
		default:
			std::cerr << "Unknown operation requested" << std::endl;
	}

	return result;

}

//Determine type of packet and handle dispatch =
long parsePacket(std::string& binary, int& offset){


	int version = rstob(binary, offset, 3);
	int packet_type = rstob(binary, offset, 3);

	return (packet_type == 4) ? parseLiteral(binary, offset) : operatorPacket(binary, offset, packet_type);

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


	std::string numberBinary[] = {"0000","0001","0010","0011", "0100","0101","0110","0111", "1000","1001"};
								//	0	   1   	  2	     3		 4		5	   6	  7		  8		 9

	std::string letterBinary[] = {"1010","1011","1100","1101","1110","1111"};
								//	 A 		B 	   C 	  D 	 E 		F

	std::string line;
	std::string binary = std::string();

	//Convert to binary
	while(!(line=getLine(in)).empty()){

		for(char c: line){

			if(c <= '9'){
				binary += numberBinary[c-'0'];
			}else{
				binary += letterBinary[c-'A'];
			}

		}

	}

	int offset = 0;

	long result = parsePacket(binary, offset);

	std::cout << "Decoded packet result: " << result << std::endl;

	in.close();

	return 0;
}