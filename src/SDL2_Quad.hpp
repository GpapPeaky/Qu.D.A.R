#pragma once

#include "../ThirdParty/SDL2/include/SDL2/SDL.h"

#include "SDL2_Camera.hpp"

#include <cmath>                /* std::roundf(...) */
#include <algorithm>            /* std::sort(...) */
#include <vector>               /* std::vector<t> */

/* Minimum quad size, affects the LOD */
#define SDL2_MIN_QUAD_SIZE 2

/* Max quads to create */
#define SDL2_MAX_QUADS 32768 * 2

/**
 * Quad object, these will be used to 
 * split uniform colored artifacts inside
 * a bitmap
 */
typedef struct SDL2_Quad{
    SDL_Rect pos;               /* Quad position and dimensions */
    SDL_Color color;            /* Quad color */
}SDL2_Quad;

/* Quads created */
extern SDL2_Quad SDL2_Quads[SDL2_MAX_QUADS];

/* Quad count */
extern int SDL2_QuadCount;

/* Debug boolen */
extern bool SDL2_QuadOutlines;

/**
 * @brief Checks if 2 colors are the same
 * 
 * @param c1 Color 1
 * @param c2 Color 2
 * @param tolerance Tolerance for color difference
 * 
 * @returns true if the colors are the same
 * false if not
 */
bool SDL2_SameColor(SDL_Color c1, SDL_Color c2, int tolerance);

/**
 * @brief Get the colour of the pixel 
 * 
 * @param src Source to read from
 * @param x X coordinate of pixel
 * @param y Y coordinate of pixel
 * 
 * @returns The found color
 */
SDL_Color SDL2_GetPixel(SDL_Surface* src, int x, int y);

/**
 * @brief Check if a region/artifact is uniform in color
 * 
 * @param src Source to read from 
 * @param x Artifact x coordinate
 * @param y Artifact y coordinate
 * @param w Artifact width
 * @param h Artifact height
 * @param outColor Colour to write
 * 
 * @returns true if the artifact is uniform,
 * false if not
 */
bool SDL2_IsRegionUniform(SDL_Surface* src, int x, int y, int w, int h, SDL_Color* outColor);

/**
 * @brief Recursive quad tree function
 * 
 * @param src Source to read from
 * @param x Artifact x coordinate
 * @param y Artifact y coordinate
 * @param w Artifact width
 * @param h Artifact height
 */
void SDL2_Quadtree(SDL_Surface* src, int x, int y, int w, int h);

/**
 * @brief Render created quads
 */
void SDL2_RenderQuads(void);

/**
 * @brief Check if two quads can be merged horizontally
 * 
 * @param a First quad
 * @param b Second quad
 * 
 * @returns true if the quads can be merged horizontally, false otherwise
 */
bool SDL2_CanMergeHorizontal(const SDL2_Quad &a, const SDL2_Quad &b);

/**
 * @brief Merge two horizontally adjacent quads into one
 * 
 * @param a First quad
 * @param b Second quad
 * 
 * @returns A new SDL2_Quad representing the merged horizontal quad
 */
SDL2_Quad SDL2_MergeHorizontal(const SDL2_Quad &a, const SDL2_Quad &b);

/**
 * @brief Check if two quads can be merged vertically
 * 
 * @param a First quad
 * @param b Second quad
 * 
 * @returns true if the quads can be merged vertically, false otherwise
 */
bool SDL2_CanMergeVertical(const SDL2_Quad &a, const SDL2_Quad &b);

/**
 * @brief Merge two vertically adjacent quads into one
 * 
 * @param a First quad
 * @param b Second quad
 * 
 * @returns A new SDL2_Quad representing the merged vertical quad
 */
SDL2_Quad SDL2_MergeVertical(const SDL2_Quad &a, const SDL2_Quad &b);

/**
 * @brief Perform post-processing to merge all possible quads
 */
void SDL2_MergeQuads(void);

