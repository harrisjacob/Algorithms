#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Pool.h"


enum Personel{isTeacher, isStudent};

template <class T>
void listPreferences(T* obj){
	std::cout << obj->getName() << "'s Preferences: " << std::endl;
	for(int i=0; i < 10; i++){

		std::cout << *(obj->getPrefAt(i)) << std::endl;
	}
}

template <class T, class S>
void populateObject(T* editObject, std::string name, int id, std::string prefRaw, Pool<S>* OppositePool){
	int prefIndex, prefID;
	std::stringstream values(prefRaw);

	editObject->setName(name);

	editObject->setID(id);

	while(values >> prefID){
		editObject->setPref(prefIndex++, OppositePool->getElemByID(prefID));	
	}
}


void readIn(Pool<Teacher>* TeacherPool, Pool<Student>* StudentPool, std::string filename, Personel person){
	std::string name, idString, pref;
	int TeacherPos = 0, StudentPos = 0;

	std::string oneline;

	std::ifstream myfile(filename);
	while(getline(myfile, oneline)){

		std::stringstream parseLine(oneline);

		getline(parseLine, name, ' ');
		getline(parseLine, idString, ' ');
		getline(parseLine, pref, '\n');

		if(!person){
			Teacher* newTeacher = TeacherPool->getElemAt(TeacherPos++);
			populateObject(newTeacher, name, stoi(idString), pref, StudentPool);	
		}else{
			Student* newStudent = StudentPool->getElemAt(StudentPos++);
			populateObject(newStudent, name, stoi(idString), pref, TeacherPool);	
		}
	}
}


template <class T>
void generatePool(Pool<T>* pool, int idSeed){
	for(int i=0; i<10; i++){
		T* newElement = new T();
		newElement->setID(i+idSeed);
		pool->setElemAt(newElement, i);
	}

}


int main(int argc, char** argv){

	std::string TeacherRecords = "TeacherData.txt";
	std::string StudentRecords = "StudentData.txt";

	Pool<Teacher>* TeacherPool = new Pool<Teacher>();
	Pool<Student>* StudentPool = new Pool<Student>();

	generatePool(StudentPool, 0);
	generatePool(TeacherPool, 10);

	Personel student = isStudent, teacher = isTeacher;

	readIn(TeacherPool, StudentPool, TeacherRecords, teacher);
	readIn(TeacherPool, StudentPool, StudentRecords, student);


	
	Teacher* firstTeach = new Teacher();
	Student* firstStudent = new Student();

	TeacherPool->setElemAt(firstTeach, 0);
	StudentPool->setElemAt(firstStudent, 0);

	firstStudent->setName("George");
	firstStudent->setID(23);

	std::cout << std::endl << *firstStudent << std::endl;


	std::cout << "All students are matched: "<<StudentPool->allMatched()<<std::endl;
	std::cout << "All teachers are matched: "<<TeacherPool->allMatched()<<std::endl;
	
	firstTeach->setMatched(firstStudent);
	firstStudent->setMatched(firstTeach);

	std::cout << "Preferred Position: "<<firstTeach->getPrefPosition()<<std::endl;
	std::cout << "Address of student: "<<firstStudent<<std::endl;
	std::cout << "Address of matched: "<<firstTeach->getMatched()<<std::endl;
	std::cout << "All students are matched: "<<StudentPool->allMatched()<<std::endl;
	std::cout << "All teachers are matched: "<<TeacherPool->allMatched()<<std::endl;

	std::cout << std::endl << *firstStudent << std::endl;
	
	std::cout << "Printing Student Pool:" <<std::endl;
	StudentPool->printPool();
	std::cout << "Printing Teacher Pool:" <<std::endl;
	TeacherPool->printPool();


	listPreferences(StudentPool->getElemAt(8));

	return 0;

}