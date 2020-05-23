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
	Teacher* getPrefAt(int index);
	void setPref(int pref, Teacher* student);
	int getPrefOf(Teacher* teacher);
	Teacher* getHighPref();
	void setHighPref(int hpref);
	std::string getName();
	void setName(std::string newName);
	int getID();
	void setID(int newID);
	bool isMatched();
	Teacher* getMatched();
	void setMatched(Teacher* teacher);
	int getPrefPosition();
};


