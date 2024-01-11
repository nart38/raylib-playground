#include <raylib.h>

typedef struct {
  Vector2 pos;
  unsigned int ptrColor;
} FirePixel;

void SpreadFire(FirePixel *pixels, int width, int height) {
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      int rand = GetRandomValue(0, 3);
      int spreadFrom = width * y + x;
      int spreadTo = spreadFrom - width - rand + 1;
      if (spreadTo <= 0) spreadTo = 0;
      if (pixels[spreadFrom].ptrColor <= 0) {
        pixels[spreadTo].ptrColor = 0;
      }
      else /* (pixels[spreadFrom].ptrColor > 0) */ {
        pixels[spreadTo].ptrColor = pixels[spreadFrom].ptrColor - (rand & 1);
      }
    }
  }
}

void DrawPixelFrameBuffer(FirePixel *pixels, Color *palette, int size) {
  for (int i = 0; i < size; i++) {
    DrawPixelV(pixels[i].pos, palette[pixels[i].ptrColor]);
  }
}

int main() {
  int screenWidth = 800;
  int screenHeight = 400;
  char *windowTitle = "OpenGL";
  InitWindow(screenWidth, screenHeight, windowTitle);
  SetTargetFPS(120);

  int colorValues[] = {
      0x070707FF, 0x1F0707FF, 0x2F0F07FF, 0x470F07FF, 0x571707FF, 0x671F07FF,
      0x771F07FF, 0x8F2707FF, 0x9F2F07FF, 0xAF3F07FF, 0xBF4707FF, 0xC74707FF,
      0xDF4F07FF, 0xDF5707FF, 0xDF5707FF, 0xD75F07FF, 0xD75F07FF, 0xD7670FFF,
      0xCF6F0FFF, 0xCF770FFF, 0xCF7F0FFF, 0xCF8717FF, 0xC78717FF, 0xC78F17FF,
      0xC7971FFF, 0xBF9F1FFF, 0xBF9F1FFF, 0xBFA727FF, 0xBFA727FF, 0xBFAF2FFF,
      0xB7AF2FFF, 0xB7B72FFF, 0xB7B737FF, 0xCFCF6FFF, 0xDFDF9FFF, 0xEFEFC7FF,
      0xFFFFFFFF};

  Color colorPalette[37];
  for (int i = 0; i <= 36; i++)
    colorPalette[i] = GetColor(colorValues[i]);

  FirePixel firePixels[screenHeight * screenWidth];
  for (int x = 0; x < screenWidth; x++) {
    for (int y = 1; y < screenHeight; y++) {
      firePixels[screenWidth * y + x].pos.x = x;
      firePixels[screenWidth * y + x].pos.y = y;
      firePixels[screenWidth * y + x].ptrColor = 0;
    }
  }

  for (int x = 0; x < screenWidth; x++) {
    firePixels[(screenHeight - 1) * screenWidth + x].ptrColor = 36;
  }

  while (!WindowShouldClose()) {
    SpreadFire(firePixels, screenWidth, screenHeight);

    BeginDrawing();
    ClearBackground(colorPalette[0]);
    DrawPixelFrameBuffer(firePixels, colorPalette, screenWidth * screenHeight);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
