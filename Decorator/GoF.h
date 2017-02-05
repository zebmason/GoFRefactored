#pragma once

namespace DecoratorPattern::GoF
{
	class VisualComponent {
	public:
		VisualComponent() {}
		virtual void Draw() {}
		virtual void Resize() {}
		// ... 
	};

	class Decorator : public VisualComponent {
	public:
		Decorator(VisualComponent*) {}

		virtual void Draw();
		virtual void Resize();
		// ... 
	private:
		VisualComponent* _component;
	};

	void Decorator::Draw() {
		_component->Draw();
	}

	void Decorator::Resize() {
		_component->Resize();
	}

	class BorderDecorator : public Decorator {
	public:
		BorderDecorator(VisualComponent* v, int borderWidth)
			: Decorator(v) 
		{}
		virtual void Draw();
	private:
		void DrawBorder(int) {}
	private:
		int _width;
	};

	void BorderDecorator::Draw() {
		Decorator::Draw();
		DrawBorder(_width);
	}

	class ScrollDecorator : public Decorator {
	public:
		ScrollDecorator(VisualComponent* v)
			: Decorator(v)
		{}
	};

	class TextView : public VisualComponent {};

	class Window
	{
	public:
		void SetContents(VisualComponent* contents) {
			// ... 
		}
	};
}
