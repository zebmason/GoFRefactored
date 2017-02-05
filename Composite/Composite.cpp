// Composite.cpp : Defines the entry point for the console application.
//

#include "GoF.h"
#include "Variant1.h"

int main()
{
	{
		CompositePattern::GoF::Composite* aComposite = new CompositePattern::GoF::Composite;
		CompositePattern::GoF::Leaf* aLeaf = new CompositePattern::GoF::Leaf;

		CompositePattern::GoF::Component* aComponent;
		CompositePattern::GoF::Composite* test;

		aComponent = aComposite;
		if (test = aComponent->GetComposite()) {
			test->Add(new CompositePattern::GoF::Leaf);
		}

		aComponent = aLeaf;

		if (test = aComponent->GetComposite()) {
			test->Add(new CompositePattern::GoF::Leaf); // will not add leaf 
		}
	}

	{
		CompositePattern::Variant1::Composite* aComposite = new CompositePattern::Variant1::Composite;
		CompositePattern::Variant1::Leaf* aLeaf = new CompositePattern::Variant1::Leaf;

		CompositePattern::Variant1::Component* aComponent;
		CompositePattern::Variant1::Composite* test;

		aComponent = aComposite;
		if (aComponent->IsComposite()) {
			test = dynamic_cast<CompositePattern::Variant1::Composite*>(aComponent);
			test->Add(new CompositePattern::Variant1::Leaf);
		}

		aComponent = aLeaf;

		if (aComponent->IsComposite()) {
			test = dynamic_cast<CompositePattern::Variant1::Composite*>(aComponent);
			test->Add(new CompositePattern::Variant1::Leaf); // will not add leaf 
		}
	}
    return 0;
}

