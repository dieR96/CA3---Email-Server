#include "TemplateQueue.h"

template <class T>
TemplateQueue<T>::TemplateQueue()
{
}

template <class T>
void TemplateQueue<T>::storeObj(T& obj)
{
	storage.push_front(obj);
}

template <class T>
T& TemplateQueue<T>::frontObj()
{
	typename list<T>::iterator iter = storage.end();
	iter--;
	return *iter;
}

template <class T>
void TemplateQueue<T>::removeFrontObj()
{
	typename list<T>::iterator iter = storage.end();
	iter--;
	storage.remove(*iter);
}



template <class T>
int TemplateQueue<T>::sizeOfQueue()
{
	return storage.size();
}

template <class T>
TemplateQueue<T>::~TemplateQueue()
{
}
