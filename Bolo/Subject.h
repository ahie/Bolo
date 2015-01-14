#pragma once

#include "Observer.h"
#include "Event.h"
#include <list>
#include <algorithm>

class Subject
{
public:
	Subject() {}
	virtual ~Subject() {}
	void addObserver(Observer* observer)
	{
		observers_.push_back(observer);
	}
	void removeObserver(Observer* observer)
	{
		observers_.erase(find(observers_.begin(), observers_.end(), observer));
	}
protected:
	void notify(Event event)
	{
		for (auto observer : observers_)
			observer->onNotify(this,event);
	}
private:
	std::list<Observer*> observers_;
};
