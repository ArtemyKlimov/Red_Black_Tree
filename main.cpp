#include <iostream>
#include "rbt.hpp"
#include <fstream>

int main(){
	RBTree mytree;
	mytree.insert(12);
	mytree.insert(15);
	mytree.insert(18);
	mytree.insert(8);
	mytree.insert(14);
	mytree.show();

std::cout<<std::endl;
return 0;
}
