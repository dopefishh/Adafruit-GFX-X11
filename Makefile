CPPFLAGS+=-Wall -Wextra -DARDUINO=200 -I. -I./Adafruit-GFX-Library
CPPFLAGS+=$(shell pkg-config --cflags x11)
LDLIBS+=$(shell pkg-config --libs x11)

VPATH=Adafruit-GFX-Library

OBJS=X11_GFX.o Adafruit_GFX.o Print.o WString.o

test: $(OBJS)

clean:
	$(RM) $(OBJS) test
