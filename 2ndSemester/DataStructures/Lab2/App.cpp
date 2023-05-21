#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"

int main() {
    std::cout << "Started tests!" << std::endl;
    testOperation();
	testAll();
	testAllExtended();
	std::cout << "Finished LP Tests!" << std::endl;
	system("pause");
}
