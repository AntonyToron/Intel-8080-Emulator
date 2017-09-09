/*
  File name : Graphics.h
  Author : Antony Toron

  Description : Provides an interface for a render function for the 8080
  emulator.

 */

extern "C" {
#include "CPU.h"
}
#include "Types.h"
//#include <GLFW/glfw.h>

typedef void (*render_func)(State8080_T, unsigned char *, GLFWwindow *);

render_func render_function(ROM rom);
/*void (*render_function(ROM rom))(State8080_T,
				 unsigned char *,
				 GLFWwindow *);
*/
