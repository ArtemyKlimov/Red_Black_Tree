#ifndef BST_HPP
#define BST_HPP
#include <fstream>

typedef struct node{
	int key ;
	node *left;
	node *right;
	node *parent;
	bool isRed;
	node(): isRed(true){} 

}node;


class RBTree{
private:
	node* root;
	node* createLeaf(int _key, node* parent);
	node* insert_private(int _key, node* ptr);
	void show_private(node* ptr);
	void rotate_left(node* ptr);
	void rotate_right(node* ptr);
	void remove_ptr(node *ptr);
	void validate(node *ptr);
	void case_one(node *ptr);
	void case_two(node *ptr);
	void case_three(node *ptr);
	void case_four(node *ptr);
	void case_five(node *ptr);
	void case_six(node*ptr);
	void removeptr(node* ptr);
	void tell_truth(node* ptr);	
public:
	RBTree();
	~RBTree();
	void insert(int _key);
	void show();
	

};


#endif



