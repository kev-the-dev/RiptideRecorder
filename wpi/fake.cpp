#ifndef FAKE_CPP
#define FAKE_CPP

#include <iostream>

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

	}
};
class Servo {
public:
	float Get() {
		return 0.8;
	}
	void Set(float x) {

	}
};
class Solenoid {
public:

	bool Get() {
		return true;
	}
	void Set(bool x) {

	}
};
class SpeedController {
public:
	float Get() {
		return 0.56;
	}
	void Set(float x) {

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

private:
	bool running;
};
#endif
