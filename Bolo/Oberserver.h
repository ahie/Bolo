#pragma once
#include "Event.h"

class Subject;

class Observer
{
public:
	Observer() {}
	virtual ~Observer() {}
	virtual void onNotify(Subject* subject, Event ev) = 0;
};