#pragma once

namespace BridgePattern::GoF
{
	class View {};
	class Coord {
	public:
		Coord(double) {}
	};
	class Point {
	private:
		Coord x, y;
	public:
		const Coord& X() const { return x; }
		const Coord& Y() const { return y; }
	};
	class WindowImp;

	class Window {
	public:
		Window(View* contents) 
			: _contents(contents)
		{}

		// requests handled by window 
		virtual void DrawContents() {}

		virtual void Open() {}
		virtual void Close() {}
		virtual void Iconify() {}
		virtual void Deiconify() {}

		// requests forwarded to implementation 
		virtual void SetOrigin(const Point& at) {}
		virtual void SetExtent(const Point& extent) {}
		virtual void Raise() {}
		virtual void Lower() {}

		virtual void DrawLine(const Point&, const Point&) {}
		virtual void DrawRect(const Point&, const Point&);
		virtual void DrawPolygon(const Point[], int n) {}
		virtual void DrawText(const char*, const Point&) {}

	protected:
		WindowImp* GetWindowImp();
		View* GetView() { return nullptr; }

	private:
		WindowImp* _imp;
			View* _contents; // the window's contents 
	};

	class WindowImp {
	public:
		virtual void ImpTop() = 0;
		virtual void ImpBottom() = 0;
		virtual void ImpSetExtent(const Point&) = 0;
		virtual void ImpSetOrigin(const Point&) = 0;

		virtual void DeviceRect(const Coord&, const Coord&, const Coord&, const Coord&) = 0;
		virtual void DeviceText(const char*, Coord, Coord) = 0;
		virtual void DeviceBitmap(const char*, Coord, Coord) = 0;
		// lots more functions for drawing on windows... 
	protected:
		WindowImp() {}
	};

	class ApplicationWindow : public Window {
	public:
		// ... 
		virtual void DrawContents();
	};

	void ApplicationWindow::DrawContents() {
		// GetView()->DrawOn(this);
	}

	class IconWindow : public Window {
	public:

		// ... 
		virtual void DrawContents();
	private:
		const char* _bitmapName;
	};

	void IconWindow::DrawContents() {
		WindowImp* imp = GetWindowImp();
		if (imp != 0) {
			imp->DeviceBitmap(_bitmapName, 0.0, 0.0);
		}
	}

	void Window::DrawRect(const Point& p1, const Point& p2) {
		WindowImp* imp = GetWindowImp();
		imp->DeviceRect(p1.X(), p1.Y(), p2.X(), p2.Y());
	}

	class Display {};
	class Drawable {};
	class GC {};

	class XWindowImp : public WindowImp {
	public:
		XWindowImp() {}

		virtual void DeviceRect(const Coord&, const Coord&, const Coord&, const Coord&) {}
		// remainder of public interface... 
	private:
		// lots of X window system-specific state, including: 
		Display* _dpy;
		Drawable _winid;  // window id 
		GC _gc;           // window graphic context 
	};

	class HPS {};

	class PMWindowImp : public WindowImp {
	public:
		PMWindowImp() {}
		virtual void DeviceRect(const Coord&, const Coord&, const Coord&, const Coord&) {}

		// remainder of public interface... 
	private:
		// lots of PM window system-specific state, including: 
		HPS _hps;
	};

	WindowImp* Window::GetWindowImp() {
		//if (_imp == 0) {
		//	_imp = WindowSystemFactory::Instance()->MakeWindowImp();
		//}
		return _imp;
	}
}
