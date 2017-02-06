#pragma once

#include <iostream>

namespace ProxyPattern::GoF2
{
	class Point {
	public:
		static Point Zero;

		bool operator==(Point&) { return false; }
	};

	Point Point::Zero = Point();

	class Event;

	class Graphic {
	public:
		virtual ~Graphic() {}

		virtual void Draw(const Point& at) = 0;
		virtual void HandleMouse(Event& event) = 0;

		virtual const Point& GetExtent() = 0;

		virtual void Load(std::istream& from) = 0;
		virtual void Save(std::ostream& to) = 0;
	protected:
		Graphic() {}
	};

	class Image : public Graphic {
	public:
		Image(const char* file) {}  // loads image from a file 
		virtual ~Image() {}

		virtual void Draw(const Point& at) {}
		virtual void HandleMouse(Event& event) {}

		virtual const Point& GetExtent() { return *(new Point()); }

		virtual void Load(std::istream& from) {}
		virtual void Save(std::ostream& to) {}
	private:
		// ... 
	};

	class ImageProxy : public Graphic {
	public:
		ImageProxy(const char* imageFile);
		virtual ~ImageProxy() {}

		virtual void Draw(const Point& at);
		virtual void HandleMouse(Event& event);

		virtual const Point& GetExtent();

		virtual void Load(std::istream& from);
		virtual void Save(std::ostream& to);
	protected:
		Image* GetImage();
	private:
		Image* _image;
		Point _extent;
		char* _fileName;
	};

	ImageProxy::ImageProxy(const char* fileName) {
//		_fileName = strdup(fileName);
		_extent = Point::Zero;  // don't know extent yet 
		_image = 0;
	}

	Image* ImageProxy::GetImage() {
		if (_image == 0) {
			_image = new Image(_fileName);
		}
		return _image;
	}

	const Point& ImageProxy::GetExtent() {
		if (_extent == Point::Zero) {
			_extent = GetImage()->GetExtent();
		}
		return _extent;
	}

	void ImageProxy::Draw(const Point& at) {
		GetImage()->Draw(at);
	}

	void ImageProxy::HandleMouse(Event& event) {
		GetImage()->HandleMouse(event);
	}

	void ImageProxy::Save(std::ostream& to) {
//		to << _extent << _fileName;
	}

	void ImageProxy::Load(std::istream& from) {
//		from >> _extent >> _fileName;
	}

	class TextDocument {
	public:
		TextDocument() {}

		void Insert(Graphic*) {}
		// ... 
	};
}
