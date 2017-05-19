V ?= 0

ifeq ($V, 1)
E =
P = @true
else
E = @
P = @echo
endif

SHELL = /bin/sh

srcdir		= src
objdir		= obj
prefix		= $(DESTDIR)/usr/local
exec_prefix	= $(DESTDIR)/${prefix}
bindir		= $(exec_prefix)/bin

CC			= $(CROSS_COMPILE)gcc
#CC			= $(CROSS_COMPILE)arm-poky-linux-gnueabi-gcc
INSTALL		= install
MKDIR		= mkdir -p

LIBS		=  -lusb-1.0 -lpthread
CFLAGS		+= -g -O0
LDFLAGS 	+=
CPPFLAGS	+=

ARCH		?= $(ARM)
#ARCH_CFLAGS	?= $(CFLAGS_x86_64)

CFLAGS		+= -I/usr/local/libusb/include
CFLAGS		+= -Wall -Wextra -Wno-char-subscripts -Wno-unused-parameter -Wno-format
CFLAGS		+= $(ARCH_CFLAGS)

OBJ 		= $(objdir)/usb.o \

TARGET		= linux-usb

all: $(objdir) $(TARGET)

$(TARGET): $(OBJ)
	$P '  LD       $@'
	$E $(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

$(objdir):
	$E mkdir $(objdir)

$(objdir)/%.o: $(srcdir)/%.c
	$P '  CC       $@'
	$E $(CC) $(CFLAGS) -c -o $@ $^

.PHONY: clean
clean:
	$P '  RM       TARGET'
	$E rm -f $(TARGET)
	$P '  RM       OBJS'
	$E rm -rf $(objdir)

install:
	$P '  MKDIRS   '
	$E $(MKDIR) $(bindir)
	$P '  INSTALL  $(TARGET)'
	$E $(INSTALL) $(TARGET) $(bindir)

uninstall:
	$P '  UNINSTALL'
	$E rm -f $(bindir)/$(TARGET)

