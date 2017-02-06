#pragma once

namespace ChainOfResponsibilityPattern::GoF2
{
	typedef int Topic;
	const Topic NO_HELP_TOPIC = -1;

	class HelpHandler {
	public:
		HelpHandler(HelpHandler* = 0, Topic = NO_HELP_TOPIC);
		virtual bool HasHelp();
		virtual void SetHandler(HelpHandler*, Topic) {}
		virtual void HandleHelp();
	private:
		HelpHandler* _successor;
		Topic _topic;
	};

	HelpHandler::HelpHandler(
		HelpHandler* h, Topic t
	) : _successor(h), _topic(t) { }

	bool HelpHandler::HasHelp() {
		return _topic != NO_HELP_TOPIC;
	}

	void HelpHandler::HandleHelp() {
		if (_successor != 0) {
			_successor->HandleHelp();
		}
	}

	class Widget : public HelpHandler {
	protected:
		Widget(Widget* parent, Topic t = NO_HELP_TOPIC);
	private:
		Widget* _parent;
	};

	Widget::Widget(Widget* w, Topic t) : HelpHandler(w, t) {
		_parent = w;
	}

	class Button : public Widget {
	public:
		Button(Widget* d, Topic t = NO_HELP_TOPIC);
		virtual void HandleHelp();
		// Widget operations that Button overrides... 
	};

	Button::Button(Widget* h, Topic t) : Widget(h, t) { }

	void Button::HandleHelp() {
		if (HasHelp()) {
			// offer help on the button 
		}
		else {
			HelpHandler::HandleHelp();
		}
	}

	class Dialog : public Widget {
	public:
		Dialog(HelpHandler* h, Topic t = NO_HELP_TOPIC);
		virtual void HandleHelp();
		// Widget operations that Dialog overrides... 
		// ... 
	};

	Dialog::Dialog(HelpHandler* h, Topic t) : Widget(0) {
		SetHandler(h, t);
	}

	void Dialog::HandleHelp() {
		if (HasHelp()) {
			// offer help on the dialog 
		}
		else {
			HelpHandler::HandleHelp();
		}
	}

	class Application : public HelpHandler {
	public:
		Application(Topic t) : HelpHandler(0, t) { }
		virtual void HandleHelp();
		// application-specific operations... 
	};

	void Application::HandleHelp() {
		// show a list of help topics 
	}
}
