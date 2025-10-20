#include "../ThirdParty/SDL2/include/SDL2/SDL.h"

#include "SDL2_Camera.hpp"          /* Camera offset manipulation */

#pragma once

/**
 * @brief Handles main loop events
 * 
 * @param quit Checks if we have quit the main loop
 */
void SDL2_HandleEvents(bool& quit);
