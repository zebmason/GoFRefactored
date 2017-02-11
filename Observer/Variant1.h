#pragma once

#include <vector>

namespace ObserverPattern::Variant1
{
	class SubjectData {
	public:
		virtual ~SubjectData() {}
	};

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

		SubjectData* Data() { return _data; }
	protected:
		Subject(SubjectData* data) : _data(data) {}
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

	class ClockTimerData : public SubjectData {
	public:
		ClockTimerData() {}
		virtual int GetHour() { return 0; }
		virtual int GetMinute() { return 0; }
		virtual int GetSecond() { return 0; }
	};

	class ClockTimer : public Subject {
	public:
		ClockTimer() : Subject(new ClockTimerData()) {}
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
		int hour = dynamic_cast<ClockTimerData*>(_subject->Data())->GetHour();
		int minute = dynamic_cast<ClockTimerData*>(_subject->Data())->GetMinute();
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
