#pragma once

#include <memory>
#include <android/asset_manager.h>
#include <android/log.h>

#include "BitmapFont.h"

struct AAssetManager;

class BitmapFont;

class FontManager {
public:

    static FontManager &instance();

    bool initialize(
            AAssetManager *assetManager);

    BitmapFont *getDefaultFont();

private:

    FontManager();

    std::unique_ptr<BitmapFont> mDefaultFont;
};