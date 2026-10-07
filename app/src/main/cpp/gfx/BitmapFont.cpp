#include "BitmapFont.h"

static Glyph gEmptyGlyph;

BitmapFont::BitmapFont()
{
    mFontInfo = nullptr;
    mPixelHeight = 16.0f;
    mLoaded = false;
}

bool BitmapFont::load(
        const uint8_t* data,
        size_t size,
        float pixelHeight)
{
    mFontData.assign(
            data,
            data + size);

    mFontInfo = new stbtt_fontinfo();

    if (!stbtt_InitFont(
            mFontInfo,
            mFontData.data(),
            0))
    {
        delete mFontInfo;
        mFontInfo = nullptr;
        return false;
    }

    mPixelHeight = pixelHeight;
    mLoaded = true;

    int lineGap;

    stbtt_GetFontVMetrics(
            mFontInfo,
            &mAscent,
            &mDescent,
            &lineGap);

    return true;
}

bool BitmapFont::isLoaded() const
{
    return mLoaded;
}

bool BitmapFont::buildGlyph(
        uint32_t codepoint,
        Glyph& glyph)
{
    if (!mLoaded)
    {
        return false;
    }

    float scale =
            stbtt_ScaleForPixelHeight(
                    mFontInfo,
                    mPixelHeight);

    int width;
    int height;
    int xoff;
    int yoff;

    auto* bmp =
            stbtt_GetCodepointBitmap(
                    mFontInfo,
                    0,
                    scale,
                    codepoint,
                    &width,
                    &height,
                    &xoff,
                    &yoff);

    if (!bmp)
    {
        return false;
    }

    int advance;
    int lsb;

    stbtt_GetCodepointHMetrics(
            mFontInfo,
            codepoint,
            &advance,
            &lsb);

    glyph.width = width;
    glyph.height = height;

    glyph.xoff = xoff;
    glyph.yoff = yoff;

    glyph.advance =
            static_cast<int>(
                    advance * scale);

    glyph.bitmap.assign(
            bmp,
            bmp + width * height);

    stbtt_FreeBitmap(
            bmp,
            nullptr);

    return true;
}

char pixelToChar(
        uint8_t value)
{
    if (value > 220) return '#';
    if (value > 180) return 'O';
    if (value > 120) return '+';
    if (value >  60) return '.';

    return ' ';
}

bool BitmapFont::dumpGlyph(
        uint32_t codepoint)
{
    const Glyph& glyph =
            getGlyph(codepoint);

    __android_log_print(
            ANDROID_LOG_ERROR,
            "FONT",
            "U+%04X size=%dx%d",
            codepoint,
            glyph.width,
            glyph.height);

    for (int y = 0;
         y < glyph.height;
         y++)
    {
        std::string line;

        for (int x = 0;
             x < glyph.width;
             x++)
        {
            uint8_t pixel =
                    glyph.bitmap[
                            y * glyph.width + x];

            line += pixelToChar(pixel);

        }

        __android_log_print(
                ANDROID_LOG_ERROR,
                "FONT",
                "%s",
                line.c_str());
    }

    return true;
}

const Glyph&
BitmapFont::getGlyph(
        uint32_t codepoint)
{
    auto it =
            mGlyphCache.find(
                    codepoint);

    if (it != mGlyphCache.end())
    {
        return it->second;
    }

    Glyph glyph;

    if (!buildGlyph(
            codepoint,
            glyph))
    {
        return gEmptyGlyph;
    }

    auto result =
            mGlyphCache.emplace(
                    codepoint,
                    std::move(glyph));

    return result.first->second;
}

int BitmapFont::getBaseline() const
{
    if (!mFontInfo)
    {
        return 0;
    }

    float scale =
            stbtt_ScaleForPixelHeight(
                    mFontInfo,
                    mPixelHeight);

    return static_cast<int>(
            mAscent * scale);
}