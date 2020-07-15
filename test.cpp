#include <stdio.h>
#include <X11/Xlib.h>
#include "X11_GFX.h"

#include <unistd.h>

int main(void)
{
	Display *display = XOpenDisplay(NULL);
	if (display == NULL) {
		fprintf(stderr, "error opening display\n");
		exit(1);
	}

	X11_GFX gfx = X11_GFX(display, 100, 100, 5);
	gfx.drawLine(5, 5, 50, 50, 1);
	gfx.drawCircle(50, 50, 10, 1);
	gfx.drawRect(80, 80, 90, 90, 1);
	gfx.drawPixel(98, 98, 1);
	gfx.drawPixel(0, 98, 1);
	gfx.drawPixel(1, 97, 1);
	gfx.drawPixel(2, 96, 1);
	gfx.drawLine(0, 95, 0, 90, 1);
	gfx.drawLine(1, 90, 1, 85, 1);
	gfx.drawLine(2, 85, 2, 80, 1);
	gfx.print("blurp");
	sleep(10);
	XCloseDisplay(display);
	return 0;
}
