#include "SDL2_Quad.hpp"

SDL2_Quad SDL2_Quads[SDL2_MAX_QUADS];

int SDL2_QuadCount;

bool SDL2_QuadOutlines = false;

bool SDL2_SameColor(SDL_Color c1, SDL_Color c2){
    return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b);
}

SDL_Color SDL2_GetPixel(SDL_Surface* src, int x, int y){
    Uint8 *p = (Uint8 *)src->pixels + y * src->pitch + x * src->format->BytesPerPixel;
    Uint32 pixel;
    switch(src->format->BytesPerPixel){
        case 1:
            pixel = *p;
            break;
        case 2:
            pixel = *(Uint16 *)p;
            break;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                pixel = p[0] << 16 | p[1] << 8 | p[2];
            else
                pixel = p[0] | p[1] << 8 | p[2] << 16;
            break;
        default:
            pixel = *(Uint32 *)p;
            break;
    }

    SDL_Color c;
    SDL_GetRGB(pixel, src->format, &c.r, &c.g, &c.b);

    return c;
}

bool SDL2_IsRegionUniform(SDL_Surface* src, int x, int y, int w, int h, SDL_Color* outColor){
    SDL_Color first = SDL2_GetPixel(src, x, y);
    for(int j = y ; j < y + h ; j++){ 
        for(int i = x ; i < x + w ; i++){
            SDL_Color c = SDL2_GetPixel(src, i, j);
            if(!SDL2_SameColor(first, c)){
                return false;
            }
        }
    }
    
    *outColor = first;
    
    return true;
}

void SDL2_Quadtree(SDL_Surface* src, int x, int y, int w, int h){
    if(SDL2_QuadCount >= SDL2_MAX_QUADS) return;

    SDL_Color c;
    if(SDL2_IsRegionUniform(src, x, y, w, h, &c) || w <= SDL2_MIN_QUAD_SIZE || h <= SDL2_MIN_QUAD_SIZE){
        SDL2_Quads[SDL2_QuadCount++] = {x, y, w, h, c};
        return;
    }

    int hw = w / 2;
    int hh = h / 2;

    SDL2_Quadtree(src, x, y, hw, hh);
    SDL2_Quadtree(src, x + hw, y, w - hw, hh);
    SDL2_Quadtree(src, x, y + hh, hw, h - hh);
    SDL2_Quadtree(src, x + hw, y + hh, w - hw, h - hh);

    return;
}

void SDL2_RenderQuads(void){
    for(int i = 0 ; i < SDL2_QuadCount ; i++){
        SDL2_Quad* q = &SDL2_Quads[i];

        // transformedRect.x = (bp->pos.x - (SDL2_Cam->offsetFromCamera.x - SDL2_WinWidth / (2.0f * SDL2_Cam->zoom))) * SDL2_Cam->zoom;
        // transformedRect.y = (bp->pos.y - (SDL2_Cam->offsetFromCamera.y - SDL2_WinHeight / (2.0f * SDL2_Cam->zoom))) * SDL2_Cam->zoom

        SDL_FRect transformed;
        transformed.x = (q->pos.x - (SDL2_Cam->offsetFromCamera.x - SDL2_WinWidth / (2.0f * SDL2_Cam->zoom))) * SDL2_Cam->zoom;
        transformed.y = (q->pos.y - (SDL2_Cam->offsetFromCamera.y - SDL2_WinHeight / (2.0f * SDL2_Cam->zoom))) * SDL2_Cam->zoom;
        transformed.w = q->pos.w * SDL2_Cam->zoom;
        transformed.h = q->pos.h * SDL2_Cam->zoom;

        SDL_FRect cameraRect = {
            (float)SDL2_Cam->cameraRect.x,
            (float)SDL2_Cam->cameraRect.y,
            (float)SDL2_Cam->cameraRect.w,
            (float)SDL2_Cam->cameraRect.h
        };
        
        SDL_FRect r;
        
        /* Render only if in camera */
        if(SDL_IntersectFRect(&transformed, &cameraRect, &r)){
            SDL_SetRenderDrawColor(SDL2_Rnd,
                q->color.r,
                q->color.g,
                q->color.b,
                255);

            if(SDL2_QuadOutlines){
                SDL_RenderDrawRectF(SDL2_Rnd, &transformed);
            }else{
                SDL_RenderFillRectF(SDL2_Rnd, &transformed);
            }
        }

        /* Reset */
        SDL_SetRenderDrawColor(SDL2_Rnd, 0, 0, 0, 0);
    }

    return;
}
