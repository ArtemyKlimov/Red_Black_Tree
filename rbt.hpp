#ifndef BST_HPP
#define BST_HPP
#include <fstream>

template<typename T>
struct node{
	T key ;
	node<T> *left;
	node<T> *right;
	node<T> *parent;
	bool isRed;
	node(): isRed(true){} 

};

template<typename T>
class RBTree{
private:
	node<T>* root;
	node<T>* createLeaf(T _key, node<T>* parent);
	node<T>* insert_private(T _key, node<T>* ptr);
	void show_private(node<T>* ptr) const;
	void rotate_left(node<T>* ptr);
	void rotate_right(node<T>* ptr);
	void remove_ptr(node<T> *ptr);
	void validate(node<T> *ptr);
	void case_one(node<T> *ptr);
	void case_two(node<T> *ptr);
	void case_three(node<T> *ptr);
	void case_four(node<T> *ptr);
	void case_five(node<T> *ptr);
	void case_six(node<T>*ptr);
	void removeptr(node<T>* ptr);
	void tell_truth(node<T>* ptr);
	void printToFile_private(std::ofstream& f, node<T>* ptr) const;
	bool isExist_private(T _key, node<T>* ptr) const;	
public:
	RBTree();
	~RBTree();
	void insert(T _key);
	void show() const;
	void printToFile(std::ofstream& f) const;
	bool isExist(T _key) const;
};

#include "rbt.cpp"
#endif



