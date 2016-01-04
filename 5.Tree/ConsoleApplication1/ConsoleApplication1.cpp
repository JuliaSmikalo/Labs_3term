#include "stdafx.h"
#include <iostream>
#include <list>

using namespace std;

template <typename T>
class Tree : public list< Tree<T> > {
private:
	typedef list< Tree<T> > _list;

public:
	T value;
	class iterator;
	friend class iterator;



	T maxValue() const{
		T max = value;

		for (typename _list::const_iterator it = _list::begin(); it != _list::end(); it++){
			T tmp = it->maxValue();

			if (tmp > max)
				max = tmp;
		}

		return max;
	}

	T minValue() const{
		T min = value;

		for (typename _list::const_iterator it = _list::begin(); it != _list::end(); it++){
			T tmp = it->maxValue();

			if (tmp < min)
				min = tmp;
		}

		return min;
	}

	bool operator<(const Tree& other) const{
		return maxValue() < other.minValue();
	}

	bool operator>(const Tree& other) const{
		return minValue() > other.maxValue();
	}


	bool operator==(const Tree& other) const{
		bool eq = false;

		eq = this->value == other.value;

		if (eq)
			eq = _list::size() == other.size();

		if (eq){
			typename _list::const_iterator it1;
			typename _list::const_iterator it2;

			it1 = _list::begin();
			it2 = other.begin();

			while ((it1 != _list::end()) && it2 != other.end()){

				eq = it1->value == it2->value && (*it1) == (*it2);

				if (!eq)
					break;
				
				it1++;
				it2++;
			}

		}

		return eq;
	}
	class iterator;

	iterator begin(){
		return this;
	}

	iterator end(){
		iterator e(this, _list::end());

		return e;
	}


	class iterator
	{
		friend class Tree;

	public:
		iterator(typename _list::iterator it) : ptr_tree(&(*it)) {
			ptr_list_p = NULL;
			ptr_list = ptr_tree->_list::begin();
		}
		iterator(Tree<T>* ptr) : ptr_tree(ptr) {
			ptr_list_p = NULL;
			ptr_list = ptr_tree->_list::begin();
		}
		iterator(Tree<T>* ptr, typename _list::iterator it) : ptr_tree(ptr) {
			ptr_list_p = NULL;
			ptr_list = it;
		}

		iterator operator++() {

			if (ptr_list != ptr_tree->_list::end()){
				if (NULL == ptr_list_p){
					ptr_list_p = new Tree<T>::iterator(ptr_list);
				}
				else
				{
					(*ptr_list_p)++;

					if (ptr_list_p->ptr_list == (ptr_list_p->ptr_tree)->_list::end())
					{
						ptr_list++;
						if (ptr_list != ptr_tree->_list::end())
							ptr_list_p = new Tree<T>::iterator(ptr_list);
						else
							ptr_list_p = NULL;
					}
				}
			}

			return *this;
		}
		iterator operator++(int junk) {
			iterator i = *this;
			++(*this);
			return i;
		}

		Tree<T>* operator&() {
			if (ptr_list_p != NULL)
				return *ptr_list_p;
			else
				return ptr_tree;
		}
		Tree<T>& operator*() {
			if (ptr_list_p != NULL)
				return *(*ptr_list_p);
			else
				return *ptr_tree;
		}
		Tree<T>* operator->() {
			if (ptr_list_p != NULL)
				return &(*(*ptr_list_p));
			else
				return ptr_tree;
		}

		int level(){
			if (ptr_list_p != NULL){
				return ptr_list_p->level() + 1;
			}

			return 0;
		}

		bool operator==(const iterator& rhs) { return ptr_tree == rhs.ptr_tree && ptr_list_p == rhs.ptr_list_p && ptr_list == rhs.ptr_list; }
		bool operator!=(const iterator& rhs) { return !operator==(rhs); }

	private:
		Tree<T>* ptr_tree;
		typename Tree<T>::iterator* ptr_list_p;
		typename _list::iterator ptr_list;
	};



};

int main() {
	cout << "Start" << endl;

	Tree<int> MyTreeRoot;

	MyTreeRoot.value = 0;

	Tree<int> MyTree1;
	Tree<int> MyTree2;
	Tree<int> MyTree3;
	Tree<int> MyTree21;

	MyTree1.value = 1;
	MyTree2.value = 2;
	MyTree3.value = 3;
	MyTree21.value = 21;


	MyTree2.push_back(MyTree21);
	MyTree3.push_back(MyTree21);
	MyTree3.push_back(MyTree21);

	MyTreeRoot.push_back(MyTree2);
	MyTreeRoot.push_back(MyTree1);
	MyTreeRoot.push_back(MyTree3);

	for (Tree<int>::iterator it = MyTreeRoot.begin(); it != MyTreeRoot.end(); it++){
		cout << it->value << " " << it.level() << endl;
	}

	MyTreeRoot.sort();

	cout << "\n";
	Tree<int>::iterator it = MyTreeRoot.begin();

	while (it != MyTreeRoot.end()){
		cout << it->value << " " << it.level() << endl;
		it++;
	}


	system("pause");
	// your code goes here
	return 0;
}
