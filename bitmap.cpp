#include "bitmap.h"


Bitmap::Bitmap (unsigned w, unsigned h) : width (w), height (h), pixels (width * height){
	assert (width < 32767);
	assert (height < 32767);
}

Color& Bitmap::operator () (unsigned x, unsigned y){
	assert (x < width);
	assert (y < height);
	return pixels[y * width + x];
}

Color Bitmap::operator () (unsigned x, unsigned y) const{
	assert (x < width);
	assert (y < height);
	return pixels[y * width + x];
}

int Bitmap::GetWidth () const{
	return width;
}

int Bitmap::GetHeight () const{
	return height;
}

void Bitmap::Fill (Color color){
	std::fill (pixels.begin (), pixels.end (), color);
}

void Bitmap::Save (const char* filename) const
{
	assert (filename);
	std::ofstream file (filename, std::ios::binary);

	enum {WORD = 2, DWORD = 4, LONG = 4};
	const unsigned padding = (4 - width * 3 % 4) % 4;

	// BITMAPFILEHEADER
	Write (file, WORD, 0x4d42);	// bfType
	Write (file, DWORD, 14 + 40 + (width * 3 + padding) * height);	// bfSize
	Write (file, WORD, 0);		// bfReserved1
	Write (file, WORD, 0);		// bfReserved2
	Write (file, DWORD, 14 + 40);	// bfOffBits

	// BITMAPINFOHEADER
	Write (file, DWORD, 40);	// biSize
	Write (file, LONG, width);	// biWidth
	Write (file, LONG, -height);	// biHeight
	Write (file, WORD, 1);		// biPlanes
	Write (file, WORD, 24);		// biBitCount
	Write (file, DWORD, 0);		// biCompression
	Write (file, DWORD, 0);		// biSizeImage
	Write (file, LONG, 0);		// biXPelsPerMeter
	Write (file, LONG, 0);		// biYPelsPerMeter
	Write (file, DWORD, 0);		// biClrUsed
	Write (file, DWORD, 0);		// biClrImportant

	for (unsigned y = 0; y != height; ++y)
	{
		for (unsigned x = 0; x != width; ++x)
		{
			const Color& color (pixels[y * width + x]);
			Write (file, color.b);
			Write (file, color.g);
			Write (file, color.r);
		}

		for (unsigned x = 0; x != padding; ++x)
			Write (file, 0);
	}
}

void Bitmap::Write (std::ostream& os, float value)
{
    int intValue = 256 * (value < 0 ? 0 : value > 1 ? 1 : value);
	os.put (intValue < 256 ? intValue : 255);
}

void Bitmap::Write (std::ostream& os, unsigned length, int value)
{
	while (length--) os.put (value & 0xff), value >>= 8;
}

