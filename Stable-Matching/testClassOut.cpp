#include <iostream>
#include "Pool.h"

int main(int argc, char** argv){

	Teacher* firstTeach = new Teacher();
	Student* firstStudent = new Student();
	Pool<Teacher>* TeacherPool = new Pool<Teacher>();
	Pool<Student>* StudentPool = new Pool<Student>();


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

	std::cout << std::endl << *firstStudent;

}