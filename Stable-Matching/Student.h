#include <string>
class Teacher;

class Student{
friend std::ostream& operator<<(std::ostream &, Student &);
private:
	std::string Name;
	int id;
	Teacher* preferences[10];
	Teacher* matched;
	int prefPosition;
public:
	Student();
	~Student();
	void setPref(int pref, Teacher* student);
	Teacher* getPref();
	std::string getName();
	void setName(std::string newName);
	int getID();
	void setID(int newID);
	bool isMatched();
	Teacher* getMatched();
	void setMatched(Teacher* teacher);
	int getPrefPosition();

};

Student::Student():preferences{nullptr}{
	Name = "Empty Name";
	id = -1;
	matched = nullptr;
	prefPosition = 0;
}

Student::~Student(){}

void Student::setPref(int pref, Teacher* teacher){
	preferences[pref] = teacher;
}

Teacher* Student::getPref(){ return preferences[prefPosition]; }

bool Student::isMatched(){
	return (matched) ? true : false;
}

std::string Student::getName(){ return Name; }

void Student::setName(std::string newName){
	Name = newName;
}

int Student::getID(){ return id; }

void Student::setID(int newID){
	id = newID;
}

Teacher* Student::getMatched(){ return matched; }

void Student::setMatched(Teacher* teacher){
	matched = teacher;
}

int Student::getPrefPosition(){ return prefPosition; }

std::ostream & operator<<(std::ostream & os, Student & student){

        os << "Name: " <<student.getName() << std::endl;
        os << "Student ID: "<<student.getID()<<std::endl;
        os << "Matched: "<< ((student.isMatched()) ? "True" : "False" )<< std::endl;
        return os;
}
