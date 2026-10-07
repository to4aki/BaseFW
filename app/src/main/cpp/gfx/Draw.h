#pragma once

#include "gfx/FrameBuffer.h"
#include "gfx/Color.h"
#include "gfx/BitmapFont.h"
#include "gfx/FontManager.h"

class Glyph;

namespace Draw {
    void pixel(
            FrameBuffer &fb,
            int x,
            int y,
            uint32_t color);

    void line(
            FrameBuffer &fb,
            int x1,
            int y1,
            int x2,
            int y2,
            uint32_t color);

    void rect(
            FrameBuffer &fb,
            int x,
            int y,
            int w,
            int h,
            uint32_t color);

    void fillRect(
            FrameBuffer &fb,
            int x,
            int y,
            int w,
            int h,
            uint32_t color);

    void circle(
            FrameBuffer &fb,
            int cx,
            int cy,
            int radius,
            uint32_t color);

    void fillCircle(
            FrameBuffer &fb,
            int cx,
            int cy,
            int radius,
            uint32_t color);

    void hLine(
            FrameBuffer &fb,
            int x1,
            int x2,
            int y,
            uint32_t color);

    void vLine(
            FrameBuffer &fb,
            int x,
            int y1,
            int y2,
            uint32_t color);

    void fillScreen(
            FrameBuffer &fb,
            uint32_t color);

    void rect3D(
            FrameBuffer &fb,
            int x,
            int y,
            int w,
            int h,
            uint32_t light,
            uint32_t dark);

    void checker(
            FrameBuffer &fb,
            int cell,
            uint32_t c1,
            uint32_t c2);

    void drawChar(
            FrameBuffer &fb,
            int x,
            int y,
            char ch,
            uint32_t fg,
            uint32_t bg);

    void drawString(
            FrameBuffer &fb,
            int x,
            int y,
            const char *text,
            uint32_t fg,
            uint32_t bg);

    void drawGlyph(
            FrameBuffer& fb,
            int px,
            int py,
            const Glyph& glyph,
            int cellW,
            int cellH,
            uint32_t fg,
            uint32_t bg);

    int stringWidth(
            const char* text);
}