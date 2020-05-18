#include "Student.h"
#include "Teacher.h"

template <class T> class Pool{
	private:
		T* elements[10];
	public:
		Pool();
		~Pool();
		void setElemAt(T* element, int index);
		T* getElemAt(int index);
		int getIndexOf(T* element);
		bool allMatched();
};

template <class T> Pool<T>::Pool():elements{nullptr}{}

template <class T> Pool<T>::~Pool<T>(){}

template <class T>
void Pool<T>::setElemAt(T* element, int index){
	elements[index] = element;
}


template <class T>
T* Pool<T>::getElemAt(int index){ return elements[index]; }

template <class T>
int Pool<T>::getIndexOf(T* element){
	for(int i=0;i<10;i++){
		if(element == elements[i]) return i;
	}
	return NULL;
}

template <class T>
bool Pool<T>::allMatched(){
	for(int i=0;i<10;i++){
		if(!elements[i]) return true; //Array is not filled
		if(!(elements[i]->isMatched())) return false; //Unmatched found
	}
	return true;
}