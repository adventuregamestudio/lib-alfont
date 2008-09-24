/* AllegroFont - a wrapper for FreeType 2 */
/* to render TTF and other font formats with Allegro */

            
/* FreeType 2 is copyright (c) 1996-2000 */
/* David Turner, Robert Wilhelm, and Werner Lemberg */
/* AllegroFont is copyright (c) 2001, 2002 Javier Gonz†lez */
/* Enhanced by Chernsha since 2004 year */

/* See FTL.txt (FreeType Project License) for license */


/* example1.c - Shows how to print some text using a given font file */


/* headers */
#include <allegro.h>
#include "../include/alfont.h"
#include <stddef.h>
#include <stdio.h>

/* defines */

/* show_help - shows the help */
void show_help(void) {
  allegro_message("Use: example1 fontFilename");
}

/* parse_parameters - checks all the parameters are right */
/*                    returns 0 on success or anything else on error */
int parse_parameters(int argc, char *argv[]) {
  /* if we don't have two parameters */
  /* (first parameter is the executable name) always passed, second
     should be the font name */
  if (argc != 2) {
    /* show help and return error */
    show_help();
    return 1;
  }

  /* all ok */
  return 0;
}

/* main */
int main(int argc, char *argv[]) {
ALFONT_FONT *user_font;
char *SAMPLE_TEXT="ABCDEFGH¡c≈È§§§Â";
char *SAMPLE_FIX;
int al_text_length=0;
#ifndef ALFONT_LINUX
char textcount[10]="";
#endif

/* init allegro */
allegro_init();

/* set the window title */
set_window_title("AllegroFont - example1");

/* parse the parameters */
if (parse_parameters(argc, argv) != 0) {
  /* error while parsing the parameters */
  allegro_exit();
  return 1;
}

/* init the gfx mode (try all possible color depths) */
set_color_depth(16);

#ifdef ALFONT_WINDOWS	//run in WINDOWS
if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0) != 0) {
#endif
#ifdef ALFONT_DOS		//run in DOS
if (set_gfx_mode(GFX_AUTODETECT, 800, 600, 0, 0) != 0) {
#endif
#ifdef ALFONT_LINUX		//run in LINUX
if (set_gfx_mode(GFX_AUTODETECT, 800, 600, 0, 0) != 0) {
#endif
  if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0) != 0) {
    set_color_depth(15);
    if (set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0) != 0) {
      set_color_depth(32);
      if (set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0) != 0) {
        set_color_depth(24);
        if (set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0) != 0) {
          /* impossible to set the gfx */
          allegro_message("Impossible to set up the gfx mode");
          allegro_exit();
          return 1;
        }
      }
    }
  }
}


/* install the keyboard routines */
install_keyboard();

/* now init AllegroFont */
if (alfont_init() != ALFONT_OK) {
  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
  allegro_message("Error while initializing alfont");
  allegro_exit();
  return 1;
}

/* try to load the font given by the parameter*/
user_font = alfont_load_font(argv[1]);
if (user_font == NULL) {
  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
  allegro_message("Cannot load the font");
  alfont_exit();
  allegro_exit();
  return 1;
}

alfont_set_language(user_font, Encode_Code);	
alfont_set_convert(user_font, TYPE_WIDECHAR);
alfont_set_char_extra_spacing(user_font, 5);
alfont_text_mode(-1);
floodfill(screen, 0, 0, makecol(125,35,45));
alfont_set_font_background(user_font, FALSE);
alfont_set_font_size(user_font,30);

if (alfont_need_uconvert(user_font, SAMPLE_TEXT)) {
#ifndef ALFONT_LINUX
allegro_message("%s", "the unicode conversion is required for SAMPLE_TEXT string.");
#else
printf("%s", "the unicode conversion is required for SAMPLE_TEXT string.");
#endif
}

alfont_textout_aa(screen, user_font, SAMPLE_TEXT, 0, 0, makecol(255,255,255));
alfont_textout(screen, user_font, SAMPLE_TEXT, 0, 30, makecol(255,255,255));

