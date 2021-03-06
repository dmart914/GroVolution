/* GROVOLUTION - relay-test-1.cpp
 * A testing program for the Relay class.
 *
 * Author: Dave Martinez
 * Created: 7/21/15
 */

#include <cstdlib>
#include <iostream>
#include <string>

#include "../RS-232/rs232.h"
#include "../headers/comms.h"
#include "../headers/relaycpp.h"

int main(int argc, char** argv) {
	std::cout << "RELAY TEST 1\n\n";

	std::cout << "01 - Initializing three Relay objects.\n";

	Relay* firstRelay = new Relay();
	Relay* secondRelay = new Relay('A', 1);
	Relay* thirdRelay = new Relay('A', 1, true);

	std::cout << "firstRelay addr.: " << firstRelay << "\n";
	std::cout << "secondRelay addr.: " << secondRelay << "\n";
	std::cout << "thirdRelay addr.: " << thirdRelay << "\n\n";

	std::cout << "Attempting to get uninitialized variables\n";

	try {
		firstRelay->getLabel();
		std::cout << "TEST FAILED: No exception thrown for label.\n";
	} catch (int e) {
		std::cout << "TEST PASSED: Exception thrown for uninit. var.\n";
	}

	try {
		firstRelay->getNumber();
		std::cout << "TEST FAILED: No exception thrown for number.\n";
	} catch (int e) {
		std::cout << "TEST PASSED: Exception thrown for uninit. var.\n";
	}

	try {
		firstRelay->getStatus();
		std::cout << "TEST FAILED: No exception thrown for status.\n";
	} catch (int e) {
		std::cout << "TEST PASSED: Exception thrown for uninit. var.\n";
	}

	try {
		firstRelay->getConnection();
		std::cout << "TEST FAILED: No exception thrown for connection.\n";
	} catch (int e) {
		std::cout << "TEST PASSED: Exception thrown for uninit. cx.\n";
	}

	std::cout << "\n02 - Testing get and set functions\n";

	firstRelay->setLabel('A');
	if (firstRelay->getLabel() != 'A') {
		std::cout << "TEST FAILED: Relay label set or get method.\n";
	} else {
		std::cout << "TEST PASSED: Relay label changed.\n";
	}

	firstRelay->setNumber(2);
	if (firstRelay->getNumber() != 2) {
		std::cout << "TEST FAILED: Relay number set or get method.\n";
	} else {
		std::cout << "TEST PASSED: Relay number changed.\n";
	}

	firstRelay->setStatus(false);
	if (firstRelay->getStatus() != false) {
		std::cout << "TEST FAILED: Relay status set or get method.\n";
	} else {
		std::cout << "TEST PASSED: Relay status changed.\n";
	}

	RS232Connection aConnection;
	firstRelay->setConnection(&aConnection);
	if (firstRelay->getConnection() != &aConnection) {
		std::cout<< "TEST FAILED: Connection addr. do not match.\n";
	} else {
		std::cout << "TEST PASSED: Connection addr. changed. \n";
	}

	std::cout << "\n03 - Testing on/off methods\n";
	std::cout << "Testing connection failure...\n";
	Relay* fourthRelay = new Relay('L', 1, false);
	try {
		fourthRelay->on();
		std::cout << "TEST FAILED: Connection did not throw exception.\n";
	} catch (int e) {
		std::cout << "TEST PASSED: Connection threw exception.\n";
	}

	std::cout << "\nNote: You'll need to check the PLC for physical results.\n\n";
	fourthRelay->setConnection(&aConnection);

	std::cout << "Testing on()...\n";
	fourthRelay->on();
	std::cout << "Did " << fourthRelay->getLabel() << fourthRelay->getNumber()
	<< " turn on?\n";
	std::cout << "Press enter to continue...";
	std::cin.ignore();

	std::cout << "\nTesting off()...\n";
	fourthRelay->off();
	std::cout << "Did " << fourthRelay->getLabel() << fourthRelay->getNumber()
	<< " turn off?\n";
	std::cout << "Press enter to continue...";
	std::cin.ignore();

	std::cout << "\nTesting toggle()...\n";
	fourthRelay->toggle();
	std::cout << "Did " << fourthRelay->getLabel() << fourthRelay->getNumber()
	<< " toggle?\n";
	std::cout << "Press enter to continue...";
	std::cin.ignore();

	std::cout << "\n\n04 - Reporting\n";
	std::cout << "Testing report()...\n";
	firstRelay->report();
	secondRelay->report();
	thirdRelay->report();
	fourthRelay->report();

	std::cout << "\n";




	return 0;
}
