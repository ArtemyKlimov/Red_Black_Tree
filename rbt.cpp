#ifndef RBT_CPP
#define RBT_CPP
#include <iostream>
#include "rbt.hpp"
#include <fstream>

template<typename T>
RBTree<T>::RBTree(){
	root = nullptr;
}
template<typename T>
node<T>* RBTree<T>::createLeaf(T _key, node<T>*_parent){
	node<T> *n = new node<T>();
	n->key = _key;
	n->left = nullptr;
	n->right = nullptr;
	n->parent=_parent;
	return n;	
}
template<typename T>
void RBTree<T>::insert(T _key){
	node<T>* n = insert_private(_key, root);
	validate(n);
	//tell_truth(n);
}

//this method was added just to be sure, that the node was placed right
template<typename T>
void RBTree<T>::tell_truth(node<T>* n){
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
	
template<typename T>
node<T>* RBTree<T>::insert_private(T _key, node<T>* ptr){
	node<T>* n = nullptr;
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
template<typename T>
void RBTree<T>::validate(node<T> *ptr){
	if(ptr == root) {
		root->isRed = false;
		return;
	}
	node<T> *d = ptr->parent->parent;
	if(d ==nullptr) return; //
	if((ptr->parent == d->left)&&(ptr->parent->isRed)){
		if(d->right)
			if(d->right->isRed){
				case_one(ptr);
				return;
			}
		if((ptr == ptr->parent->right)&&(d->right == nullptr || !d->right->isRed)){
			case_two(ptr);
			return;
		}
		if((ptr == ptr->parent->left)&&(d->right ==nullptr || !d->right->isRed)){
			case_three(ptr);
			return;
		}
	}
	else if((ptr->parent == d->right) &&(ptr->parent->isRed)){
		if((ptr == ptr->parent->right)&&(d->left == nullptr || !d->left->isRed)){
			case_six(ptr);
			return;
		}
		if (d->left)
			if(d->left->isRed ){
				case_four(ptr);
				return;
			}
		if((ptr == ptr->parent->left)&&(d->left == nullptr || !d->left->isRed)){
			case_five(ptr);
			return;
		}
	}
}
template<typename T>
void RBTree<T>::case_four(node<T> *ptr){
	node<T> *d = ptr->parent->parent;
	d->right->isRed = false;
	d->left->isRed = false;
	d->isRed = true;
	validate(d);
}

template<typename T>
void RBTree<T>::case_six(node<T> *ptr){
	if(ptr->parent != nullptr){
		ptr->parent->isRed =false;
		if(ptr->parent->parent != nullptr){
			ptr->parent->parent->isRed = true;
			rotate_left(ptr->parent->parent);
		}
	}
}

template<typename T>
void RBTree<T>::case_five(node<T> *ptr){
	rotate_right(ptr->parent);
	case_six(ptr->parent);
}

template<typename T>
void RBTree<T>::case_three(node<T> *ptr){
	if(ptr->parent){
		ptr->parent->isRed = false;
		if(ptr->parent->parent){
			ptr->parent->parent->isRed = true;
			rotate_right(ptr->parent->parent);
		}
	}
}

template<typename T>
void RBTree<T>::case_two(node<T> *ptr){
	rotate_left(ptr->parent);
	case_three(ptr->left); 
}

template<typename T>
void RBTree<T>::case_one(node<T> *ptr){
	node<T> *d = ptr->parent->parent;
	d->left->isRed = false;
	d->right->isRed = false;
	d->isRed = true;
	validate(d);
}

template <typename T>
void RBTree<T>::show() const{
	show_private(root);
} 
template <typename T>
void RBTree<T>::show_private(node<T> *ptr) const{
	if(ptr == nullptr) return;
	if(ptr->left != nullptr){
		show_private(ptr->left);
	}
	std::cout<<ptr->key<<" ";
	if(ptr->right !=nullptr){
		show_private(ptr->right);
	}
}

template <typename T>
void RBTree<T>::rotate_left(node<T> *ptr){
	if(ptr !=nullptr){
		if(ptr == root) root = ptr->right;
		node<T> *r = ptr->right;
		if(r == nullptr) return;
		node<T> *p = ptr->parent;
		if(p != nullptr){		
			if(ptr == p->right) p->right = r; 
			else p->left = r;
		}
		r->parent = p;
		ptr->right = r->left; 
		if(r->left != nullptr) r->left->parent = ptr;
		r->left = ptr;
		ptr->parent = r;
	}
}
template <typename T>
void RBTree<T>::rotate_right(node<T> *ptr){
	if(ptr !=nullptr){
		if(ptr == root) root = ptr->left;
		node<T> *l =ptr->left;
		if( l == nullptr) return;
		node<T> *p =ptr->parent;
		if(p != nullptr){
			if(ptr ==p->right) p->right = l;
			else p->left = l;
		}
		l->parent = p;	
		ptr->left = l->right;
		if(l->right !=nullptr) l->right->parent = ptr;
		l->right = ptr;
		ptr->parent = l;
	}
}

template<typename T>
bool RBTree<T>::isExist(T _key) const{
	return (isExist_private(_key, root));
}

template<typename T>
bool RBTree<T>::isExist_private(T _key, node<T>* ptr) const{
	if(ptr !=nullptr){
		if(ptr->key == _key) return true;
		if(ptr->key > _key){
			if(ptr->left != nullptr){
				if(isExist_private(_key, ptr->left)) return true;
			}
			else return false;
		}
		if(ptr->key < _key){
			if(ptr->right != nullptr){
				if(isExist_private(_key,ptr->right)) return true;
			}
			else return false;
		}
	}
	return false;
}

template <typename T>
RBTree<T>::~RBTree(){
	removeptr(root);
}

template <typename T>
void RBTree<T>::removeptr(node<T>* Ptr){
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


template<typename T>
void RBTree<T>::printToFile_private(std::ofstream& f, node<T>* ptr)const{
	if(ptr != nullptr){
		if(ptr->left !=nullptr){
			printToFile_private(f, ptr->left);
		}
		f<<ptr->key<<" ";	
		if(ptr->right !=nullptr){
			printToFile_private(f, ptr->right);
		}
	}
}

template <typename T>
void RBTree<T>::printToFile(std::ofstream& f) const{
	printToFile_private(f, root);
}



#endif
