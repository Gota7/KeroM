#include "px/Localize.hpp"

#include "px/File.hpp"
#include "px/Mem.hpp"
#include "pxwr/AppEtc.hpp"
#include <cstdio>
#include <cstring>
#include <string>

#define LANGUAGE_DIR_LEN 0x40
#define MAX_REGION_LEN 28

const char* _region_tbl[] =
{
    "ENGLISH",
    "en",
    "JAPANESE",
    "ja",
    "CHINESE",
    "zh-Hans",
    "FRENCH",
    "fr",
    "ITALIAN",
    "it",
    "GERMAN",
    "de",
    "SPANISH",
    "es",
    "PORTUGUES",
    "pt",
    "RUSSIAN",
    "ru"
};

pxLocalize::~pxLocalize()
{
    initialized = false;
    pxStrT_free(&profileDir);
    pxStrT_free(&profileFile);
    pxStrT_free(&localizeDir);
    pxStrT_free(&languageDir);
}

bool pxLocalize::init(const char* profileDir, const char* profileFile, const char* localizeDir)
{
    if (initialized) return false;

    // Get directories.
    if (localizeDir)
    {
        this->localizeDir = pxStrT_copy_allocate(localizeDir);
        if (!this->localizeDir) goto end;
    }
    if (profileDir)
    {
        this->profileDir = pxStrT_copy_allocate(profileDir);
        if (!this->profileDir) goto end;
    }
    if (profileFile)
    {
        this->profileFile = pxStrT_copy_allocate(profileFile);
        if (!this->profileFile) goto end;
    }

    // Get language directory.
    if (pxMem_zero_alloc((void**)&languageDir, LANGUAGE_DIR_LEN))
    {
        unsigned int langId = pxwrAppEtc_Local();
        region = REGION_COUNT;
        if (langId < REGION_COUNT)
        {
            region = (pxLOCALREGION)langId;
        }
        initialized = true;
        sprintf(languageDir, "%s/%s.lproj", this->localizeDir, _region_tbl[region * 2 + 1]);
    }

    // Final check.
end:
    if (initialized) return true;
    else
    {
        pxStrT_free(&this->profileDir);
        pxStrT_free(&this->profileFile);
        pxStrT_free(&this->localizeDir);
        pxStrT_free(&this->languageDir);
        return false;
    }

}

bool pxLocalize::load()
{
    if (!initialized) return false;

    // Read region file.
    pxFile file(false, false);
    if (!file.open(profileDir, profileFile, "rb")) return false;
    int strLen;
    if (!FILE_ITEM_READ(file, strLen)) return false;
    char regionStr[MAX_REGION_LEN] = { 0 };
    if (!FILE_ITEMS_READ(file, regionStr, strLen)) return false;

    // Fetch the proper language.
    std::string sStr(regionStr);
    if (sStr == "ENGLISH")          region = REGION_ENGLISH;
    else if (sStr == "JAPANESE")    region = REGION_JAPANESE;
    else if (sStr == "CHINESE")     region = REGION_CHINESE;
    else if (sStr == "FRENCH")      region = REGION_FRENCH;
    else if (sStr == "ITALIAN")     region = REGION_ITALIAN;
    else if (sStr == "GERMAN")      region = REGION_GERMAN;
    else if (sStr == "SPANISH")     region = REGION_SPANISH;
    else if (sStr == "PORTUGUES")   region = REGION_PORTUGUES;
    else if (sStr == "RUSSIAN")     region = REGION_RUSSIAN;
    sprintf(languageDir, "%s/%s.lproj", this->localizeDir, _region_tbl[region * 2 + 1]);
    return true;

}

bool pxLocalize::save()
{
    if (!initialized) return false;

    // Save region info.
    pxFile file(false, false);
    const char* regionStr = _region_tbl[region * 2];
    if (!file.open(profileDir, profileFile, "wb")) return false;
    int regionLen = (int)strlen(regionStr);
    if (!FILE_ITEM_WRITE(file, regionLen)) return false;
    return FILE_ITEMS_WRITE(file, regionStr, regionLen);

}

bool pxLocalize::set(pxLOCALREGION region)
{
    if (!initialized) return false;
    if (region >= REGION_COUNT) return false;

    // Set region.
    this->region = region;
    sprintf(languageDir, "%s/%s.lproj", this->localizeDir, _region_tbl[region * 2 + 1]);
    return true;

}

bool pxLocalize::set_and_save(pxLOCALREGION region)
{
    if (!set(region)) return false;
    return save();
}

pxLOCALREGION pxLocalize::get()
{
    return region;
}

char* pxLocalize::get_region_dir()
{
    if (initialized)
        return languageDir;
    else
        return nullptr;
}