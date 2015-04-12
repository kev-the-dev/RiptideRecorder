#include <iostream>
#include "RiptideRecorder/RiptideRecorder.h"
#include "TestDevice.h"

using namespace std;
int main(int argc, char* argv[]) {

	cout << argc << endl;
	for (int h = 0; h<argc; h++)
		cout << argv[h] << endl;

	cout << endl;

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
	cout << dev->GetName() << endl;


	Macro* mac = rec -> macro();

	int iterations;
	//if (argc > 1) iterations = std::atoi(argv[1]);
	//else
	iterations = 8;


	for (int i = 0; i<iterations; i++) {
		mac->Record();
	}

	string path (argv[0]);
	path = path.substr(0, path.size() - 4);

	mac->WriteFile(path + "/../saves/auto.csv");
	mac->Reset();

	mac->ReadFile(path +  "/../saves/auto.csv");
	while (!mac->IsFinished()) mac->PlayBack();

	cout << "plz work" << endl;

	return 0;
}
