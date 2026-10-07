#include "Draw.h"

void Draw::fillRect(
        FrameBuffer &fb,
        int x,
        int y,
        int w,
        int h,
        uint32_t color) {
    for (int yy = y; yy < y + h; yy++) {
        for (int xx = x; xx < x + w; xx++) {
            fb.setPixel(
                    xx,
                    yy,
                    color);
        }
    }
}

void Draw::pixel(
        FrameBuffer &fb,
        int x,
        int y,
        uint32_t color) {
    fb.setPixel(
            x,
            y,
            color);
}

void Draw::line(
        FrameBuffer &fb,
        int x1,
        int y1,
        int x2,
        int y2,
        uint32_t color) {
    int dx = abs(x2 - x1);
    int sx = x1 < x2 ? 1 : -1;

    int dy = -abs(y2 - y1);
    int sy = y1 < y2 ? 1 : -1;

    int err = dx + dy;

    while (true) {
        fb.setPixel(
                x1,
                y1,
                color);

        if (x1 == x2 &&
            y1 == y2) {
            break;
        }

        int e2 = 2 * err;

        if (e2 >= dy) {
            err += dy;
            x1 += sx;
        }

        if (e2 <= dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void Draw::rect(
        FrameBuffer &fb,
        int x,
        int y,
        int w,
        int h,
        uint32_t color) {
    line(
            fb,
            x,
            y,
            x + w,
            y,
            color);

    line(
            fb,
            x,
            y,
            x,
            y + h,
            color);

    line(
            fb,
            x + w,
            y,
            x + w,
            y + h,
            color);

    line(
            fb,
            x,
            y + h,
            x + w,
            y + h,
            color);
}

void Draw::circle(
        FrameBuffer &fb,
        int cx,
        int cy,
        int r,
        uint32_t color) {
    int x = r;
    int y = 0;

    int err = 0;

    while (x >= y) {
        fb.setPixel(cx + x, cy + y, color);
        fb.setPixel(cx + y, cy + x, color);
        fb.setPixel(cx - y, cy + x, color);
        fb.setPixel(cx - x, cy + y, color);

        fb.setPixel(cx - x, cy - y, color);
        fb.setPixel(cx - y, cy - x, color);
        fb.setPixel(cx + y, cy - x, color);
        fb.setPixel(cx + x, cy - y, color);

        y++;

        if (err <= 0) {
            err += 2 * y + 1;
        }

        if (err > 0) {
            x--;
            err -= 2 * x + 1;
        }
    }
}

void Draw::fillCircle(
        FrameBuffer &fb,
        int cx,
        int cy,
        int r,
        uint32_t color) {
    for (int y = -r; y <= r; y++) {
        for (int x = -r; x <= r; x++) {
            if ((x * x) + (y * y) <= (r * r)) {
                fb.setPixel(
                        cx + x,
                        cy + y,
                        color);
            }
        }
    }
}

void Draw::hLine(
        FrameBuffer &fb,
        int x1,
        int x2,
        int y,
        uint32_t color) {
    if (x1 > x2) {
        std::swap(x1, x2);
    }

    for (int x = x1; x <= x2; x++) {
        fb.setPixel(
                x,
                y,
                color);
    }
}

void Draw::vLine(
        FrameBuffer &fb,
        int x,
        int y1,
        int y2,
        uint32_t color) {
    if (y1 > y2) {
        std::swap(y1, y2);
    }

    for (int y = y1; y <= y2; y++) {
        fb.setPixel(
                x,
                y,
                color);
    }
}

void Draw::fillScreen(
        FrameBuffer &fb,
        uint32_t color) {
    fb.clear(color);
}

void Draw::rect3D(
        FrameBuffer &fb,
        int x,
        int y,
        int w,
        int h,
        uint32_t light,
        uint32_t dark) {
    hLine(
            fb,
            x,
            x + w,
            y,
            light);

    vLine(
            fb,
            x,
            y,
            y + h,
            light);

    hLine(
            fb,
            x,
            x + w,
            y + h,
            dark);

    vLine(
            fb,
            x + w,
            y,
            y + h,
            dark);
}

void Draw::checker(
        FrameBuffer &fb,
        int cell,
        uint32_t c1,
        uint32_t c2) {
    for (int y = 0; y < fb.height(); y++) {
        for (int x = 0; x < fb.width(); x++) {
            bool odd =
                    ((x / cell) + (y / cell))
                    & 1;

            fb.setPixel(
                    x,
                    y,
                    odd ? c1 : c2);
        }
    }
}

void Draw::drawChar(
        FrameBuffer &fb,
        int px,
        int py,
        char ch,
        uint32_t fg,
        uint32_t bg) {
    auto *font =
            FontManager::instance()
                    .getDefaultFont();

    if (!font) {
        return;
    }

    bool half =
            static_cast<unsigned char>(ch)
            < 0x80;

    const int cellW =
            half ? 8 : 16;

    const int cellH = 24;

    const Glyph &glyph =
            font->getGlyph(
                    static_cast<unsigned char>(ch));

    drawGlyph(
            fb,
            px,
            py,
            glyph,
            cellW,
            cellH,
            fg,
            bg);
}

static uint32_t nextUtf8(
        const char*& text)
{
    uint8_t c =
            static_cast<uint8_t>(*text++);

    if(c < 0x80)
    {
        return c;
    }

    if((c & 0xE0) == 0xC0)
    {
        uint32_t cp =
                ((c & 0x1F) << 6);

        cp |=
                (*text++ & 0x3F);

        return cp;
    }

    if((c & 0xF0) == 0xE0)
    {
        uint32_t cp =
                ((c & 0x0F) << 12);

        cp |=
                ((*text++ & 0x3F) << 6);

        cp |=
                (*text++ & 0x3F);

        return cp;
    }

    if((c & 0xF8) == 0xF0)
    {
        uint32_t cp =
                ((c & 0x07) << 18);

        cp |=
                ((*text++ & 0x3F) << 12);

        cp |=
                ((*text++ & 0x3F) << 6);

        cp |=
                (*text++ & 0x3F);

        return cp;
    }

    return '?';
}

void Draw::drawString(
        FrameBuffer& fb,
        int x,
        int y,
        const char* text,
        uint32_t fg,
        uint32_t bg)
{
    auto* font =
            FontManager::instance()
                    .getDefaultFont();

    if(!font)
    {
        return;
    }

    while(*text)
    {
        uint32_t codepoint =
                nextUtf8(text);

        const Glyph& glyph =
                font->getGlyph(
                        codepoint);

        drawGlyph(
                fb,
                x,
                y,
                glyph,
                glyph.advance,
                24,
                fg,
                bg);

        x += glyph.advance;
    }
}

void Draw::drawGlyph(
        FrameBuffer &fb,
        int px,
        int py,
        const Glyph &glyph,
        int cellW,
        int cellH,
        uint32_t fg,
        uint32_t bg) {

    const int ox = 0;

    auto *font =
            FontManager::instance()
                    .getDefaultFont();

    int baseline =
            font->getBaseline();

    int oy =
            baseline + glyph.yoff;

    const uint8_t fr =
            (fg >> 16) & 0xff;

    const uint8_t fg_g =
            (fg >> 8) & 0xff;

    const uint8_t fb_b =
            fg & 0xff;

    const uint8_t br =
            (bg >> 16) & 0xff;

    const uint8_t bg_g =
            (bg >> 8) & 0xff;

    const uint8_t bb =
            bg & 0xff;

    for (int y = 0;
         y < glyph.height;
         y++) {
        for (int x = 0;
             x < glyph.width;
             x++) {
            uint8_t alpha =
                    glyph.bitmap[
                            y * glyph.width + x];

            if (alpha == 0) {
                continue;
            }

            uint8_t r =
                    (br * (255 - alpha) +
                     fr * alpha) / 255;

            uint8_t g =
                    (bg_g * (255 - alpha) +
                     fg_g * alpha) / 255;

            uint8_t b =
                    (bb * (255 - alpha) +
                     fb_b * alpha) / 255;

            uint32_t color =
                    (r << 16) |
                    (g << 8) |
                    b;

            fb.setPixel(
                    px + ox + x,
                    py + oy + y,
                    color);
        }
    }
}

int Draw::stringWidth(
        const char* text)
{
    auto* font =
            FontManager::instance()
                    .getDefaultFont();

    if(!font)
    {
        return 0;
    }

    int width = 0;

    while(*text)
    {
        uint32_t codepoint =
                nextUtf8(text);

        const Glyph& glyph =
                font->getGlyph(
                        codepoint);

        width +=
                glyph.advance;
    }

    return width;
}
