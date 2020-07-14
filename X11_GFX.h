#ifndef _X11_GFX_H
#define _X11_GFX_H

#include <X11/Xlib.h>

#include "Adafruit_GFX.h"

#define X11_BLACK 0
#define X11_WHITE 1

class X11_GFX : public Adafruit_GFX {
public:
	X11_GFX(Display *display, int w, int h, double xscale, double yscale,
		const char *title);
	X11_GFX(Display *display, int w, int h, double xscale, double yscale);
	X11_GFX(Display *display, int w, int h);
	~X11_GFX(void);

	void drawPixel(int16_t x, int16_t y, uint16_t color);

	void startWrite(void);
	void writePixel(int16_t x, int16_t y, uint16_t color);
	void writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h,
		uint16_t color);
	void writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
	void writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
	void writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
		uint16_t color);
	void endWrite(void);

	void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
	void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
	void fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
		uint16_t color);
	void fillScreen(uint16_t color);
private:
	void setDrawColor(uint16_t color);

	Display *disp;
	Window win;
	GC gc;
	int black, white;
	double xs, ys;
};

#endif
