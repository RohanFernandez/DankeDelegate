//Project created by RohanFernandez
//repository : https://github.com/RohanFernandez/DankeDelegate

#include <iostream>
#include "src/event_manager.h"

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

void executeDelegate(FretBuzz::Delegate<int(int)> a_Delegate, int a_iPrintNum)
{
	std::cout<<"\t\t"<<a_Delegate(a_iPrintNum)<<"\n";
}

int main()
{

	/************************************************************* DELEGATE EXAMPLE IMPLEMENTATION **************************************************************/

	std::cout << "************************************************************* DELEGATE EXAMPLE IMPLEMENTATION **************************************************************\n";



	///testing fuzzy delegates
	doClass testDoClass;
	doClass testDoClass1;

	//Create delegate of type <int(int)>
	FretBuzz::Delegate<int(int)> fuzzDele;			
	fuzzDele.Add<doClass, &doClass::printThis1>(&testDoClass);	//Add function of object doClass::printThis1
	fuzzDele.Add<doClass, &doClass::printThis2>(&testDoClass);	//Add function of object doClass::printThis2
	fuzzDele.Add<&doClass::printThis3>();						//Add static function
	fuzzDele.Add <&printThis4>();								//Add global function

	FretBuzz::Delegate<int(int)> fuzzDele1;
	fuzzDele1.Add<doClass, &doClass::printThis1>(&testDoClass1);	//Add function of object doClass::printThis1
	fuzzDele1.Add<doClass, &doClass::printThis2>(&testDoClass1);	//Add function of object doClass::printThis2
	fuzzDele1.Add<&doClass::printThis3>();							//Add static function
	fuzzDele1.Add <&printThis4>();									//Add global function


	// Combining 2 Delegates and executing by passing a parameter
	// Will call all stored functions inside both delegates with the passed arguement
	std::cout << "\n\n-------Combining 2 Delegates and executing by passing a parameter,\n-------Will call all stored functions inside both delegates with the passed arguement\n";
	executeDelegate(fuzzDele + fuzzDele1, 777);
	system("pause");

	// Will call all stored functions inside delegate 'fuzzDele' with the passed arguement
	std::cout << "\n\n-------Will call all stored functions inside delegate 'fuzzDele' with the passed arguement\n";
	executeDelegate(fuzzDele, 666);
	system("pause");

	// Removes the global function 'printThis4' from the delegate 'fuzzDele1' and then calls all the functions stored in the delegate 'fuzzDele1' with the passed arguement
	std::cout << "\n\n-------Removes the global function 'printThis4' from the delegate 'fuzzDele1' and then calls all the functions stored in the delegate 'fuzzDele1' with the passed arguement\n";
	fuzzDele1.Remove<&printThis4>();
	executeDelegate(fuzzDele1,667);
	system("pause");

	// Removes the static function 'doClass::printThis3' from the delegate 'fuzzDele' and then calls all the functions stored in the delegate 'fuzzDele; with the passed arguement
	std::cout << "\n\n-------Removes the static function 'doClass::printThis3' from the delegate 'fuzzDele' and then calls all the functions stored in the delegate 'fuzzDele; with the passed arguement\n";
	fuzzDele.Remove<&doClass::printThis3>();
	executeDelegate(fuzzDele, 668);
	system("pause");

	// Removes the function 'doClass::printThis2' from the delegate 'fuzzDele' and then calls all the functions stored in the delegate 'fuzzDele; with the passed arguement
	std::cout << "\n\n-------Removes the function 'doClass::printThis2' from the delegate 'fuzzDele' and then calls all the functions stored in the delegate 'fuzzDele; with the passed arguement\n";
	fuzzDele.Remove<doClass, &doClass::printThis2>(&testDoClass);
	executeDelegate(fuzzDele, 669);
	system("pause");

	// Removes the function 'doClass::printThis1' from the delegate 'fuzzDele' and then calls all the functions stored in the delegate 'fuzzDele; with the passed arguement
	std::cout << "\n\n-------Removes the function 'doClass::printThis1' from the delegate 'fuzzDele' and then calls all the functions stored in the delegate 'fuzzDele; with the passed arguement\n";
	fuzzDele.Remove<doClass, &doClass::printThis1>(&testDoClass);
	executeDelegate(fuzzDele, 669);
	system("pause");
	
	// Combining 2 Delegates and executing by passing a parameter
	// Will call all stored functions inside both delegates with the passed arguement
	std::cout << "\n\n-------Combining 2 Delegates and executing by passing a parameter \n-------Will call all stored functions inside both delegates with the passed arguement\n";
	executeDelegate(fuzzDele + fuzzDele1, 777);
	system("pause");

	// Removes doClass::printThis1 from the delegate fuzzDele1, then calls the delegate 'fuzzDele1'
	std::cout << "\n\n-------Removes doClass::printThis1 from the delegate fuzzDele1, then calls the delegate 'fuzzDele1'\n";
	fuzzDele1.Remove<doClass, &doClass::printThis1>(&testDoClass);
	executeDelegate(fuzzDele1, 999);
	system("pause");

	// Removes all functions stored in fuzzDele that are common with fuzzDele1, then calls the delegate 'fuzzDele'
	std::cout << "\n\n-------Removes all functions stored in fuzzDele that are common with fuzzDele1, then calls the delegate 'fuzzDele'\n";
	fuzzDele.Remove(fuzzDele1);
	executeDelegate(fuzzDele, 999);
	system("pause");



	







	/************************************************************* EVENT EXAMPLE IMPLEMENTATION **************************************************************/

	std::cout << "************************************************************* EVENT EXAMPLE IMPLEMENTATION **************************************************************\n";

	//Creates Event Manager
	FretBuzz::EventManager* l_pEventManager = FretBuzz::EventManager::Initialize();

	std::string l_strEventNameFuzzDele = "FuzzDeleEvent";
	std::string l_strEventNameFuzzDele1 = "FuzzDeleEvent1";

	//Subscribe to event 'FuzzDeleEvent', with the delegate 'fuzzDele'
	std::cout << "\n\n-------Subscribe to event 'FuzzDeleEvent', with the delegate 'fuzzDele'\n";
	l_pEventManager->Subscribe<int(int)>(l_strEventNameFuzzDele, fuzzDele);

	//Subscribe to event 'FuzzDeleEvent1', with the delegate 'fuzzDele1'
	std::cout << "\n\n-------Subscribe to event 'FuzzDeleEvent1', with the delegate 'fuzzDele1'\n";
	l_pEventManager->Subscribe<int(int)>(l_strEventNameFuzzDele1, fuzzDele1);

	system("pause");

	//Invoke event 'l_strEventNameFuzzDele' with the arguement 100000
	std::cout << "\n\n-------Invoke event 'l_strEventNameFuzzDele' with the arguement 100000\n";
	l_pEventManager->Invoke<int(int)>(l_strEventNameFuzzDele, 100000);
	system("pause");

	//Invoke event 'l_strEventNameFuzzDele' with the arguement 999999
	std::cout << "\n\n-------Invoke event 'l_strEventNameFuzzDele' with the arguement 999999\n";
	l_pEventManager->Invoke<int(int)>(l_strEventNameFuzzDele1, 999999);
	system("pause");

	//Unsubscribe from event 'FuzzDeleEvent', with the delegate 'fuzzDele'
	// Will remove the 'fuzzDele' from the registered callbacks of 'FuzzDeleEvent' event
	std::cout << "\n\n-------Unsubscribe from event 'FuzzDeleEvent', with the delegate 'fuzzDele' \n-------Will remove the 'fuzzDele' from the registered callbacks of 'FuzzDeleEvent' event\n";
	l_pEventManager->Unsubscribe<int(int)>(l_strEventNameFuzzDele, fuzzDele);

	//Unsubscribe from event 'FuzzDeleEvent1', with the delegate 'fuzzDele1'
	// Will remove the 'fuzzDele1' from the registered callbacks of 'FuzzDeleEvent1' event
	std::cout << "\n\n-------Unsubscribe from event 'FuzzDeleEvent1', with the delegate 'fuzzDele1' \n-------Will remove the 'fuzzDele1' from the registered callbacks of 'FuzzDeleEvent1' event\n";
	l_pEventManager->Unsubscribe<int(int)>(l_strEventNameFuzzDele1, fuzzDele1);

	//Destroys Event Manager
	std::cout << "\n\n-------Destroys Event Manager\n";
	l_pEventManager->destroy();
	system("pause");

	return 0;
}