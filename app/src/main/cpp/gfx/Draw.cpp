#include "Draw.h"

void Draw::fillRect(
        FrameBuffer& fb,
        int x,
        int y,
        int w,
        int h,
        uint32_t color)
{
    for(int yy = y; yy < y + h; yy++)
    {
        for(int xx = x; xx < x + w; xx++)
        {
            fb.setPixel(
                    xx,
                    yy,
                    color);
        }
    }
}

void Draw::pixel(
        FrameBuffer& fb,
        int x,
        int y,
        uint32_t color)
{
    fb.setPixel(
            x,
            y,
            color);
}

void Draw::line(
        FrameBuffer& fb,
        int x1,
        int y1,
        int x2,
        int y2,
        uint32_t color)
{
    int dx = abs(x2 - x1);
    int sx = x1 < x2 ? 1 : -1;

    int dy = -abs(y2 - y1);
    int sy = y1 < y2 ? 1 : -1;

    int err = dx + dy;

    while(true)
    {
        fb.setPixel(
                x1,
                y1,
                color);

        if(x1 == x2 &&
           y1 == y2)
        {
            break;
        }

        int e2 = 2 * err;

        if(e2 >= dy)
        {
            err += dy;
            x1 += sx;
        }

        if(e2 <= dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void Draw::rect(
        FrameBuffer& fb,
        int x,
        int y,
        int w,
        int h,
        uint32_t color)
{
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
        FrameBuffer& fb,
        int cx,
        int cy,
        int r,
        uint32_t color)
{
    int x = r;
    int y = 0;

    int err = 0;

    while(x >= y)
    {
        fb.setPixel(cx + x, cy + y, color);
        fb.setPixel(cx + y, cy + x, color);
        fb.setPixel(cx - y, cy + x, color);
        fb.setPixel(cx - x, cy + y, color);

        fb.setPixel(cx - x, cy - y, color);
        fb.setPixel(cx - y, cy - x, color);
        fb.setPixel(cx + y, cy - x, color);
        fb.setPixel(cx + x, cy - y, color);

        y++;

        if(err <= 0)
        {
            err += 2 * y + 1;
        }

        if(err > 0)
        {
            x--;
            err -= 2 * x + 1;
        }
    }
}

void Draw::fillCircle(
        FrameBuffer& fb,
        int cx,
        int cy,
        int r,
        uint32_t color)
{
    for(int y = -r; y <= r; y++)
    {
        for(int x = -r; x <= r; x++)
        {
            if((x * x) + (y * y) <= (r * r))
            {
                fb.setPixel(
                        cx + x,
                        cy + y,
                        color);
            }
        }
    }
}

void Draw::hLine(
        FrameBuffer& fb,
        int x1,
        int x2,
        int y,
        uint32_t color)
{
    if(x1 > x2)
    {
        std::swap(x1,x2);
    }

    for(int x=x1;x<=x2;x++)
    {
        fb.setPixel(
                x,
                y,
                color);
    }
}

void Draw::vLine(
        FrameBuffer& fb,
        int x,
        int y1,
        int y2,
        uint32_t color)
{
    if(y1 > y2)
    {
        std::swap(y1,y2);
    }

    for(int y=y1;y<=y2;y++)
    {
        fb.setPixel(
                x,
                y,
                color);
    }
}

void Draw::fillScreen(
        FrameBuffer& fb,
        uint32_t color)
{
    fb.clear(color);
}

void Draw::rect3D(
        FrameBuffer& fb,
        int x,
        int y,
        int w,
        int h,
        uint32_t light,
        uint32_t dark)
{
    hLine(
            fb,
            x,
            x+w,
            y,
            light);

    vLine(
            fb,
            x,
            y,
            y+h,
            light);

    hLine(
            fb,
            x,
            x+w,
            y+h,
            dark);

    vLine(
            fb,
            x+w,
            y,
            y+h,
            dark);
}

void Draw::checker(
        FrameBuffer& fb,
        int cell,
        uint32_t c1,
        uint32_t c2)
{
    for(int y=0;y<fb.height();y++)
    {
        for(int x=0;x<fb.width();x++)
        {
            bool odd =
                    ((x/cell)+(y/cell))
                    & 1;

            fb.setPixel(
                    x,
                    y,
                    odd ? c1 : c2);
        }
    }
}

void Draw::drawChar(
        FrameBuffer& fb,
        int px,
        int py,
        char ch,
        uint32_t fg,
        uint32_t bg)
{
    const uint8_t* glyph =
            font8x8_basic[
                    static_cast<unsigned char>(ch)];

    for(int y = 0; y < 8; y++)
    {
        uint8_t row = glyph[y];

        for(int x = 0; x < 8; x++)
        {
            bool set =
                    (row & (0x80 >> x)) != 0;

            fb.setPixel(
                    px + (7 - x),
                    py + y,
                    set ? fg : bg);
        }
    }
}

void Draw::drawString(
        FrameBuffer& fb,
        int x,
        int y,
        const char* text,
        uint32_t fg,
        uint32_t bg)
{
    while(text[0] != '\0')
    {
        drawChar(
                fb,
                x,
                y,
                text[0],
                fg,
                bg);

        x += 8;

        text++;
    }
}