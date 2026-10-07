#include "FontManager.h"

FontManager&
FontManager::instance()
{
    static FontManager mgr;
    return mgr;
}

FontManager::FontManager()
{
}

bool FontManager::initialize(
        AAssetManager* assetManager)
{
    AAsset* asset =
            AAssetManager_open(
                    assetManager,
//                    "fonts/HackNerdFont-Bold.ttf",
                    "fonts/GenJyuuGothicL-Monospace-Bold.ttf",
//                    "fonts/Hack-Bold.ttf",
//                    "fonts/DotGothic16-Regular.ttf",
                    AASSET_MODE_BUFFER);

    if (!asset)
    {
        __android_log_print(
                ANDROID_LOG_ERROR,
                "FONT",
                "DotGothic16.ttf open failed");

        return false;
    }

    const auto size =
            AAsset_getLength(asset);

    std::vector<uint8_t> buffer(size);

    AAsset_read(
            asset,
            buffer.data(),
            size);

    AAsset_close(asset);

    mDefaultFont =
            std::make_unique<BitmapFont>();

    bool result =
            mDefaultFont->load(
                    buffer.data(),
                    buffer.size(),
                    28.0f);

    Glyph glyph;

    bool ok =
            mDefaultFont->buildGlyph(
                    'A',
                    glyph);

    __android_log_print(
            ANDROID_LOG_ERROR,
            "FONT",
            "build=%d size=%dx%d",
            ok,
            glyph.width,
            glyph.height);

    return result;
}

BitmapFont*
FontManager::getDefaultFont()
{
    return mDefaultFont.get();
}