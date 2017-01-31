#include <iostream>
#include "rbt.hpp"
#include <fstream>

RBTree::RBTree(){
	root = nullptr;
}

node* RBTree::createLeaf(int _key, node*_parent){
	node *n = new node();
	n->key = _key;
	n->left = nullptr;
	n->right = nullptr;
	n->parent=_parent;
	return n;	
}

void RBTree::insert(int _key){
	insert_private(_key, root);
}

void RBTree::insert_private(int _key, node* ptr){
	if(ptr == nullptr){
		root = createLeaf(_key, nullptr);
		root->isRed =false;
		return;
	}
	if(ptr->key > _key){
		if(ptr->left != nullptr){
			insert_private(_key, ptr->left);
		}
		else{ 
			ptr->left = createLeaf(_key, ptr);
			validate(ptr->left);
		}
	}
	else{
		if(ptr->right != nullptr){
			insert_private(_key, ptr->right);
		}
		else {
			ptr->right = createLeaf(_key,ptr);
			std::cout<<"entered this"<<std::endl;
			validate(ptr->right);
		}
	}	
}


void RBTree::validate(node *ptr){
	if(ptr == nullptr) return;
	if(ptr == root) {
		std::cout<<"isBlack"<<std::endl;
		root->isRed = false;
		return;
	}
	node *d = ptr->parent->parent;
	if(d ==nullptr) return; //
	if((ptr->parent == d->left)&&(ptr->parent->isRed)){
		if(d->right->isRed) 
			case_one(ptr);
		if((ptr == ptr->parent->right)&&(!d->right->isRed || d->right == nullptr))
			case_two(ptr);
		if((ptr == ptr->parent->left)&&(!d->right->isRed || d->right ==nullptr))
			case_tree(ptr);
	}
	else if((ptr->parent == d->right) &&(ptr->parent->isRed)){
		if(d->left->isRed)
			case_four(ptr);
		if((ptr == ptr->parent->left)&&(!d->left->isRed || d->left == nullptr))
			case_five(ptr);
		if((ptr==ptr->parent->left)&&(!d->left->isRed || d->left == nullptr))
			case_six(ptr);
	}
	
}

void RBTree::case_four(node*ptr){
	node *d = ptr->parent->parent;
	d->right->isRed = false;
	d->left->isRed = false;
	d->isRed = true;
	validate(d);
}

void RBTree::case_six(node *ptr){
	node *d = ptr->parent->parent;
	ptr->parent->isRed =false;
	d->isRed = true;
	rotate_left(d);
}

void RBTree::case_five(node *ptr){
	rotate_right(ptr->parent);
	case_six(ptr->parent);
}

void RBTree::case_tree(node *ptr){
	node *d = ptr->parent->parent;
	ptr->parent->isRed = false;
	d->isRed = true;
	rotate_right(d);
}

void RBTree::case_two(node*ptr){
	rotate_left(ptr->parent);
	case_tree(ptr->parent); //??
}

void RBTree::case_one(node *ptr){
	node *d = ptr->parent->parent;
		d->left->isRed = false;
		d->right->isRed = false;
		d->isRed = true;
		validate(d);
}

void RBTree::show(){
	show_private(root);
}

void RBTree::show_private(node *ptr){
	if(ptr == nullptr) return;
	if(ptr->left != nullptr){
		show_private(ptr->left);
	}
	std::cout<<ptr->key<<" ";
	if(ptr->right !=nullptr){
		show_private(ptr->right);
	}
}



void RBTree::rotate_left(node *ptr){
	if(ptr !=nullptr){
		node *r = ptr->right;
		if(r == nullptr) return;
		node *p = ptr->parent;		
		if(ptr == p->right) p->right = r;
		else p->left = r;
		ptr->right = r->left;
		if(r->left != nullptr) r->left->parent = ptr;
		r->left = ptr;
		ptr->parent = r;		
	}
}

void RBTree::rotate_right(node *ptr){
	if(ptr !=nullptr){
		node *l =ptr->left;
		if( l == nullptr) return;
		node *p =ptr->parent;
		if(ptr ==p->right) p->right = l;
		else p->left = l;	
		ptr->left = l->right;
		if(l->right !=nullptr) l->right->parent = ptr;
		l->right = ptr;
		ptr->parent = l;
	}
}

RBTree::~RBTree(){
	removeptr(root);
}

void RBTree::removeptr(node* Ptr){
	if(Ptr != nullptr){
		if(Ptr->left != nullptr){
			removeptr(Ptr->left);
		}
		if(Ptr->right != nullptr) {
			removeptr(Ptr->right);
		}
		delete Ptr;
	}
}





