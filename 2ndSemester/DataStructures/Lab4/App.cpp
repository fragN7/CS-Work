#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"

using namespace std;

int main() {

    cout << "Start" << endl;
    testAll();
    cout << "End" << endl;

	testAllExtended();
	cout << "Test over" << endl;
	system("pause");
}
