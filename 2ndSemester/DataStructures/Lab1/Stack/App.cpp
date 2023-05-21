#include "Stack.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>

using namespace std;

int main() {
    cout << "Start tests" << endl;
	testAll();
	testAllExtended();
	cout << "End tests" << endl;
}