#ifndef _SLLIST_H_
#define _SLLIST_H_

template<typename Type> class SLLIter;

//
// LIST CLASS
//
template<typename Type>
class SLList
{
	friend class SLLIter < Type > ;
	struct Node
	{
		Type element;
		Node* next;
	};
	Node* head;
	unsigned int Size;
public:
	SLList();
	~SLList();
	SLList(const SLList<Type>& obj);
	SLList<Type>& operator=(const SLList<Type>& obj);
	void addHead(const Type& v);
	void clear();
	void insert(SLLIter<Type>& index, const Type& v);
	void remove(SLLIter<Type>& index);
	inline unsigned int size() const{ return Size; }
};
template<typename Type>
SLList<Type>::SLList()
{
	head = nullptr;
	//head->next = nullptr;
	Size = 0;
}
template<typename Type>
SLList<Type>::~SLList()
{
	clear();
}
template<typename Type>
SLList<Type>::SLList(const SLList<Type>& obj)
{
	/*Node* tmp = obj.head;
	while (tmp != nullptr)
	{
		Node* n = new Node;
		n->element = tmp->element;
		tmp = tmp->next;
		n->next = head;
		head = n;
	}
	Size = obj.Size;*/
	if (obj.head != nullptr)
	{
		Node* tmp = obj.head;
		addHead(tmp->element);
		Node* n = head;
		tmp = tmp->next;
		while (tmp != nullptr)
		{
			n->next = new Node;
			n = n->next;
			n->next = nullptr;
			n->element = tmp->element;
			tmp = tmp->next;
			//n->next = head;
			//head = n;
		}
	}
	Size = obj.Size;
}
template<typename Type>
SLList<Type>& SLList<Type>::operator=(const SLList<Type>& obj)
{
	if (this != &obj)
	{
		clear();
		if (obj.head != nullptr)
		{
			Node* tmp = obj.head;
			addHead(tmp->element);
			Node* n = head;
			tmp = tmp->next;
			while (tmp != nullptr)
			{
				n->next = new Node;
				n = n->next;
				n->next = nullptr;
				n->element = tmp->element;
				tmp = tmp->next;
				//n->next = head;
				//head = n;
			}
		}
	}
	Size = obj.Size;
	return *this;
}
template<typename Type>
void SLList<Type>::addHead(const Type& v)
{
	//if (head->next == nullptr)
		//head->element = 
	Node* n = new Node;
	n->element = v;
	n->next = head;
	head = n;
	Size++;
}
template<typename Type>
void SLList<Type>::clear()
{
	while (head != nullptr)
	{
		Node* tmp = head;
		head = head->next;
		delete tmp;
	}
	Size = 0;
}
template<typename Type>
void SLList<Type>::insert(SLLIter<Type>& index, const Type& v)
{
	if (index.curr != nullptr)
	{
		if (index.curr == head)
		{
			addHead(v);
			index.curr = head;
		}
		else
		{
			Node* n = new Node;
			n->element = v;
			index.prev->next = n;
			n->next = index.curr;
			index.curr = index.prev->next;
			Size++;
		}
	}
}
template<typename Type>
void SLList<Type>::remove(SLLIter<Type>& index)
{
	if (index.curr != nullptr)
	{
		if (index.curr == head)
		{
			head = head->next;
			delete index.curr;
			index.curr = head;
			Size--;
		}
		else
		{
			index.prev->next = index.curr->next;
			delete index.curr;
			index.curr = index.prev->next;
			Size--;
		}
	}
}

//
// ITERATOR CLASS
//
template<typename Type>
class SLLIter
{
	friend class SLList < Type > ;
	typename SLList<Type>::Node* curr;
	typename SLList<Type>::Node* prev;
	SLList<Type>* theList;
public:
	SLLIter(SLList<Type>& list);
	void begin();
	bool end() const;
	SLLIter<Type>& operator++();
	Type& current() const;
};
template<typename Type>
SLLIter<Type>::SLLIter(SLList<Type>& list)
{
	theList = &list;
	curr = theList->head;
	prev = nullptr;
}
template<typename Type>
void SLLIter<Type>::begin()
{
	curr = theList->head;
	prev = nullptr;
}
template<typename Type>
bool SLLIter<Type>::end() const
{
	if (curr == nullptr)
		return true;
	else
		return false;
}
template<typename Type>
SLLIter<Type>& SLLIter<Type>::operator++()
{
	if (!end())
	{
		prev = curr;
		curr = curr->next;
	}
	return *this;
}
template<typename Type>
Type& SLLIter<Type>::current() const
{
	return curr->element;
}
#endif