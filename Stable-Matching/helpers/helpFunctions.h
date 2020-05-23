#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Pool.h"

#define POOL_SZ 10 
enum Personel{isTeacher, isStudent};

template <class T>
void listPreferences(T* obj){
	std::cout << obj->getName() << "'s Preferences: " << std::endl;
	for(int i=0; i < 10; i++){

		std::cout << *(obj->getPrefAt(i)) << std::endl;
	}
}

template <class T, class S>
void populateObject(T* editObject, std::string name, int id, std::string prefRaw, Pool<S,T>* OppositePool){
	int prefIndex, prefID;
	std::stringstream values(prefRaw);

	editObject->setName(name);

	editObject->setID(id);

	while(values >> prefID){
		editObject->setPref(prefIndex++, OppositePool->getElemByID(prefID));	
	}
}


void readIn(Pool<Teacher, Student>* TeacherPool, Pool<Student, Teacher>* StudentPool, std::string filename, Personel person){
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


template <class T, class S>
void generatePool(Pool<T, S>* pool, int idSeed){
	for(int i=0; i<10; i++){
		T* newElement = new T();
		newElement->setID(i+idSeed);
		pool->setElemAt(newElement, i);
	}

}

void fillPools(Pool<Teacher, Student>* teacherPool, Pool<Student, Teacher>* studentPool, std::string teacherFile, std::string studentFile){
	Personel student = isStudent, teacher = isTeacher;
	readIn(teacherPool, studentPool, teacherFile, student);
	readIn(teacherPool, studentPool, studentFile, teacher);
}

bool tryUpgrade(Student* newStud, Teacher* teach){
	Student* oldStud = teach->getMatched();
	if(oldStud){
		if( (teach->getPrefOf(oldStud)) <= (teach->getPrefOf(newStud)) ) return 0; //Not an upgrade
	}
	newStud->setMatched(teach);
	teach->setMatched(newStud);
	oldStud->setMatched(nullptr);
	return 1;
}

void printResults(Pool<Student, Teacher>* studentPool){
	Teacher* teach;
	studentPool->printMatches(teach);
}

void verifyStable(Pool<Student, Teacher>* studentPool){
	Teacher* teach;
	studentPool->verify(teach);
}