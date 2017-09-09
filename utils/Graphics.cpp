/*
  File name : Graphics.c
  Author : Antony Toron

  Description : Defines an easy interface for determining a render function
  based on a ROM for the 8080 emulator.
 */

#include <GLFW/glfw3.h>
#include "Graphics.h"
extern "C" {
#include "Types.h"
}
extern "C" {
#include "CPU.h"
}

#include <unistd.h>

const int RGB_ON = 0xFFFFFFFF;
const int RGB_OFF = 0x00000000;

const unsigned int W_internal = 224;
const unsigned int H_internal = 256;


// ----------------------- POPULATE WINDOW --------------------- //

void populateWindowFromMemoryInvaders(State8080_T state, unsigned char *windowPixels) {
  int i, j;
  
  // 1-bit space invaders video into window
  uint16_t startVideoMemory = 0x2400;
  uint8_t *videoMemory = pointerToMemoryAt(state, startVideoMemory);
  
  // copy into window
  for (i = 0; i < 224; i++) {
    for (j = 0; j < 256; j+=8) {
      int p;
      // Read first 1-bit pixel, divide by 8 bc 8 pixels in byte
      unsigned char pix = videoMemory[(i * (256/8)) + j/8];

      // 8 output vertical pixels --> vertical flip, j start at last line
      int offset = (255-j)*(224*4) + (i*4);
      unsigned int *p1 = (unsigned int *)(&windowPixels[offset]);
      for (p = 0; p < 8; p++) {
	if (0 != (pix & (1 << p))) { // white pixel
	  *p1 = RGB_ON;
	}
	else
	  *p1 = RGB_OFF;
	p1 -= 224;	
      }
    }
  }
}

/* ------------------------ RENDER FUNCTIONS -------------------//

  /*
    QUICK NOTE ON RENDERING:

    https://stackoverflow.com/questions/5829881/avoid-waiting-on-swapbuffers
    https://askubuntu.com/questions/331499/xorg-compiz-is-using-massive-amounts-of-cpu-what-to-do

    
   */

void render_invaders(State8080_T state, unsigned char *windowPixels, GLFWwindow *window) {
  // ADDS A LOCK ON RENDERING  
  usleep(16000);

  // POPULATE WINDOW WITH IN-MEMORY VIDEO RAM, (effective 60hz draw)
  populateWindowFromMemoryInvaders(state, windowPixels);
  
  // RENDER SCREEN
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glRasterPos2f(-1, 1); // IMPORTANT FOR STARTING AT 0, 0
  glPixelZoom(1 * 2, -1 * 2);   // MIRROR IMAGE, and ZOOM IN, to window size
  
  glDrawPixels(W_internal, H_internal, GL_RGBA, GL_UNSIGNED_BYTE, windowPixels);
  
  glfwSwapBuffers(window);
}

void render_laguna(State8080_T state, unsigned char *windowPixels, GLFWwindow *window) {
  // ADDS A LOCK ON RENDERING  
  usleep(16000);

  // POPULATE WINDOW WITH IN-MEMORY VIDEO RAM, (effective 60hz draw)
  populateWindowFromMemoryInvaders(state, windowPixels); // also horizontal
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glRasterPos2f(1, -1); // IMPORTANT FOR STARTING AT 0, 0
  glPixelZoom(-1 * 2, 2);    // ZOOM IN, to window size
  
  glDrawPixels(W_internal, H_internal, GL_RGBA, GL_UNSIGNED_BYTE, windowPixels);
  
  glfwSwapBuffers(window);
}


// ------------------------ GET RENDER FUNCTION -------------------//

/*void (*render_function(ROM rom))(State8080_T,
				 unsigned char *,
				 GLFWwindow *) {*/
render_func render_function(ROM rom) {
  switch (rom) {
  case INVADERS:
    return &render_invaders;
  case LAGUNA: // THIS GAME WILL NOT RUN STILL (REQUIRES PADDLE/JOYSTICK/PEDAL)
    return &render_laguna;
  default:
    return &render_invaders;
  }
}
