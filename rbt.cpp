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
	node* n = insert_private(_key, root);
	validate(n);
	//tell_truth(n);
}
void RBTree::tell_truth(node* n){
	std::cout<<n->key;
	if(n->parent){
		if(n->parent->isRed) std::cout<<"my parent is red - "<<n->parent->key<<std::endl;
		else std::cout<<"my parent is black - "<<n->parent->key<<std::endl;
			if(n->parent->parent) {
			std::cout<<"my dad is: "<<n->parent->parent->key;
			if(n->parent->parent->isRed) std::cout<<"  is red - "<<std::endl;
			else std::cout<<" my parent is black - "<<std::endl;
		}
	}
}
	

node* RBTree::insert_private(int _key, node* ptr){
//	std::cout<<"INSERTION "<<_key<<std::endl;
	node* n = nullptr;
	if(ptr == nullptr){
		root = createLeaf(_key, nullptr);
		root->isRed =false;
		n = root;
	}
	else{
		if(ptr->key > _key){
			if(ptr->left != nullptr){
				n = insert_private(_key, ptr->left);
			}
			else{ 
				ptr->left = createLeaf(_key, ptr);
				n = ptr->left;
			}
		}
		else{
			if(ptr->right != nullptr){
				n =insert_private(_key, ptr->right);
			}
			else {
				ptr->right = createLeaf(_key, ptr);
				n = ptr->right;
			}
		}
	}
	return n;	
}
void RBTree::validate(node *ptr){
	if(ptr == root) {
		root->isRed = false;
		return;
	}
	node *d = ptr->parent->parent;
	if(d ==nullptr) return; //
	if((ptr->parent == d->left)&&(ptr->parent->isRed)){
		if(d->right)
			if(d->right->isRed){
//				std::cout<<"case 1"<<std::endl;
				case_one(ptr);
				return;
			}
		if((ptr == ptr->parent->right)&&(d->right == nullptr || !d->right->isRed)){
//			std::cout<<"case 2"<<std::endl;
			case_two(ptr);
			return;
		}
		if((ptr == ptr->parent->left)&&(d->right ==nullptr || !d->right->isRed)){
//			std::cout<<"case 3"<<std::endl;
			case_three(ptr);
			return;
		}
	}
	else if((ptr->parent == d->right) &&(ptr->parent->isRed)){
		if((ptr == ptr->parent->right)&&(d->left == nullptr || !d->left->isRed)){
//			std::cout<<"case 6"<<std::endl;
			case_six(ptr);
			return;
		}
		if (d->left)
			if(d->left->isRed ){
//				std::cout<<"case 4"<<std::endl;
				case_four(ptr);
				return;
			}
		if((ptr == ptr->parent->left)&&(d->left == nullptr || !d->left->isRed)){
//			std::cout<<"case 5"<<std::endl;
			case_five(ptr);
			return;
		}
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
	if(ptr->parent != nullptr){
		ptr->parent->isRed =false;
		if(ptr->parent->parent != nullptr){
			ptr->parent->parent->isRed = true;
			rotate_left(ptr->parent->parent);
		}
	}
}

void RBTree::case_five(node *ptr){
	rotate_right(ptr->parent);
	case_six(ptr->parent);
}

void RBTree::case_three(node *ptr){
	if(ptr->parent){
		ptr->parent->isRed = false;
		if(ptr->parent->parent){
			ptr->parent->parent->isRed = true;
			rotate_right(ptr->parent->parent);
		}
	}
}

void RBTree::case_two(node*ptr){
	rotate_left(ptr->parent);
	case_three(ptr->left); //??
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
		if(ptr == root) root = ptr->right;
		node *r = ptr->right;
		if(r == nullptr) return;
		node *p = ptr->parent;
		if(p != nullptr){		
			if(ptr == p->right) p->right = r; 
			else p->left = r;
		}
		r->parent = p;
		ptr->right = r->left; 
		if(r->left != nullptr) r->left->parent = ptr;
		r->left = ptr;
		ptr->parent = r;
		//std::cout<<root->key<< "is new root"<<std::endl;
	}
}

void RBTree::rotate_right(node *ptr){
	if(ptr !=nullptr){
		if(ptr == root) root = ptr->left;
		node *l =ptr->left;
		if( l == nullptr) return;
		node *p =ptr->parent;
		if(p != nullptr){
			if(ptr ==p->right) p->right = l;
			else p->left = l;
		}
		l->parent = p;	
		ptr->left = l->right;
		if(l->right !=nullptr) l->right->parent = ptr;
		l->right = ptr;
		ptr->parent = l;
		//std::cout<<root->key<< "is new root"<<std::endl;
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

