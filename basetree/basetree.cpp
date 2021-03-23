#include <iostream>
#include "basetree.h"
#include "treeofsearch.h"
#include "randomtree.h"
int main()
{
	int arr[14] = {5,7,8,-85,5,58,4,32,1,8,225,1338,1337,665};
	searchTree<int> testTree(arr,14);
	testTree.print();
	testTree.DelNode(arr[10]);
	std::cout << "Test delete node: " << arr[10]<<std::endl;
	testTree.print();
	bool test = testTree.FindNode(arr[0]);
	std::cout << "Test find node:"<<arr[0]<<':';
	if (test)
		std::cout << "true";
	else
		std::cout << "false";
	int height = testTree.Height();
	std::cout << std::endl << "Height = " << height<<std::endl; 
	searchTree<int> testTree1;
	testTree1 = testTree;
	std::cout << "Test operator=" << std::endl;
	testTree1.print();
	randomTree<int> testingTree(arr, 14);
	testingTree.print();
	int a = testingTree.FindMax();
	std::cout<<"max:" << a;
	int b = testingTree.FindMin();
	std::cout<<std::endl << "min:" << b;
	testingTree.DelNode(arr[12]);
	std::cout << std::endl << "test delete node:" << arr[12]<< std::endl;
	testingTree.print();
}

