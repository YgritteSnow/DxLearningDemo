#include "config.h"
#include <math.h>

int g_screen_pixel_width = 800;
int g_screen_pixel_height = 600;
float g_fov = 1.7f;
float g_zmin = 1.0f;
float g_zmax = 100.f;
float g_aspect = (float)g_screen_pixel_width / (float)g_screen_pixel_height;
float g_screen_real_height = 2.f * tan( g_fov / 2.f );
float g_screen_real_width = g_screen_real_height * g_aspect;