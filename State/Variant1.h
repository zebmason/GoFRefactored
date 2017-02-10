#pragma once

namespace StatePattern::Variant1
{
	class TCPOctetStream;

	class TCPConnection {
	public:
		TCPConnection() {}
		void ProcessOctet(TCPOctetStream*) {}
	};

	class TCPState {
	public:
		enum State {
			None,
			Closed,
			Listen,
			Established
		};
		virtual void Transmit(TCPConnection*, TCPOctetStream*);
		virtual TCPState::State ActiveOpen(TCPConnection*);
		virtual TCPState::State PassiveOpen(TCPConnection*);
		virtual TCPState::State Close(TCPConnection*);
		virtual TCPState::State Synchronize(TCPConnection*);
		virtual TCPState::State Acknowledge(TCPConnection*) {}
		virtual TCPState::State Send(TCPConnection*) {}
	protected:
		void ChangeState(TCPConnection*, TCPState*);
	};

	void TCPState::Transmit(TCPConnection*, TCPOctetStream*) { }
	TCPState::State TCPState::ActiveOpen(TCPConnection*) { return TCPState::State::None; }
	TCPState::State TCPState::PassiveOpen(TCPConnection*) { return TCPState::State::None; }
	TCPState::State TCPState::Close(TCPConnection*) { return TCPState::State::None; }
	TCPState::State TCPState::Synchronize(TCPConnection*) { return TCPState::State::None; }

	class TCPEstablished : public TCPState {
	public:
		static TCPState* Instance() { return nullptr; }

		virtual void Transmit(TCPConnection*, TCPOctetStream*);
		virtual TCPState::State Close(TCPConnection*);
	};

	TCPState::State TCPEstablished::Close(TCPConnection* t) {
		// send FIN, receive ACK of FIN 
		return TCPState::State::Listen;
	}

	void TCPEstablished::Transmit(TCPConnection* t, TCPOctetStream* o) {
		t->ProcessOctet(o);
	}

	class TCPListen : public TCPState {
	public:
		static TCPState* Instance() { return nullptr; }
		virtual TCPState::State Send(TCPConnection*);
		// ...  
	};

	TCPState::State TCPListen::Send(TCPConnection* t) {
		// send SYN, receive SYN, ACK, etc. 
		return TCPState::State::Established;
	}

	class TCPClosed : public TCPState {
	public:
		static TCPState* Instance() { return nullptr; }
		virtual TCPState::State ActiveOpen(TCPConnection*);
		virtual TCPState::State PassiveOpen(TCPConnection*);
		// ...     
	};

	TCPState::State TCPClosed::ActiveOpen(TCPConnection* t) {
		// send SYN, receive SYN, ACK, etc. 
		return TCPState::State::Established;
	}
	TCPState::State TCPClosed::PassiveOpen(TCPConnection* t) {
		return TCPState::State::Listen;
	}

	class TCPStateHolder {
		TCPState::State _state;
	public:
		TCPStateHolder();
		void ActiveOpen();
		void PassiveOpen();
		void Close();
		void Send() {}
		void Acknowledge();
		void Synchronize();
	private:
		TCPState* State()
		{
			switch (_state)
			{
			case TCPState::State::Closed:
				return TCPClosed::Instance();
				break;
			case TCPState::State::Established:
				return TCPEstablished::Instance();
				break;
			case TCPState::State::Listen:
				return TCPListen::Instance();
				break;
			}
			return nullptr;
		}
	private:
		TCPConnection* _connection;
		TCPState** states;
	};

	void TCPStateHolder::ActiveOpen() {
		_state = State()->ActiveOpen(_connection);
	}
	void TCPStateHolder::PassiveOpen() {
		_state = State()->PassiveOpen(_connection);
	}
	void TCPStateHolder::Close() {
		_state = State()->Close(_connection);
	}
	void TCPStateHolder::Acknowledge() {
		_state = State()->Acknowledge(_connection);
	}
	void TCPStateHolder::Synchronize() {
		_state = State()->Synchronize(_connection);
	}

	TCPStateHolder::TCPStateHolder() {
		_state = TCPState::State::Closed;
	}
}