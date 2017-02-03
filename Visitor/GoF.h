#pragma once

#include <iostream>
#include <vector>

namespace VisitorPattern::GoF
{
	class ElementA;
	class ElementB;

	class Visitor {
	public:
		virtual void VisitElementA(ElementA*)
		{
			std::cout << "A";
		}

		virtual void VisitElementB(ElementB*)
		{
			std::cout << "B";
		}

		Visitor() {}
	};

	class Element {
	public:
		virtual ~Element() {}
		virtual void Accept(Visitor&) = 0;
	protected:
		Element() {}
	};

	class ElementA : public Element {
	public:
		ElementA() {}
		virtual void Accept(Visitor& v) { v.VisitElementA(this); }
	};

	class ElementB : public Element {
	public:
		ElementB() {}
		virtual void Accept(Visitor& v) { v.VisitElementB(this); }
	};

	class CompositeElement : public Element {
	private:
		std::vector<Element*> _children;
	public:
		virtual void Accept(Visitor& v) {
			std::cout << "C";
			for (auto i : _children)
				i->Accept(v);
		}

		void Add(Element* child)
		{
			_children.push_back(child);
		}
	};
}