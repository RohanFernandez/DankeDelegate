#include <iostream>
#include "src/delegate.h"

class doClass
{
public:
	int printThis1(int)
	{
		std::cout << "Printing 111 ... member func\n";
		return 0;
	}

	int printThis2(int) const
	{
		std::cout << "Printing 222 ... const member func\n";
		return 0;
	}

	static int printThis3(int)
	{
		std::cout << "Printing 333 ... static member func\n";
		return 0;
	}
};

int printThis4(int)
{
	std::cout << "Printing 444 ... global func\n";
	return 0;
}

void executeDelegate(ns_fretBuzz::Delegate<int(int)> a_Delegate)
{
	a_Delegate.Invoke(5);
}

int main()
{
	///testing fuzzy delegates
	doClass testDoClass;
	ns_fretBuzz::Delegate<int(int)> fuzzDele;
	fuzzDele.Add<doClass, &doClass::printThis1>(&testDoClass);
	fuzzDele.Add<doClass, &doClass::printThis2>(&testDoClass);
	fuzzDele.Add<&doClass::printThis3>();
	fuzzDele.Add <&printThis4>();

	executeDelegate(fuzzDele);

	system("pause");

	fuzzDele.Remove<&printThis4>();
	executeDelegate(fuzzDele);

	system("pause");

	fuzzDele.Remove<&doClass::printThis3>();
	executeDelegate(fuzzDele);

	system("pause");

	fuzzDele.Remove<doClass, &doClass::printThis2>(&testDoClass);
	executeDelegate(fuzzDele);

	system("pause");

	fuzzDele.Remove<doClass, &doClass::printThis1>(&testDoClass);
	executeDelegate(fuzzDele);

	system("pause");

	executeDelegate(fuzzDele);
	system("pause");

	return 0;
}