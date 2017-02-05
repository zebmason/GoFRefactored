#pragma once

namespace CompositePattern::Variant1
{
	class Component {
	public:
		//... 
		virtual bool IsComposite() { return false; }
	};

	class Composite : public Component {
	public:
		void Add(Component*) {}
		// ... 
		virtual bool IsComposite() { return true; }
	};

	class Leaf : public Component {
		// ... 
	};
}
