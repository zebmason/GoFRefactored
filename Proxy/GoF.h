#pragma once

namespace ProxyPattern::GoF
{
	class Image;
	Image* LoadAnImageFile(const char*) { return nullptr; }
	// external function 

	class ImagePtr {
	public:
		ImagePtr(const char* imageFile);
		virtual ~ImagePtr() {}

		virtual Image* operator->();
		virtual Image& operator*();
	private:
		Image* LoadImage();
	private:
		Image* _image;
		const char* _imageFile;
	};

	ImagePtr::ImagePtr(const char* theImageFile) {
		_imageFile = theImageFile;
		_image = 0;
	}

	Image* ImagePtr::LoadImage() {
		if (_image == 0) {
			_image = LoadAnImageFile(_imageFile);
		}
		return _image;
	}

	Image* ImagePtr::operator-> () {
		return LoadImage();
	}

	Image& ImagePtr::operator* () {
		return *LoadImage();
	}
}
