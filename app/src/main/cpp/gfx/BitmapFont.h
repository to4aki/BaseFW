#pragma once

#include <vector>
#include <cstdint>
#include <unordered_map>
#include <android/log.h>

#include "../thirdparty/stb_truetype.h"

struct stbtt_fontinfo;

struct Glyph
{
    int width;
    int height;

    int xoff;
    int yoff;

    int advance;

    std::vector<uint8_t> bitmap;

    static constexpr int CELL_W = 16;
    static constexpr int CELL_H = 16;
};

class BitmapFont
{
public:

    BitmapFont();

    bool load(
            const uint8_t* data,
            size_t size,
            float pixelHeight);

    bool isLoaded() const;

    bool buildGlyph(
            uint32_t codepoint,
            Glyph& glyph);

    bool dumpGlyph(
            uint32_t codepoint);

    const Glyph&
    getGlyph(
            uint32_t codepoint);

    int getHalfWidth() const
    {
        return 8;
    }

    int getFullWidth() const
    {
        return 16;
    }

    int getHeight() const
    {
        return 16;
    }

    int getBaseline() const;

private:

    std::vector<uint8_t> mFontData;

    stbtt_fontinfo* mFontInfo;

    float mPixelHeight;

    bool mLoaded;

    std::unordered_map<
            uint32_t,
            Glyph> mGlyphCache;

    int mAscent = 0;
    int mDescent = 0;
};