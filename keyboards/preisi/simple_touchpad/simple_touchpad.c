#include <hal.h>
#include <quantum.h>

void keyboard_post_init_user(void) {
	debug_enable = true;
	debug_matrix = true;
}
