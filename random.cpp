#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>

int main(){

	int max = 0;
	std::vector<int> vec;
	std::cout<<"How many numbers we will sort?"<<std::endl;
	std::cin>>max;

	for(int i = 0;i < max; ++i)
		vec.push_back(i);
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(vec.begin(), vec.end(), std::default_random_engine(seed));
	
	std::ofstream fout("list.txt");
	for(auto it: vec){
		fout<<it<<" ";
	}
	fout.close();


return 0;
}
