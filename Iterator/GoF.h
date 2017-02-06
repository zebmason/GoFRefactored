#pragma once

#define DEFAULT_LIST_CAPACITY 10

namespace IteratorPattern::GoF
{
	class Item {};

	class List {
	public:
		List(long size = DEFAULT_LIST_CAPACITY) {}
		long Count() const { return 0; }
		Item& Get(long index) const { return *new Item(); }
		// ... 
	};


	class Iterator {
	public:
		virtual void First() = 0;
		virtual void Next() = 0;
		virtual bool IsDone() const = 0;
		virtual Item CurrentItem() const = 0;
	protected:
		Iterator() {}
	};

	class ListIterator : public Iterator {
	public:
		ListIterator(const List* aList);
		virtual void First();
		virtual void Next();
		virtual bool IsDone() const;
		virtual Item CurrentItem() const;
	private:
		const List* _list;
		long _current;
	};

	ListIterator::ListIterator(const List* aList)
		: _list(aList), _current(0) {    }

	void ListIterator::First()
	{
		_current = 0;
	}

	void ListIterator::Next()
	{
		_current++;
	}

	bool ListIterator::IsDone() const
	{
		return _current >= _list->Count();
	}

	Item ListIterator::CurrentItem() const {
		if (IsDone()) {
//			throw IteratorOutOfBounds;
		}
		return _list->Get(_current);
	}

	class Employee : public Item {
	public:
		void Print() {}
	};

	void PrintEmployees(Iterator& i) {
		for (i.First(); !i.IsDone(); i.Next()) {
			((Employee *)(&i.CurrentItem()))->Print();
		}
	}

	class AbstractList {
	public:
		virtual Iterator* CreateIterator() const = 0;
		// ...  
	};

#if 0
	template <class Item>
	Iterator<Item>* List<Item>::CreateIterator() const {
		return new ListIterator<Item>(this);
	}
#endif

	class IteratorPtr {
	public:
		IteratorPtr(Iterator* i) : _i(i) { }
		~IteratorPtr() { delete _i; }
		Iterator* operator->() { return _i; }
		Iterator& operator*() { return *_i; }
	private:
		// disallow copy and assignment to avoid 
		// multiple deletions of _i: 
		IteratorPtr(const IteratorPtr&);
		IteratorPtr& operator=(const IteratorPtr&);
	private:
		Iterator* _i;
	};

	class ListTraverser {
	public:
		ListTraverser(List* aList);
		bool Traverse();
	protected:
		virtual bool ProcessItem(const Item&) = 0;
	private:
		ListIterator _iterator;
	};

	ListTraverser::ListTraverser(List* aList)
		: _iterator(aList) { }

	bool ListTraverser::Traverse() {
		bool result = false;
		for (_iterator.First(); !_iterator.IsDone(); _iterator.Next()) {
			result = ProcessItem(_iterator.CurrentItem());
			if (result == false) {
				break;
			}
		}
		return result;
	}

	class PrintNEmployees : public ListTraverser {
	public:
		PrintNEmployees(List* aList, int n) :
			ListTraverser(aList),
			_total(n), _count(0) { }
	protected:
		bool ProcessItem(Employee* const&);
	private:
		int _total;
		int _count;
	};
	bool PrintNEmployees::ProcessItem(Employee* const& e) {
		_count++;
		e->Print();
		return _count < _total;
	}

	template <class Item>
	class FilteringListTraverser {
	public:
		FilteringListTraverser(List* aList) {}
		bool Traverse() { return true; }
	protected:
		virtual bool ProcessItem(const Item&) = 0;
		virtual bool TestItem(const Item&) = 0;
	private:
		ListIterator _iterator;
	};
}
