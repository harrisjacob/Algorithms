
#include <iostream>
#include "Pool.h"

using namespace std;

int main(int argc, char** argv){

	Teacher* firstTeach = new Teacher();
	Student* firstStudent = new Student();
	Pool<Teacher>* TeacherPool = new Pool<Teacher>();
	Pool<Student>* StudentPool = new Pool<Student>();


	TeacherPool->setElemAt(firstTeach, 0);
	StudentPool->setElemAt(firstStudent, 0);

	cout << "All students are matched: "<<StudentPool->allMatched()<<endl;
	cout << "All teachers are matched: "<<TeacherPool->allMatched()<<endl;
	
	firstTeach->setMatched(firstStudent);
	firstStudent->setMatched(firstTeach);

	cout << "Preferred Position: "<<firstTeach->getPrefPosition()<<endl;
	cout << "Address of student: "<<firstStudent<<endl;
	cout << "Address of matched: "<<firstTeach->getMatched()<<endl;
	cout << "All students are matched: "<<StudentPool->allMatched()<<endl;
	cout << "All teachers are matched: "<<TeacherPool->allMatched()<<endl;

}