#pragma once

namespace CompositePattern::GoF2
{
	class Watt {};
	class Currency {};
	class Iterator {};
	class List {};

	class Equipment {
	public:
		virtual ~Equipment() {}

		const char* Name() { return _name; }

		virtual Watt Power() { return *new Watt(); }
		virtual Currency NetPrice() { return *new Currency(); }
		virtual Currency DiscountPrice() { return *new Currency(); }

		virtual void Add(Equipment*) {}
		virtual void Remove(Equipment*) {}
		virtual Iterator* CreateIterator() {}
	protected:
		Equipment(const char*) {}
	private:
		const char* _name;
	};

	class FloppyDisk : public Equipment {
	public:
		FloppyDisk(const char* name) : Equipment(name) {}
		virtual ~FloppyDisk() {}

		virtual Watt Power() { return *new Watt(); }
		virtual Currency NetPrice() { return *new Currency(); }
		virtual Currency DiscountPrice() { return *new Currency(); }
	};

	class CompositeEquipment : public Equipment {
	public:
		virtual ~CompositeEquipment() {}

		virtual Watt Power() { return *new Watt(); }
		virtual Currency NetPrice();
		virtual Currency DiscountPrice() { return *new Currency(); }

		virtual void Add(Equipment*) {}
		virtual void Remove(Equipment*) {}
		virtual Iterator* CreateIterator() { return nullptr; }

	protected:
		CompositeEquipment(const char* name) : Equipment(name) {}
	private:
		List _equipment;
	};

	Currency CompositeEquipment::NetPrice() {
		Iterator* i = CreateIterator();
		Currency total; // = 0;

//		for (i->First(); !i->IsDone(); i->Next()) {
//			total += i->CurrentItem()->NetPrice();
//		}
		delete i;
		return total;
	}

	class Chassis : public CompositeEquipment {
	public:
		Chassis(const char* name) : CompositeEquipment(name) {}
		virtual ~Chassis() {}

		virtual Watt Power() { return *new Watt(); }
		virtual Currency NetPrice() { return *new Currency(); }
		virtual Currency DiscountPrice() { return *new Currency(); }
	};
}
