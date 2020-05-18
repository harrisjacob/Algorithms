
class Teacher;

class Student{
private:
	Teacher* preferences[10];
	Teacher* matched;
	int prefPosition;
public:
	Student();
	~Student();
	void setPref(int pref, Teacher* student);
	Teacher* getPref();
	Teacher* getMatched();
	void setMatched(Teacher* teacher);
	int getPrefPosition();

};

Student::Student(){
	for(int i=0; i<10;i++){
		preferences[i]=nullptr;
	}
	matched = nullptr;
	prefPosition = 0;
}

Student::~Student(){}

void Student::setPref(int pref, Teacher* teacher){
	preferences[pref] = teacher;
}

Teacher* Student::getPref(){ return preferences[prefPosition]; }

Teacher* Student::getMatched(){ return matched; }

void Student::setMatched(Teacher* teacher){
	matched = teacher;
}

int Student::getPrefPosition(){ return prefPosition; }