#include "auxf/includes.aux"

int main(int argc, char* argv[]){
    SDL2_InitWin(); /* Initialise */

    SDL2_Cam = SDL2_NewCamera();
    
    /* NOTE: It is preferable the image dimensions are a power of 2 for more accurate artifacts */
    /* NOTE: Image complexity will affect the output */
    /* TODO: Add LOD reduction when zooming too far out */
    SDL2_Bitmap* bp = SDL2_NewBitmap("assets/gfx/quads.bmp");
    SDL2_RecalibrateBitmapSizeAspectRatioLocked(bp, SDL2_WinWidth);

    SDL2_Quadtree(bp->srfc, 0, 0, bp->srfc->w, bp->srfc->h);
    std::printf("Generated %d quads\n", SDL2_QuadCount);
    SDL2_MergeQuads();
    std::printf("Post processing created %d quads\n", SDL2_QuadCount);

    bool SDL2_Quit = false;
    while(!SDL2_Quit){
        SDL2_HandleEvents(SDL2_Quit); /* Creates a new event to poll per call (Might need to be optimised) */

        /* Updates to assets / sprites */

        SDL_RenderClear(SDL2_Rnd);

        // SDL2_RenderBitmap(bp);
        SDL2_RenderQuads();

        SDL_RenderPresent(SDL2_Rnd);
    }

    SDL2_FreeCamera();
    SDL2_FreeBitmap(bp);

    SDL_DestroyRenderer(SDL2_Rnd);
    SDL_DestroyWindow(SDL2_Win);
    IMG_Quit();
    SDL_Quit();

    return SUCCESS;
}
