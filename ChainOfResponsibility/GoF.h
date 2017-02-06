#pragma once

namespace ChainOfResponsibilityPattern::GoF
{
	class HelpHandler {
	public:
		HelpHandler(HelpHandler* s) : _successor(s) { }
		virtual void HandleHelp();
	private:
		HelpHandler* _successor;
	};

	void HelpHandler::HandleHelp() {
		if (_successor) {
			_successor->HandleHelp();
		}
	}

	enum RequestType
	{
		Help,
		Print,
		Preview
	};

	class Request {
	public:
		RequestType GetKind() { return Help; }
	};

	class HelpRequest : public Request {};

	class PrintRequest : public Request {};

	class Handler
	{
	public:

		void HandleHelp(HelpRequest* theRequest) {}

		void HandlePrint(PrintRequest* theRequest) {}

		void HandleRequest(Request* theRequest) {
			switch (theRequest->GetKind()) {
			case Help:
				// cast argument to appropriate type 
				HandleHelp((HelpRequest*)theRequest);
				break;
			case Print:
				HandlePrint((PrintRequest*)theRequest);
				// ... 
				break;
			default:
				// ... 
				break;
			}
		}
	};

	class ExtendedHandler : public Handler {
	public:
		virtual void HandleRequest(Request* theRequest);
		// ... 
	};

	void ExtendedHandler::HandleRequest(Request*theRequest) {
		switch (theRequest->GetKind()) {
		case Preview:
			// handle the Preview request 
			break;
		default:
			// let Handler handle other requests 
			Handler::HandleRequest(theRequest);
		}
	}
}
