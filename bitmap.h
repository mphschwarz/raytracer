#ifndef BITMAP_H
#define BITMAP_H

#include <vector>
#include <fstream>

#include "color.h"

class Bitmap{
	public:
		Bitmap (unsigned, unsigned);

		Color& operator () (unsigned, unsigned);
		Color operator () (unsigned, unsigned) const;

		int GetWidth () const;
		int GetHeight () const;

		void Fill (Color);
		void Save (const char*) const;

	private:	
		unsigned width, height;
		std::vector<Color> pixels;
	
		static void Write (std::ostream&, float);
		static void Write (std::ostream&, unsigned, int);
};

#endif
