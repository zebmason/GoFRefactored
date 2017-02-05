#pragma once

namespace CompositePattern::GoF
{
	class Composite;

	class Component {
	public:
		//... 
			virtual Composite* GetComposite() { return 0; }
	};

	class Composite : public Component {
	public:
		void Add(Component*) {}
		// ... 
		virtual Composite* GetComposite() { return this; }
	};

	class Leaf : public Component {
		// ... 
	};
}
