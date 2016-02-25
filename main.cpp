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


	int iterations = 5;


	for (int i = 0; i<iterations; i++) {
		mac->Record();
	}

	mac->WriteFile("auto.csv");
	mac->Reset();

	mac->ReadFile("auto.csv");
	while (!mac->IsFinished())
	{
		mac->PlayBack();
	}

	cout << "plz work" << endl;

	mac->Reset();
	Command* recCom = mac->NewRecordFileCommand("auto2.csv");
	recCom->Initialize();
	for (int i = 0; i < 30; i ++) recCom->Execute();
	recCom->End();

	return 0;
}
