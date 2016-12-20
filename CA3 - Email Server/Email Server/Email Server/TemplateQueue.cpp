#include "TemplateQueue.h"

// default constructor for class
template <class T>
TemplateQueue<T>::TemplateQueue()
{
}

// simply add a new object to the front of the queue, maybe back would have work better for queue 
template <class T>
void TemplateQueue<T>::storeObj(T& obj)
{
	storage.push_front(obj);
}

// return and do not modify the front object in the queue
template <class T>
T& TemplateQueue<T>::frontObj()
{
	// require iterator from end of storage back one to get the last element at the front of the list
	typename list<T>::iterator iter = storage.end();
	iter--;
	return *iter;
}

// remove the object from the front of queue and do not return it before deletion
template <class T>
void TemplateQueue<T>::removeFrontObj()
{
	typename list<T>::iterator iter = storage.end();
	iter--;
	storage.remove(*iter);
}

// return size of the underlying list of the queue back to the user
template <class T>
int TemplateQueue<T>::sizeOfQueue()
{
	return storage.size();
}

// normal destructor of the class, no dynamic memory to release in this class
template <class T>
TemplateQueue<T>::~TemplateQueue()
{
}
