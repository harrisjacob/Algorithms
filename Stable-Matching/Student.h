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


