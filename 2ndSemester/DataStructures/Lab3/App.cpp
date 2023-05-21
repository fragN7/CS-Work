#include <iostream>
#include "MultiMap.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "MultiMapIterator.h"

using namespace std;


int main() {

    cout << "Start short tests" << endl;
	testAll();
    cout << "Ended short tests" << endl;

    cout << "Start" << endl;
    testAllExtended();
	cout << "End" << endl;
	system("pause");

}
