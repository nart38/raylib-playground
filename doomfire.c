/*******************************************************************************************
 *
 * Reccreation of DOOM fire effect in raylib
 *
 * Inspiratons:
 * https://www.youtube.com/watch?v=YJB0gfP-GRY&t=10s
 * https://fabiensanglard.net/doom_fire_psx/
 * https://github.com/const-void/DOOM-fire-zig
 *
 ********************************************************************************************/

#include <raylib.h>

// Pixel type
typedef struct {
  Vector2 pos;              // Position of pixel
  unsigned int ptrColor;    // Pointer to color of pixel in color palette array
} FirePixel;

// Recalculate pixel colors in the pixel frame buffer
// Update frame buffer
// Point is simulating fire particles cooldown as they go up
void SpreadFire(FirePixel *pixels, int width, int height) {
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      int rand = GetRandomValue(
          0, 3);                                      // Using rng to make illusion look more realistic
      int spreadFrom = width * y + x;                 // Current we are in
      int spreadTo = spreadFrom - width - rand + 1;   // Determining the next pixel that fire going to spread

      if (spreadTo <= 0)
        spreadTo = 0;                                 // Checking boundaries
      if (pixels[spreadFrom].ptrColor <= 0) {
        pixels[spreadTo].ptrColor = 0;
      } else {                                        // If not out of bounds spreading fire to the next pixel
        pixels[spreadTo].ptrColor = pixels[spreadFrom].ptrColor - (rand & 1);
      }
    }
  }
}

// Going through frame buffer and drawing evey pixel on screen
void DrawPixelFrameBuffer(FirePixel *pixels, Color *palette, int size) {
  for (int i = 0; i < size; i++) {
    DrawPixelV(pixels[i].pos, palette[pixels[i].ptrColor]);
  }
}

// Program main entry
int main() {

  // Initilazation
  int screenWidth = 800;
  int screenHeight = 400;
  char *windowTitle = "raylib - DOOM fire";
  InitWindow(screenWidth, screenHeight, windowTitle);
  SetTargetFPS(60);

  // Color hex values of fire gradient
  int colorValues[] = {
      0x070707FF, 0x1F0707FF, 0x2F0F07FF, 0x470F07FF, 0x571707FF, 0x671F07FF,
      0x771F07FF, 0x8F2707FF, 0x9F2F07FF, 0xAF3F07FF, 0xBF4707FF, 0xC74707FF,
      0xDF4F07FF, 0xDF5707FF, 0xDF5707FF, 0xD75F07FF, 0xD75F07FF, 0xD7670FFF,
      0xCF6F0FFF, 0xCF770FFF, 0xCF7F0FFF, 0xCF8717FF, 0xC78717FF, 0xC78F17FF,
      0xC7971FFF, 0xBF9F1FFF, 0xBF9F1FFF, 0xBFA727FF, 0xBFA727FF, 0xBFAF2FFF,
      0xB7AF2FFF, 0xB7B72FFF, 0xB7B737FF, 0xCFCF6FFF, 0xDFDF9FFF, 0xEFEFC7FF,
      0xFFFFFFFF};

  // Populating the color palette array with raylib colors
  Color colorPalette[37];
  for (int i = 0; i <= 36; i++)
    colorPalette[i] = GetColor(colorValues[i]);

  // Initilazing pixel frame buffer and filling it with zeros (black)
  FirePixel firePixels[screenHeight * screenWidth];
  for (int x = 0; x < screenWidth; x++) {
    for (int y = 1; y < screenHeight; y++) {
      firePixels[screenWidth * y + x].pos.x = x;
      firePixels[screenWidth * y + x].pos.y = y;
      firePixels[screenWidth * y + x].ptrColor = 0;
    }
  }

  // Filling the bottom line with 36 (white) 
  // which will be our constant fire source
  for (int x = 0; x < screenWidth; x++) {
    firePixels[(screenHeight - 1) * screenWidth + x].ptrColor = 36;
  }

  // Main game loop
  while (!WindowShouldClose()) {
    // Update
    SpreadFire(firePixels, screenWidth, screenHeight);

    // Draw
    BeginDrawing();
    ClearBackground(colorPalette[0]);
    DrawPixelFrameBuffer(firePixels, colorPalette, screenWidth * screenHeight);
    EndDrawing();
  }

  // De-Initialization
  CloseWindow(); // Close window and OpenGL context

  return 0;
}
