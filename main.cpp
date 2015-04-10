#include <iostream>
#include "RiptideRecorder/RiptideRecorder.h"
#include "TestDevice.h"
using namespace std;
int main() {
	Recorder* rec = Recorder::GetInstance();

	TestDevice* dev = new TestDevice("dev");

	Relay* rel = new Relay();

	rec->AddDevice("relay",rel);
	rec->AddDevice(dev);

	Macro* mac = rec -> macro();

	mac->Record();
	mac->Record();
	mac->WriteFile("saves/new.csv");

	std::cout << "plz work" << std::endl;
	return 0;
}
