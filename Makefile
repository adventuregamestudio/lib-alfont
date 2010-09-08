# Makefile for AllegroFont using FreeType 2


# select (uncomment) one target and comment DJGPP if you are not aiming
# for that platform

#TARGET=DJGPP_STATIC
#TARGET=MINGW32_STATIC
#TARGET=MINGW32_DLL
TARGET=LINUX_STATIC


CC=gcc
LFLAGS=
LIBIMP=



# DJGPP_STATIC
ifeq ($(TARGET),DJGPP_STATIC)
TARGETFLAGS=-Wall -O2 -march=pentium -fomit-frame-pointer -finline-functions -ffast-math
LIBS=../lib/djgpp/libiconv.a  -liconv
OBJDIR=obj/djgpp/static
LIBDEST=lib/djgpp/libalfont.a
LIB_INSTALL_PATH = $(DJDIR)/lib
INCLUDE_INSTALL_PATH = $(DJDIR)/include
endif



# MINGW32_STATIC
ifeq ($(TARGET),MINGW32_STATIC)
LFLAGS=-mwindows
TARGETFLAGS=-Wall -O2 -march=pentium -fomit-frame-pointer -finline-functions -ffast-math
OBJDIR=obj/mingw32/static
LIBDEST=lib/mingw32/libalfont.a
LIB_INSTALL_PATH = $(MINGDIR)/lib
INCLUDE_INSTALL_PATH = $(MINGDIR)/include
endif


# MINGW32_DLL
ifeq ($(TARGET),MINGW32_DLL)
LFLAGS=-mwindows -shared
TARGETFLAGS=-Wall -O2 -march=pentium -fomit-frame-pointer -finline-functions -ffast-math
OBJDIR=obj/mingw32/dll
LIBIMP=lib/mingw32/libalfontdll.a
LIBDEST=lib/mingw32/alfont.dll
ALFONT_DLL=1
ALFONT_DLL_EXPORTS=1
LIB_INSTALL_PATH = $(MINGDIR)/lib
INCLUDE_INSTALL_PATH = $(MINGDIR)/include
endif



# LINUX_STATIC
ifeq ($(TARGET),LINUX_STATIC)
TARGETFLAGS=-Wall -O2 -march=pentium -fomit-frame-pointer -finline-functions -ffast-math
OBJDIR=obj/linux/static
LIBDEST=lib/linux/libalfont.a
LIB_INSTALL_PATH = /usr/local/lib
INCLUDE_INSTALL_PATH = /usr/local/include
endif



# setting object files, paths and compiler flags
vpath %.c freetype/src/autofit
vpath %.c freetype/src/base
vpath %.c freetype/src/cache
vpath %.c freetype/src/cff
vpath %.c freetype/src/cid
vpath %.c freetype/src/lzw
vpath %.c freetype/src/otvalid
vpath %.c freetype/src/pcf
vpath %.c freetype/src/psaux
vpath %.c freetype/src/psnames
vpath %.c freetype/src/pshinter
vpath %.c freetype/src/raster
vpath %.c freetype/src/sfnt
vpath %.c freetype/src/smooth
vpath %.c freetype/src/truetype
vpath %.c freetype/src/type1
vpath %.c freetype/src/type42
vpath %.c freetype/src/gzip
vpath %.c freetype/src/bdf
vpath %.c freetype/src/pfr
vpath %.c freetype/src/winfonts

vpath %.c src
vpath %.o $(OBJDIR)

CFLAGS=$(TARGETFLAGS) -Ifreetype/include -Iinclude
OBJECTS=alfont.o ftsystem.o ftdebug.o ftinit.o ftbase.o ftbitmap.o ftglyph.o ftmm.o ftcache.o cff.o type1cid.o otvalid.o pcf.o psaux.o pshinter.o psmodule.o raster.o sfnt.o smooth.o truetype.o type1.o winfnt.o type42.o ftgzip.o ftlzw.o pfr.o bdf.o autofit.o
OBJECTS2=$(addprefix $(OBJDIR)/,$(OBJECTS))



# making of the library

# MINGW32_DLL
ifeq ($(TARGET),MINGW32_DLL)
$(LIBDEST): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS2) $(LFLAGS) $(CFLAGS) -Wl,--out-implib=$(LIBIMP) -lalleg

# others
else
$(LIBDEST): $(OBJECTS)
	ar rs $(LIBDEST) $(OBJECTS2)
endif


# compiling of the library
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $(OBJDIR)/$@

.PHONY: clean install
clean:
	rm -f $(OBJECTS2) $(LIBDEST) $(LIBIMP)

.PHONY: install
install: $(LIBDEST)
ifeq ($(TARGET),MINGW32_DLL)
	copy /y $(LIBDEST) $(subst /,\,$(LIB_INSTALL_PATH))
	copy /y include\*.h $(subst /,\,$(INCLUDE_INSTALL_PATH))
else
	cp $(LIBDEST) $(LIB_INSTALL_PATH)
	cp include/*.h $(INCLUDE_INSTALL_PATH)
endif
