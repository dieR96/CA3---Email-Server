#pragma once
#include <list>
#include "Email.h"

using std::list;

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

#include "TemplateQueue.cpp"

