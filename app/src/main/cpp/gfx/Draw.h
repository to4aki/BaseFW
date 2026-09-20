#pragma once

#include "FrameBuffer.h"
#include "Color.h"
#include "Font8x8.h"

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
            FrameBuffer& fb,
            int x,
            int y,
            char ch,
            uint32_t fg,
            uint32_t bg);

    void drawString(
            FrameBuffer& fb,
            int x,
            int y,
            const char* text,
            uint32_t fg,
            uint32_t bg);
}