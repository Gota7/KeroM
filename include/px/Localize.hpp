#pragma once

#include "px/StrT.hpp"

// Language enum.
enum pxLOCALREGION : int
{
    REGION_ENGLISH,
    REGION_JAPANESE,
    REGION_CHINESE,
    REGION_FRENCH,
    REGION_ITALIAN,
    REGION_GERMAN,
    REGION_SPANISH,
    REGION_PORTUGUES,
    REGION_RUSSIAN,
    REGION_COUNT
};

// For language related activities.
class pxLocalize
{
    bool initialized = false;
    pxLOCALREGION region = REGION_COUNT;
    char* profileDir = nullptr;
    char* profileFile = nullptr; // Region info file.
    char* localizeDir = nullptr;
    char* languageDir = nullptr;

public:

    // Destructor.
    ~pxLocalize();

    // Initialize from folders.
    bool init(const char* profileDir, const char* profileFile, const char* localizeDir);

    // Load language information.
    bool load();

    // Save language information.
    bool save();

    // Set the local region.
    bool set(pxLOCALREGION region);

    // Set local region and save.
    bool set_and_save(pxLOCALREGION region);

    // Get local region.
    pxLOCALREGION get();

    // Get the directory used for region files.
    char* get_region_dir();

};