
#pragma once

class Decorator{
public:
	Decorator(Decorator* next, int para){
		component_ = next;
	}

	Decorator() : component_(0) {}

	void operate(){
		// do something...
		if (component_) { component_->operate(); }
	}

private:
	Decorator* component_;
};
