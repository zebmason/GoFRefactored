#pragma once

namespace MementoPattern::GoF
{
	class State {};

	class Memento;

	class Originator {
	public:
		Memento* CreateMemento() {}
		void SetMemento(const Memento*) {}
		// ... 
	private:
		State* _state;
		// internal data structures 
		// ... 
	};

	class Memento {
	public:
		// narrow public interface 
		virtual ~Memento() {}
	private:
		// private members accessible only to Originator 
		friend class Originator;
		Memento();
		void SetState(State*) {}
		State* GetState() { return _state; }
		// ... 
	private:
		State* _state;
		// ... 
	};
}
