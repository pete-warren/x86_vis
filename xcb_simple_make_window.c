#include <xcb/xcb.h>
#include <unistd.h> // used for pause()


int main() {
	xcb_connection_t 	*c;
	xcb_screen_t  		*screen;
	xcb_window_t		win;

	// open the connection to the x server
	c = xcb_connect(NULL, NULL);

	// get the first screen?..
	screen = xcb_setup_roots_iterator(xcb_get_setup(c)).data;

	// get a window id
	win = xcb_generate_id(c);

	// use id to make window
	xcb_create_window(c,
			XCB_COPY_FROM_PARENT,
			win,
			screen->root,
			0, 0,
			150, 150,
			10,
			XCB_WINDOW_CLASS_INPUT_OUTPUT,
			screen->root_visual,
			0, NULL);

	// map the win to the screen
	xcb_map_window(c, win);

	// make sure cmds are sent before we pause, so window is shown
	xcb_flush(c);

	pause(); // holds it here until ctrl-c
	
	return 0;
}

