#ifndef FAKE_CPP
#define FAKE_CPP

#include <iostream>

using namespace std;

class DoubleSolenoid {
public:
	enum Value {
		kForward,
		kReverse,
		kOff
	};
	Value Get() {
		return kOff;
	}
	void Set(Value x) {
		switch (x) {
			case kForward:
				cout << "Double Solenoid set to kForward" << endl;
				break;
			case kReverse:
				cout << "Double Solenoid set to kReverse" << endl;
				break;
			default:
				cout << "Double Solenoid set to kOff" << endl;
		}
	}
};
class Relay {
public:
	enum Value {
		kForward,
		kReverse,
		kOff,
		kOn
	};
	Value Get() {
		return kOn;
	}
	void Set(Value x) {
		switch (x) {
			case kOn:
				cout << "Relay set to kOn" << endl;
				break;
			case kForward:
				cout << "Relay set to kForward" << endl;
				break;
			case kReverse:
				cout << "Relay set to kReverse" << endl;
				break;
			default:
				cout << "Relay set to kOff" << endl;
		}
	}
};
class Subsystem
{

};
class Servo {
public:
	float Get() {
		return 0.8;
	}
	void Set(float x) {
		cout << "Setting a Servo to " << x << endl;
	}
};
class Solenoid {
public:

	bool Get() {
		return true;
	}
	void Set(bool x) {
		cout << "Setting a solenoid to " << x << endl;
	}
};
class SpeedController {
public:
	float Get() {
		return 0.56;
	}
	void Set(float x) {
		cout << "Setting a speed controller to " << x << endl;
	}
};
class Command {
public:
	Command() {
		running = false;
	}
	bool IsRunning() {
		return running;
	}
	void Cancel() {
		running = false;
	}
	void Start() {
		running = true;
		Initialize();
		int i;
		for (i = 0; i<1000 || IsFinished(); i++) {
			Execute();
		}
		std::cout << "Ran for " << i << " iterations" << std::endl;
		End();
		running = false;
	}

protected:
	virtual void Initialize() = 0;
	virtual void Execute() = 0;
	virtual bool IsFinished() = 0;
	virtual void End() = 0;
	virtual void Interrupted() = 0;
	void Requires(Subsystem* s)
	{

	}
private:
	bool running;
};
#endif
