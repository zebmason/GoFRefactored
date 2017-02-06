#pragma once

namespace MementoPattern::GoF2
{
	typedef double Point;

	class Graphic {
	public:
		void Move(Point delta) {}
	};

	class ConstraintSolverMemento;

	// base class for graphical objects in the graphical editor  
	class MoveCommand {
	public:
		MoveCommand(Graphic* target, const Point& delta) : _delta(delta), _target(target) {}
		void Execute();
		void Unexecute();
	private:
		ConstraintSolverMemento* _state;
		Point _delta;
		Graphic* _target;
	};

	class ConstraintSolver {
	public:
		static ConstraintSolver* Instance() { return nullptr; }
		void Solve() {}
		void AddConstraint(
			Graphic* startConnection, Graphic* endConnection
		) {}
		void RemoveConstraint(
			Graphic* startConnection, Graphic* endConnection
		) {}
		ConstraintSolverMemento* CreateMemento() { return nullptr; }
		void SetMemento(ConstraintSolverMemento*) {}
	private:
		// nontrivial state and operations for enforcing 
		// connectivity semantics    };  
		class ConstraintSolverMemento {
		public:
			virtual ~ConstraintSolverMemento() {}
		private:
			friend class ConstraintSolver;
			ConstraintSolverMemento();
			// private constraint solver state 
		};
	};

	void MoveCommand::Execute() {
		ConstraintSolver* solver = ConstraintSolver::Instance();
		_state = solver->CreateMemento();
		// create a memento 
		_target->Move(_delta);
		solver->Solve();
	}

	void MoveCommand::Unexecute() {
		ConstraintSolver* solver = ConstraintSolver::Instance();
		_target->Move(-_delta);
		solver->SetMemento(_state);
		// restore solver state 
		solver->Solve();
	}
}
