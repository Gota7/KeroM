#ifdef __linux

#include "Platform.hpp"
#include <unistd.h>

namespace KeroPlatform
{

    int ChangeDir(char* path)
    {
        return chdir(path);
    }

}

#endif