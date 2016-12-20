#pragma once
#include <list>
#include "Email.h"

using std::list;


// templated queue made out from list that adds data and removes it from the end, memory storage is working opposite way, must be list memory allocation implementation causing this
template <class T>
class TemplateQueue
{
private:
	list<T> storage;
public:
	TemplateQueue();
	void storeObj(T& obj);
	T& frontObj();
	void removeFrontObj();
	int sizeOfQueue();

	~TemplateQueue();
};

// compile the two files of a template class together and exclude the below file from the visual studio build from project
#include "TemplateQueue.cpp"