alfont_set_font_outline_top(user_font,1);
alfont_set_font_outline_bottom(user_font,1);
alfont_set_font_outline_left(user_font,1);
alfont_set_font_outline_right(user_font,1);
alfont_set_font_outline_color(user_font,makecol(22,33,144));
alfont_textout(screen, user_font, SAMPLE_TEXT, 0, 60, makecol(255,255,255));

alfont_set_font_outline_hollow(user_font, TRUE);
alfont_textout(screen, user_font, SAMPLE_TEXT, 0, 90, makecol(255,255,255));
alfont_set_font_outline_hollow(user_font, FALSE);
alfont_set_font_outline_top(user_font,0);
alfont_set_font_outline_bottom(user_font,0);
alfont_set_font_outline_left(user_font,0);
alfont_set_font_outline_right(user_font,0);

alfont_set_font_style(user_font, STYLE_STANDARD);
alfont_textout(screen, user_font, SAMPLE_TEXT, 0, 120, makecol(255,255,255));

alfont_set_font_style(user_font, STYLE_ITALIC);
alfont_textout(screen, user_font, SAMPLE_TEXT, 0, 150, makecol(255,255,255));

alfont_set_font_style(user_font, STYLE_BOLD);
alfont_textout(screen, user_font, SAMPLE_TEXT, 0, 180, makecol(255,255,255));

alfont_set_font_style(user_font, STYLE_BOLDITALIC);
alfont_textout(screen, user_font, SAMPLE_TEXT, 0, 210, makecol(255,255,255));
alfont_set_font_style(user_font, STYLE_STANDARD);

alfont_set_font_underline(user_font, TRUE);	
alfont_textout(screen, user_font, SAMPLE_TEXT, 0, 240, makecol(255,255,255));

alfont_set_font_style(user_font, STYLE_ITALIC);
alfont_set_font_underline_right(user_font, TRUE); //connect underline from this string to next string.
alfont_textout(screen, user_font, SAMPLE_TEXT, 0, 270, makecol(255,255,255));
alfont_set_font_underline_right(user_font, FALSE);

alfont_set_font_style(user_font, STYLE_BOLDITALIC);
alfont_set_font_underline_left(user_font, TRUE); //connect underline from last string to this string.
alfont_textout(screen, user_font, SAMPLE_TEXT, 0, 300, makecol(255,255,255));
alfont_set_font_style(user_font, STYLE_STANDARD);
alfont_set_font_underline(user_font, FALSE);
alfont_set_font_underline_left(user_font, FALSE);

alfont_set_font_transparency(user_font, 50);
alfont_textout(screen, user_font, SAMPLE_TEXT, 0, 330, makecol(255,255,255));

#ifndef ALFONT_LINUX
allegro_message("%d", alfont_text_count(user_font,SAMPLE_TEXT));  //show char count message
#else
printf("%d",alfont_text_count(user_font,SAMPLE_TEXT));
#endif

alfont_set_font_transparency(user_font, 255);
alfont_set_autofix(user_font, TRUE);

SAMPLE_FIX = SAMPLE_TEXT;
while (*SAMPLE_FIX != '\0') {
	SAMPLE_FIX++;
}
SAMPLE_FIX--;
*SAMPLE_FIX='\0';

alfont_textout(screen, user_font, SAMPLE_TEXT, 0, 360, makecol(255,255,255));

SAMPLE_TEXT = (char *)malloc(2*sizeof(char));
memset(SAMPLE_TEXT, 0, 2);
SAMPLE_TEXT[0] = 229;
SAMPLE_TEXT[1] = 0;
alfont_textout(screen, user_font, SAMPLE_TEXT, 0, 390, makecol(255,255,255));

readkey();

alfont_destroy_font(user_font);
alfont_exit();
allegro_exit();
  return 0;
}
END_OF_MAIN();