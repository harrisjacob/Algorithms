#include <string>

class Student;

class Teacher{
friend std::ostream& operator<<(std::ostream &, Teacher &);
private:
	std::string Name;
	int id;
	Student* preferences[10];
	Student* matched;
	int prefPosition;
public:
	Teacher();
	~Teacher();
	Student* getPrefAt(int index);
	Student* getHighPref();
	void setPref(int pref, Student* student);
	std::string getName();
	void setName(std::string name);
	int getID();
	void setID(int newID);
	int getStudentID(Student* student);
	bool isMatched();
	Student* getMatched();
	void setMatched(Student* student);
	int getPrefPosition();

};

