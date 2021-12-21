#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


int parsePacket(std::string&, int&);

int versionSum = 0;


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
int rstob(std::string& s, int& offset, int len){
	int r = 0;
	for(char c: s.substr(offset, len)){
		r= r<<1;
		r += (c=='0') ? 0 : 1;
	}
	offset += len;
	return r;
}


int parseLiteral(std::string& binary, int& offset){
	
	int r = 0;
	int result;
	int mask = ~(16);
	while((result = rstob(binary, offset, 5)) > 15){ //While bit 5 (higest bit) is 0
		r = r << 4;
		r |= (result & mask);
	}

	r = r << 4;
	r |= result;

	// std::cout << r << std::endl;
	return r;

}

int operatorPacket(std::string& binary, int& offset){
	
	int parseResult;
	
	if(rstob(binary, offset, 1)){
		// std::cout << "Total length encoding" << std::endl;

		int subpacket_count = rstob(binary, offset, 11);
		// std::cout << "Subpacket count: " << subpacket_count << std::endl;
		for(int i=0; i<subpacket_count; i++){
			parseResult = parsePacket(binary, offset);
		}

	}else{
		// std::cout << "Subpacket count encoding" << std::endl;
		int total_length = rstob(binary, offset, 15);
		// std::cout << "Total bit length of subpackets: " << total_length << std::endl;
		int preOffset = offset;
		while(offset-preOffset < total_length){
			parseResult = parsePacket(binary, offset);
			// std::cout << "Bits read: " << bitsRead << std::endl;
		}


	}

	return -1;

}

int parsePacket(std::string& binary, int& offset){

	int parseResult;

	int version = rstob(binary, offset, 3);
	int packet_type = rstob(binary, offset, 3);

	versionSum += version;

	// std::cout << "Version: " << version;
	// std::cout << "\tPacket Type: " << packet_type<< std::endl;

	if(packet_type == 4){
		// std::cout << "Literal Packet\n";
		parseResult = parseLiteral(binary, offset);
	}else{
		// std::cout << "Operator Packet\n";
		parseResult = operatorPacket(binary, offset);
	}

	return -1;
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

	parsePacket(binary, offset);

	std::cout << "Version Sum: " << versionSum << std::endl;

	in.close();

	return 0;
}