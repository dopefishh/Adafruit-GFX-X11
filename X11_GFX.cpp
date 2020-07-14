#include <X11/Xlib.h>

#include "Adafruit_GFX.h"
#include "X11_GFX.h"

#define r(a, s) ((int)((double)a*s))

X11_GFX::X11_GFX(Display *display, int w, int h, double xscale, double yscale,
	const char *title)
	: Adafruit_GFX(w, h)
{
	disp = display;
	xs = xscale;
	ys = yscale;

	// Get some colors
	black = BlackPixel(disp, DefaultScreen(disp));
	white = WhitePixel(disp, DefaultScreen(disp));

	// Create the window
	win = XCreateSimpleWindow(disp, DefaultRootWindow(disp), 0, 0,
		w*xs, h*ys, 0, black, black);

	XStoreName(disp, win, title);

	// We want to get MapNotify events
	XSelectInput(disp, win, StructureNotifyMask);

	// "Map" the window (that is, make it appear on the screen)
	XMapWindow(disp, win);

	// Create a "Graphics Context"
	gc = XCreateGC(disp, win, 0, NULL);

	// Wait for the MapNotify event
	for(;;) {
		XEvent e;
		XNextEvent(disp, &e);
		if (e.type == MapNotify)
			break;
	}

	XSetBackground(disp, gc, white);
	XSetForeground(disp, gc, black);

	// Send the "DrawLine" request to the server
	XFlush(disp);
}
X11_GFX::X11_GFX(Display *display, int w, int h, double xscale, double yscale)
	: X11_GFX(display, w, h, xscale, yscale, "GFX Window") {}
X11_GFX::X11_GFX(Display *display, int w, int h)
	: X11_GFX(display, w, h, 1, 1) {}

X11_GFX::~X11_GFX(void)
{
	XFreeGC(disp, gc);
	XDestroyWindow(disp, win);
}

void X11_GFX::setDrawColor(uint16_t color)
{
	XSetForeground(disp, gc, color == 0 ? black : white);
}

void X11_GFX::drawPixel(int16_t x, int16_t y, uint16_t color)
{
	setDrawColor(color);
	XDrawPoint(disp, win, gc, r(x, xs), r(y, ys));
	XFlush(disp);
}

void X11_GFX::startWrite(void) { }
void X11_GFX::writePixel(int16_t x, int16_t y, uint16_t color)
{
	setDrawColor(color);
	XDrawPoint(disp, win, gc, r(x, xs), r(y, ys));
}
void X11_GFX::writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
	setDrawColor(color);
	XFillRectangle(disp, win, gc, r(x, xs), r(y, ys), r(w, xs), r(h, ys));
}
void X11_GFX::writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
	setDrawColor(color);
	XDrawLine(disp, win, gc, r(x, xs), r(y, ys), r(x, xs), r(y+h, ys));
}
void X11_GFX::writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
	setDrawColor(color);
	XDrawLine(disp, win, gc, r(x, xs), r(y, ys), r(x+w, xs), r(y, ys));
}
void X11_GFX::writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
	uint16_t color)
{
	setDrawColor(color);
	XDrawLine(disp, win, gc, r(x0, xs), r(y0, ys), r(x1, xs), r(y1, ys));
}
void X11_GFX::endWrite(void)
{
	XFlush(disp);
}

void X11_GFX::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
	startWrite();
	writeFastVLine(x, y, h, color);
	endWrite();
}
void X11_GFX::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
	startWrite();
	writeFastHLine(x, y, w, color);
	endWrite();
}
void X11_GFX::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
	startWrite();
	writeFillRect(x, y, w, h, color);
	endWrite();
}
void X11_GFX::fillScreen(uint16_t color)
{
	fillRect(0, 0, r(WIDTH, xs), r(HEIGHT, ys), color);
}
