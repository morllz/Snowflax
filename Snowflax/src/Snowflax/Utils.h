#pragma once


#define COLOR16_FROM_RGB(R, G, B) (uint16_t)((G << 10) & (R << 5) & (B))