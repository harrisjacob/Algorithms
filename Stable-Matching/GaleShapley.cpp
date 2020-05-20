#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream>
#include "helpers/helpFunctions.h"



void usage(char* prog){
	std::cout << "Usage:" << std::endl;
	std::cout << "-h\t help"<<std::endl;
	std::cout << "-s\t specify student data file"<<std::endl;
	std::cout << "-t\t specify teacher data file"<<std::endl;
	std::cout << "Example usage: " << prog << " -s [StudentData] -t [TeacherData]\n" << std::endl;
	std::cout << "Usage Notes:" <<std::endl;
	std::cout << "Both StudentData and TeacherData must be spefied, but their order is irrelevant."<<std::endl;
	std::cout << "Each file should contain 10 entries. Each entry should conist of a name, an ID, \n" <<
				 "and an ordered listing of the IDs of the opposite group listed highest preference\n" <<
				 "to lowest. Entries should contain space delimited elements and be newline terminated.\n" <<
				 "Each entry should list preferences for all 10 members of the opposite group.\n" <<
				 "Valid student IDs are in the range 0-9 and valid teacher IDs are in the range 10-19." << std::endl;

}

void runGS(Pool<Teacher, Student>* tp, Pool<Student, Teacher>* sp){
	
	Student* currentStud;
	Teacher* potTeacher;
	while(!(sp->allMatched())){
		for(int stud = 0; stud < POOL_SZ; stud++){
			currentStud = sp->getElemAt(stud);
			
			if(currentStud->isMatched()) continue; //Skip if matched
				
			potTeacher = currentStud->getHighPref(); //Get the highest current preferce
			if(potTeacher->isMatched()){
				if(tryUpgrade(currentStud, potTeacher)) sp->resetHighPref();
			}else{
				currentStud->setMatched(potTeacher);
				potTeacher->setMatched(currentStud);
			}
		}

	}

	//Student gets first preference
	//Teacher responds maybe to the highest priorty and no to other
	//Students and then in the teacher's class and the teacher then has the student

	//Each student without a class applies for the next available class in their preferences
	//If applied student is better than current student, teacher can upgrade and the
	//origin student should then search for a new teacher (jilt)

	//Repeat until everyone is paired
}




int main(int argc, char** argv){

	int opt;
	std::string studentFile, teacherFile;
	//if help flag
	while((opt = getopt(argc, argv, "hs:t:")) != -1 ){
		switch(opt){
			case 'h':
				usage(argv[1]);
				return 0;
			case 's':
				studentFile = optarg;
				break;
			case 't':
				teacherFile = optarg;
				break;
			default:
				usage(argv[1]);
				return 1;
		}
	}


	if(argc != 5){
		usage(argv[0]);
		return 1;
	}


	Pool<Teacher, Student>* TeacherPool = new Pool<Teacher, Student>();
	Pool<Student, Teacher>* StudentPool = new Pool<Student, Teacher>();
	
	generatePool(StudentPool, 0);
	generatePool(TeacherPool, 10);

	fillPools(TeacherPool, StudentPool, studentFile, teacherFile);

	runGS(TeacherPool, StudentPool);
	
	printResults(StudentPool);

	return 0;
}