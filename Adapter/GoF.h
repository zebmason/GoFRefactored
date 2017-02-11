#pragma once

namespace AdapterPattern::GoF
{
	class Coord {
	public:
		Coord& operator+ (Coord&) { return *this; }
	};

	class Point {
	public:
		Point(Coord&, Coord&) {};
	};
	class Manipulator {};

	class Shape {
	public:
		Shape() {}
		virtual void BoundingBox(
			Point& bottomLeft, Point& topRight
		) const {}
		virtual Manipulator* CreateManipulator() const { return nullptr; }
	};

	class TextManipulator : public Manipulator {
	public:
		TextManipulator(const Shape*) {}
	};

	class TextView {
	public:
		TextView() {}
		void GetOrigin(Coord& x, Coord& y) const {}
		void GetExtent(Coord& width, Coord& height) const {}
		virtual bool IsEmpty() const {}
	};

	class TextShape : public Shape {
	public:
		TextShape(TextView*);

		virtual void BoundingBox(
			Point& bottomLeft, Point& topRight
		) const;
		virtual bool IsEmpty() const;
		virtual Manipulator* CreateManipulator() const;
	private:
		TextView* _text;
	};

	TextShape::TextShape(TextView* t) {
		_text = t;
	}

	void TextShape::BoundingBox(
		Point& bottomLeft, Point& topRight
	) const {
		Coord bottom, left, width, height;

		_text->GetOrigin(bottom, left);
		_text->GetExtent(width, height);

		bottomLeft = Point(bottom, left);
		topRight = Point(bottom + height, left + width);
	}

	bool TextShape::IsEmpty() const {
		return _text->IsEmpty();
	}

	Manipulator* TextShape::CreateManipulator() const {
		return new TextManipulator(this);
	}
}
