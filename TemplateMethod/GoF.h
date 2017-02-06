#pragma once

namespace TemplateMethodPattern::GoF
{
	class View
	{
	protected:
		void SetFocus() {}
		void ResetFocus() {}
		virtual void DoDisplay();
	public:
		void Display();
	};

	void View::Display() {
		SetFocus();
		DoDisplay();
		ResetFocus();
	}

	void View::DoDisplay() { }

	class MyView : public View
	{
	protected:
		virtual void DoDisplay();
	};

	void MyView::DoDisplay() {
		// render the view's contents 
	}
}
