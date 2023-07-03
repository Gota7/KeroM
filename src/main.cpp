#include "px/Error.hpp"
#include "px/File.hpp"
#include "Platform.hpp"
#include <SDL2/SDL.h>

const char* g_app_name_c = "Kero Blaster";

// Main executable.
int main()
{

    // TODO: FIGURE OUT FLAG ENUM!
    if (SDL_Init(SDL_INIT_VIDEO))
    {
#ifdef STEAMWORKS
        // TODO: STEAM CALL!
#endif
    }
    else
    {

        // Setup working directory.
        char* basePath = SDL_GetBasePath();
        if (basePath)
        {
            KeroPlatform::ChangeDir(basePath);
            SDL_free(basePath);
        }

        // TODO: pxmApp_GetApplicationSupport.
        if (pxFile::sttc_set_master_base_dir("rsc_k"))
        {
            // TODO!!!
        }
        else
        {
            // TODO!!!
        }

        // TODO!!!
        return 0;

    }

    // Error handler code.
    // TODO: LOOP STOP GLOBAL!!!
    SDL_ShowSimpleMessageBox(
        SDL_MESSAGEBOX_ERROR,
        g_app_name_c,
        pxError_is_error() ? pxError_get_message() : "FATAL ERROR",
        nullptr
    );
    return 0;

}