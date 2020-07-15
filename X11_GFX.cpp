#include <X11/Xlib.h>

#include "X11_GFX.h"
#include "Adafruit_GFX.h"

#define r(a) ((int)((double)a*sc + sc/2.0))

X11_GFX::X11_GFX(Display *display, int w, int h, double scale,
	const char *title)
	: Adafruit_GFX(w, h)
{
	disp = display;
	sc = scale < 1.0 ? 1.0 : scale;

	// Get some colors
	black = BlackPixel(disp, DefaultScreen(disp));
	white = WhitePixel(disp, DefaultScreen(disp));

	// Create the window
	win = XCreateSimpleWindow(disp, DefaultRootWindow(disp), 0, 0,
		r(w), r(h), 0, black, black);

	// Set the title
	XStoreName(disp, win, title);

	// We want to get MapNotify events
	XSelectInput(disp, win, StructureNotifyMask);

	// "Map" the window (that is, make it appear on the screen)
	XMapWindow(disp, win);

	// Create a "Graphics Context"
	gc = XCreateGC(disp, win, 0, NULL);
	XSetLineAttributes(disp, gc, (int)sc, LineSolid, CapNotLast,
		JoinMiter);

	// Wait for the MapNotify event
	for(;;) {
		XEvent e;
		XNextEvent(disp, &e);
		if (e.type == MapNotify)
			break;
	}

	XSetBackground(disp, gc, white);
	XSetForeground(disp, gc, black);
}

X11_GFX::X11_GFX(Display *display, int w, int h, double scale)
	: X11_GFX(display, w, h, scale, "GFX Window") {}

X11_GFX::X11_GFX(Display *display, int w, int h)
	: X11_GFX(display, w, h, 1.0) {}

X11_GFX::X11_GFX(Display *display)
	: X11_GFX(display, 100, 100) {}

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
	startWrite();
	writePixel(x, y, color);
	endWrite();
}

void X11_GFX::writePixel(int16_t x, int16_t y, uint16_t color)
{
	setDrawColor(color);
	XFillRectangle(disp, win, gc, r(x), r(y), sc, sc);
}

void X11_GFX::writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h,
	uint16_t color)
{
	setDrawColor(color);
	XFillRectangle(disp, win, gc, r(x), r(y), r(w), r(h));
}

void X11_GFX::writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
	uint16_t color)
{
	setDrawColor(color);
	XDrawLine(disp, win, gc, r(x0), r(y0), r(x1), r(y1));
}

void X11_GFX::endWrite(void)
{
	XFlush(disp);
}
