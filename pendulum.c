/*******************************************************************************************
*
* Inspiration: https://www.youtube.com/watch?v=NBWMtlbbOag
*
********************************************************************************************/


#include <raylib.h>
#include <math.h>

float get_radian(int degree){
  return degree * (PI/180);
}


int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "raylib - pendulum");
  SetTargetFPS(60);
  int length = 300;
  int degree = 60;
  float angle = get_radian(degree);
  Vector2 starting_point = {400,50};
  Vector2 end_point;
  end_point.x = starting_point.x - length;
  end_point.y = starting_point.y;

  const float g_const = 9.81f;
  const float mass = 1.00f;


  float acc = 0.00f;
  float vel = 0.00f;
  float force = 0.00f;
  float grav_force = mass * g_const;
  
  int frame_counter = 0;

  while (!WindowShouldClose()) {
    acc = -1 * grav_force * sin(angle) / length;
    force = mass * acc;
    vel += force;
    angle += vel;
    end_point.x = starting_point.x + sin(angle)*length ;
    end_point.y = starting_point.y + cos(angle)*length ;
    // if ((degree >= 45) || (degree <= -45)) direction *= -1;
    // if (frame_counter % 2 == 0) degree+=direction;
    
    frame_counter++;
    
    BeginDrawing();
      ClearBackground(BLACK);

      
      DrawLineEx(starting_point, end_point, 5, GOLD);
      DrawCircleV(end_point, 35, GOLD);
      DrawCircleV(end_point, 25, YELLOW);
      // DrawRectangle(100, 100, 200, 200, RED);
      // DrawTriangle(starting_point, end_point, v3, RED);
      DrawFPS(5, 5);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
