#pragma once

#include <vector>

namespace CommandPattern::GoF
{
	class Command {
	public:
		virtual ~Command() {};
		virtual void Execute() = 0;
	protected:
		Command() {};
	};

	class Document;

	class Application {
	public:
		void Add(Document*) {}
	};

	class OpenCommand : public Command {
	public:
		OpenCommand(Application*);
		virtual void Execute();
	protected:
		virtual const char* AskUser() { return nullptr; };
	private:
		Application* _application;
		char* _response;
	};

	OpenCommand::OpenCommand(Application* a) {
		_application = a;
	}

	class Document {
	public:
		Document(const char* name) {}
		void Open() {}
		void Paste() {}
	};

	void OpenCommand::Execute() {
		const char* name = AskUser();
		if (name != 0) {
			Document* document = new Document(name);
			_application->Add(document);
			document->Open();
		}
	}

	class PasteCommand : public Command {
	public:
		PasteCommand(Document*);
		virtual void Execute();
	private:
		Document* _document;
	};

	PasteCommand::PasteCommand(Document* doc) { _document = doc; }
	
	void PasteCommand::Execute() { _document->Paste(); }

	class Receiver;
	class SimpleCommand : public Command {
	public:
		typedef void (Receiver::* Action)();
		SimpleCommand(Receiver* r, Action a) :
			_receiver(r), _action(a) { }
		virtual void Execute();
	private:
		Action _action;
		Receiver* _receiver;
	};

	void SimpleCommand::Execute() { (_receiver->*_action)(); }

	class MacroCommand : public Command {
	public:
		MacroCommand() {};
		virtual ~MacroCommand() {};
		virtual void Add(Command*);
		virtual void Remove(Command*);
		virtual void Execute();
	private:
		std::vector<Command*>* _cmds;
	};

	void MacroCommand::Execute() {
		auto i(_cmds->begin());
		for (; i != _cmds->end(); ++i) {
			(*i)->Execute();
		}
	}

	void MacroCommand::Add(Command* c) { _cmds->push_back(c); }
	void MacroCommand::Remove(Command* c) { 
		//_cmds->erase(c); 
	}
}
