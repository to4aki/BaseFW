#include "TextConsole.h"

TextConsole::TextConsole()
{
    clear();
}

void TextConsole::clear()
{
    std::memset(
            vram_,
            ' ',
            sizeof(vram_));

    cursorX_ = 0;
    cursorY_ = 0;
}

void TextConsole::locate(
        int x,
        int y)
{
    cursorX_ = x;
    cursorY_ = y;

    if(cursorX_ < 0)
    {
        cursorX_ = 0;
    }

    if(cursorX_ >= COLS)
    {
        cursorX_ = COLS - 1;
    }

    if(cursorY_ < 0)
    {
        cursorY_ = 0;
    }

    if(cursorY_ >= ROWS)
    {
        cursorY_ = ROWS - 1;
    }
}

void TextConsole::putChar(
        char ch)
{
    if(ch == '\r')
    {
        return;
    }

    if(ch == '\n')
    {
        cursorX_ = 0;
        cursorY_++;

        if(cursorY_ >= ROWS)
        {
            scroll();
        }

        return;
    }

    vram_[cursorY_][cursorX_] =
            ch;

    cursorX_++;

    if(cursorX_ >= COLS)
    {
        cursorX_ = 0;
        cursorY_++;

        if(cursorY_ >= ROWS)
        {
            scroll();
        }
    }
}

void TextConsole::putString(
        const std::string& text)
{
    for(char ch : text)
    {
        putChar(ch);
    }
}

void TextConsole::scroll()
{
    for(int y = 1;
        y < ROWS;
        y++)
    {
        for(int x = 0;
            x < COLS;
            x++)
        {
            vram_[y - 1][x] =
                    vram_[y][x];
        }
    }

    for(int x = 0;
        x < COLS;
        x++)
    {
        vram_[ROWS - 1][x] =
                ' ';
    }

    cursorY_ =
            ROWS - 1;
}

void TextConsole::draw(
        FrameBuffer& fb,
        int baseX,
        int baseY)
{
    char str[2];

    str[1] = 0;

    for(int y = 0;
        y < ROWS;
        y++)
    {
        for(int x = 0;
            x < COLS;
            x++)
        {
            str[0] =
                    vram_[y][x];

            Draw::drawString(
                    fb,
                    baseX + x * 8,
                    baseY + y * 8,
                    str,
                    Color::WHITE,
                    Color::BLACK);
        }
    }
}