//Project created by RohanFernandez
//repository : https://github.com/RohanFernandez/DankeDelegate

#include <iostream>
#include "src/delegate.h"

class doClass
{
public:
	int printThis1(int a_iPrintNum)
	{
		std::cout << "Printing 111 ... member func\n";
		return a_iPrintNum;
	}

	int printThis2(int a_iPrintNum) const
	{
		std::cout << "Printing 222 ... const member func\n";
		return a_iPrintNum;
	}

	static int printThis3(int a_iPrintNum)
	{
		std::cout << "Printing 333 ... static member func\n";
		return a_iPrintNum;
	}
};

int printThis4(int a_iPrintNum)
{
	std::cout << "Printing 444 ... global func\n";
	return a_iPrintNum;
}

void executeDelegate(ns_fretBuzz::Delegate<int(int)> a_Delegate, int a_iPrintNum)
{
	std::cout<<"\t\t"<<a_Delegate.Invoke(a_iPrintNum)<<"\n";
}

int main()
{
	///testing fuzzy delegates
	doClass testDoClass;
	doClass testDoClass1;
	ns_fretBuzz::Delegate<int(int)> fuzzDele;
	fuzzDele.Add<doClass, &doClass::printThis1>(&testDoClass);
	fuzzDele.Add<doClass, &doClass::printThis2>(&testDoClass);
	fuzzDele.Add<&doClass::printThis3>();
	fuzzDele.Add <&printThis4>();

	ns_fretBuzz::Delegate<int(int)> fuzzDele1;
	fuzzDele1.Add<doClass, &doClass::printThis1>(&testDoClass1);
	fuzzDele1.Add<doClass, &doClass::printThis2>(&testDoClass1);
	fuzzDele1.Add<&doClass::printThis3>();
	fuzzDele1.Add <&printThis4>();

	executeDelegate(fuzzDele, 666);

	system("pause");

	fuzzDele.Remove<&printThis4>();
	executeDelegate(fuzzDele,667);

	system("pause");

	fuzzDele.Remove<&doClass::printThis3>();
	executeDelegate(fuzzDele, 668);

	system("pause");

	fuzzDele.Remove<doClass, &doClass::printThis2>(&testDoClass);
	executeDelegate(fuzzDele, 669);

	system("pause");

	fuzzDele.Remove<doClass, &doClass::printThis1>(&testDoClass);
	executeDelegate(fuzzDele, 669);

	system("pause");

	fuzzDele.Add(fuzzDele1);
	executeDelegate(fuzzDele, 666);
	system("pause");

	fuzzDele1.Remove<doClass, &doClass::printThis1>(&testDoClass);
	executeDelegate(fuzzDele1, 999);
	system("pause");


	fuzzDele.Remove(fuzzDele1);
	executeDelegate(fuzzDele, 999);
	system("pause");

	return 0;
}