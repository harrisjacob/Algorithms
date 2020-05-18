
class Student;

class Teacher{
private:
	Student* preferences[10];
	Student* matched;
	int prefPosition;
public:
	Teacher();
	~Teacher();
	void setPref(int pref, Student* student);
	Student* getPref();
	Student* getMatched();
	void setMatched(Student* student);
	int getPrefPosition();

};

Teacher::Teacher(){
	for(int i=0; i<10;i++){
		preferences[i]=nullptr;
	}
	matched = nullptr;
	prefPosition = 0;
}

Teacher::~Teacher(){}

void Teacher::setPref(int pref, Student* student){
	preferences[pref] = student;
}

Student* Teacher::getPref(){ return preferences[prefPosition]; }

Student* Teacher::getMatched(){ return matched; }

void Teacher::setMatched(Student* student){
	matched = student;
}

int Teacher::getPrefPosition(){ return prefPosition; }

