#include <iostream>
#include "RiptideRecorder/RiptideRecorder.h"
#include "TestDevice.h"
using namespace std;
int main() {
	Recorder* rec = Recorder::GetInstance();

	//One of each device
	TestDevice* dev = new TestDevice("dev");
	Relay* rel = new Relay();
	SpeedController* ctrl = new SpeedController();
	Servo* serv = new Servo();
	DoubleSolenoid* ds = new DoubleSolenoid();
	Solenoid* sol = new Solenoid();

	//Add all devices to recorder
	rec->AddDevice("Relay",rel);
	rec->AddDevice("Speed Controller",ctrl);
	rec->AddDevice("Servo",serv);
	rec->AddDevice("Double Solenoid",ds);
	rec->AddDevice("Solenoid",sol);
	rec->AddDevice(dev);

	//Creates macro
	Macro* mac = rec -> macro();


	for (int i = 0; i<3000; i++) {
		mac->Record();
	}

	mac->WriteFile("saves/auto.csv");
	mac->Reset();

	mac->ReadFile("saves/auto.csv");
	while (!mac->IsFinished()) mac->PlayBack();

	std::cout << "plz work" << std::endl;

}
