#include "tree.h"
#define _treeSize 4
#define _maxValue 1000000
int main()
{
	try{
		RBTree tree;
		set<int> s;
		int i, k, p;
		srand(time(nullptr));
		for(i = 0; i < _treeSize; i++){
			k = rand() % _maxValue;
			tree.insert(k);
			s.insert(k);
		}
		tree.print();
		tree.printDepth(); // Все же выводится верно, т.к. у дерева есть еще null-листья,
						// которые не отображаются при выводе за ненадобностью
		p = rand() % _maxValue;
		
		auto t1 = chrono::high_resolution_clock::now();
		tree.searchTree(p);
		auto t2 = chrono::high_resolution_clock::now();

		auto ns = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);

		std::cout << "Execution time for my own implementation is " <<  ns.count() << "ns\n";

		t1 = chrono::high_resolution_clock::now();
		auto I = s.find(p);
		t2 = chrono::high_resolution_clock::now();

		ns = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);

		std::cout << "Execution time for STL implementation is " <<  ns.count() << "ns\n";
		
		if(I == s.end()) cout << "The value hasn't been found" << endl;
			else cout << "The value " << p << " has been found" << endl;
		
	}
	catch (bad_alloc)
	{
		throw myException("Memory allocation error\n", EC_MEMORY);
	}
	catch (runtime_error)
	{
		throw myException("Runtime error\n", EC_MEMORY);
	}
	catch (myException e)
	{
		cout << e.getMessage();
		return e.getCode();
	}
	return 0;
}