#pragma once

#include <iostream>
#include <vector>

namespace VisitorPattern::Variant1
{
	class Element {
	public:
		virtual ~Element() {}

		virtual const char* Id() = 0;
	protected:
		Element() {}
	};

	class ElementA : public Element {
	public:
		ElementA() {}
		const char* Id() { return "A"; }
	};

	class ElementB : public Element {
	public:
		ElementB() {}
		const char* Id() { return "B"; }
	};

	class IVisitor {
	public:
		virtual void Visit(Element* el) = 0;
	};

	class CompositeElement : public Element {
	private:
		std::vector<Element*> _children;
	public:
		void Accept(IVisitor& v) {
			for (auto i : _children)
			{
				v.Visit(i);
			}
		}

		const char* Id() { return "C"; }

		void Add(Element* child)
		{
			_children.push_back(child);
		}
	};


	class Visitor : public IVisitor {
	public:
		void Visit(Element* el)
		{
			auto id = el->Id();
			std::cout << id;
			auto comp = dynamic_cast<CompositeElement*>(el);
			if (comp != nullptr)
				comp->Accept(*this);
		}
	};

}