#include "pxw/File.hpp"

#include <cstring>
#include <cstdio>
#include <SDL2/SDL.h>

#ifdef BUG_FIXES
#define DIR_PATH_SIZE 0x100
#else
#define DIR_PATH_SIZE 0x400
#endif

// Where the base directoy is.
char _path_dir_master_base[DIR_PATH_SIZE] = { 0 };

// Where the common directoy is.
char _path_dir_master_cmmn[DIR_PATH_SIZE] = { 0 };

// Where the resource path is.
char _path_dir_trns[DIR_PATH_SIZE] = { 0 };

std::size_t pxwFile_set_master_base_dir(const char* dir)
{

    // Find base path.
    char* basePath;
    char firstChar;
#ifdef BUG_FIXES
    if (strlen(dir) == 0 || dir[0] == '/')
#else
    if (firstChar = dir[0], firstChar == '/')
#endif
    {
#ifdef BUG_FIXES
        firstChar = '/';
#endif
        basePath = "";
    }
    else
    {
        basePath = SDL_GetBasePath();
        if (!basePath) return 0;
        size_t basePathLen = strlen(basePath);
        if (basePath[basePathLen - 1] == '/')
        {
            basePath[basePathLen - 1] = 0;
        }
    }

    // Set base path.
    int len = snprintf(_path_dir_master_base, 0x400, "%s/%s", basePath, dir);
    // TODO: INODE STUFF???
    if (firstChar != '/') SDL_free(basePath);
    return (std::size_t)len;

}

bool pxwFile_create_trns_sub_dir(const char* dir)
{
    bool pathValid = _path_dir_trns[0] != 0;
    if (pathValid)
    {
        char path[DIR_PATH_SIZE];
        bzero(path, DIR_PATH_SIZE);
        snprintf(path, DIR_PATH_SIZE, "%s/%s", _path_dir_trns, dir);
        // TODO: INODE STUFF!!!
    }
    else return pathValid;
}

bool pxwFile_get_real_path_master_base(char* outRealPath, const char* dir, const char* file)
{
    bool pathValid = _path_dir_master_base[0] != 0;
    if (pathValid)
    {
        if (dir)
            snprintf(outRealPath, 0x104, "%s/%s/%s", _path_dir_master_base, dir, file);
        else
            snprintf(outRealPath, 0x104, "%s/%s", _path_dir_master_base, file);
    }
    return pathValid;
}

bool pxwFile_get_real_path_master_cmmn(char* outRealPath, const char* dir, const char* file)
{
    bool pathValid = _path_dir_master_cmmn[0] != 0;
    if (pathValid)
    {
        if (dir)
            snprintf(outRealPath, 0x104, "%s/%s/%s", _path_dir_master_cmmn, dir, file);
        else
            snprintf(outRealPath, 0x104, "%s/%s", _path_dir_master_cmmn, file);
    }
    return pathValid;
}

bool pxwFile_get_real_path_trns(char* outRealPath, const char* dir, const char* file)
{
    bool pathValid = _path_dir_trns[0] != 0;
    if (pathValid)
    {
        if (dir)
            snprintf(outRealPath, 0x104, "%s/%s/%s", _path_dir_trns, dir, file);
        else
            snprintf(outRealPath, 0x104, "%s/%s", _path_dir_trns, file);
    }
    return pathValid;
}