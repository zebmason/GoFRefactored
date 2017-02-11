#pragma once

#include <vector>

namespace ObserverPattern::Variant1
{
	class SubjectData {};

	class Observer {
	public:
		virtual ~Observer() {}
		virtual void Update(SubjectData* theChangedSubject) = 0;
	protected:
		Observer() {}
	};

	class Subject {
	public:
		virtual ~Subject() {}
		virtual void Attach(Observer*);
		virtual void Detach(Observer*);
		virtual void Notify();
	protected:
		Subject() {}
	private:
		SubjectData* _data;
		std::vector<Observer*> _observers;
	};

	void Subject::Attach(Observer* o) { _observers.emplace_back(o); }

	void Subject::Detach(Observer* o) { }

	void Subject::Notify() {
		for (auto ob : _observers)
		{
			ob->Update(_data);
		}
	}

	class ClockTimer : public Subject {
	public:
		ClockTimer() {}
		virtual int GetHour() { return 0; }
		virtual int GetMinute() { return 0; }
		virtual int GetSecond() { return 0; }
		void Tick();
	};

	void ClockTimer::Tick() {
		// update internal time-keeping state 
		// ... 
		Notify();
	}

	class Widget {};

	class DigitalClock : public Widget, public Observer {
	public:
		DigitalClock(ClockTimer*);
		virtual ~DigitalClock();
		virtual void Update(Subject*);
		// overrides Observer operation 
		virtual void Draw();
		// overrides Widget operation; 
		// defines how to draw the digital clock 
	private:
		ClockTimer* _subject;
	};

	DigitalClock::DigitalClock(ClockTimer* s) {
		_subject = s;
		_subject->Attach(this);
	}

	DigitalClock::~DigitalClock() {
		_subject->Detach(this);
	}

	void DigitalClock::Update(Subject* theChangedSubject) {
		if (theChangedSubject == _subject) {
			Draw();
		}
	}

	void DigitalClock::Draw() {
		// get the new values from the subject  
		int hour = _subject->GetHour();
		int minute = _subject->GetMinute();
		// etc.  
		// draw the digital clock 
	}

	class AnalogClock : public Widget, public Observer {
	public:
		AnalogClock(ClockTimer*) {}
		virtual void Update(Subject*) {}
		virtual void Draw() {}
		// ... 
	};

}
