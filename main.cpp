#include <iostream>
#include "rbt.hpp"
#include <fstream>

int main(int argc, char **argv){
	RBTree<int> mytree;
	mytree.insert(12);
	mytree.insert(15);
	mytree.insert(18);
	mytree.insert(8);
	mytree.insert(14);
	mytree.insert(21);
	mytree.insert(28);
	mytree.insert(31);
	mytree.insert(2);
	mytree.insert(6);
	mytree.insert(7);
	mytree.insert(32);
	mytree.insert(105);
	mytree.insert(132);
	mytree.insert(199);
	mytree.insert(6);
	if((argc == 2)||(argc ==3)){

	std::ifstream fin(argv[1]);
	int number = 0;
	while(fin>> number){
		mytree.insert(number);
	}
	fin.close();
	if(argc == 3){
		std::ofstream fout(argv[2]);
		mytree.printToFile(fout);
		fout.close();
	}
	fin.close();
	}
	if(mytree.isExist(500)) std::cout<<"500 exists"<<std::endl;
	if(mytree.isExist(200)) std::cout<<"200 exists"<<std::endl;	
	mytree.show();



std::cout<<std::endl;
return 0;
}
