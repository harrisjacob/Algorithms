#include <ostream>

template <class T> class Node{
	template <class U>
	friend std::ostream& operator<<(std::ostream & os, Node<U> & node);
	private:
		T data;
		Node<T>* next;
	public:
		Node();
		Node(T data, Node* next);
		~Node();
		T getData();
		void setData(T data);
		Node<T>* getNext();
		void setNext(Node* next);
};

template <class T> Node<T>::Node(){
	data = 0;
	next = nullptr;
}

template <class T> Node<T>::Node(T data, Node* next){
	this->data = data;
	this->next = next;
}

template <class T> Node<T>::~Node(){}

template <class T>
T Node<T>::getData(){
	return data;
}

template <class T>
void Node<T>::setData(T data){
	this->data = data;
}

template <class T>
Node<T>* Node<T>::getNext(){
	return next;
}

template <class T>
void Node<T>::setNext(Node* next){
	this->next = next;
}

template <class T>
std::ostream & operator<<(std::ostream & os, Node<T> & node){
	os << node.data;
	return os;
}