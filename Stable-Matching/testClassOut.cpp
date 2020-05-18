
#include <iostream>
#include "Teacher.h"
#include "Student.h"

using namespace std;

int main(int argc, char** argv){

	Teacher* firstTeach = new Teacher();
	Student* firstStudent = new Student();

	firstTeach->setMatched(firstStudent);

	cout << "Preferred Position: "<<firstTeach->getPrefPosition()<<endl;
	cout << "Address of student: "<<firstStudent<<endl;
	cout << "Address of matched: "<<firstTeach->getMatched()<<endl;

}