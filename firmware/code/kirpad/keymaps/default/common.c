#include "common.h"
#include OLED_FONT_H

uint8_t rect_out_of_bounds(int16_t x, int16_t y, uint8_t width, uint8_t height, int8_t padding)
{
    /* Return a bit mask representing the direction collission happened.
     * Direction positions are like vim arrow keys: <left><down><up><right>
     */
    uint8_t collision_map = 0x00;
    if (x < -padding)
    {
        collision_map |= COLLISION_MASK_LEFT;
    }
    if ((x + width) >= (OLED_DISPLAY_WIDTH + padding))
    {
        collision_map |= COLLISION_MASK_RIGHT;
    }
    if (y < -padding)
    {
        collision_map |= COLLISION_MASK_UP;
    }
    if ((y + height) >= (OLED_DISPLAY_HEIGHT + padding))
    {
        collision_map |= COLLISION_MASK_DOWN;
    }
    return collision_map;
}

bool point_out_of_bounds(int16_t x, int16_t y, int8_t padding)
{
    return rect_out_of_bounds(x, y, 1, 1, padding);
}

static const uint8_t column_masks[8] = {1, 2, 4, 8, 16, 32, 64, 128};

//画像素图片
void oled_draw_bitmap(const uint8_t *data, int16_t x, int16_t y, uint8_t width, uint8_t height, bool invert)
{
    if ((x + width) <= 0 || (x >= OLED_DISPLAY_WIDTH) || (y + height <= 0) || (y >= OLED_DISPLAY_HEIGHT))
    {
        return;
    }
    int16_t draw_x = x;
    int16_t draw_y = y;
    uint8_t draw_w = width;
    uint8_t draw_h = height;
    uint8_t sprite_x = 0;
    uint8_t sprite_y = 0;
    // If partially out of screen, calculate bounds for the visible part;
    if (x < 0)
    {
        draw_x = 0;
        draw_w = x + width;
        sprite_x = -x;
    }
    else if ((x + width) > OLED_DISPLAY_WIDTH)
    {
        draw_w = OLED_DISPLAY_WIDTH - x;
    }
    if (y < 0)
    {
        draw_y = 0;
        draw_h = y + height;
        sprite_y = -y;
    }
    else if ((y + height) > OLED_DISPLAY_HEIGHT)
    {
        draw_h = OLED_DISPLAY_HEIGHT - y;
    }
    uint8_t sprite_y_row_offset = sprite_y / 8;
    uint8_t sprite_y_bit_offset = sprite_y % 8;

    uint8_t total_rows = (height / 8);
    uint8_t n_trailing_row_bits = height % 8;
    if (n_trailing_row_bits > 0)
    {
        total_rows++;
    }
    total_rows -= sprite_y_row_offset;
    // TODO: Check for the case (y % 8 == 0) and just set bytes directly
    for(uint8_t sprite_row_i = 0; sprite_row_i < total_rows; sprite_row_i++)
    {
        uint8_t n_bits = 8;
        uint8_t bit_start = 0;
        bool first_row = (sprite_row_i == 0);
        bool last_row = (sprite_row_i == total_rows - 1);
        if (first_row && sprite_y_bit_offset)
        {
            n_bits = 8 - sprite_y_bit_offset;
            bit_start = sprite_y_bit_offset;
        }
        else if (last_row)
        {
            if ((n_trailing_row_bits > 0) && (n_trailing_row_bits < n_bits))
            {
                n_bits = n_trailing_row_bits;
            }
            if (draw_h < n_bits)
            {
                n_bits = draw_h;
            }
        }
        for(uint8_t sprite_col_i = 0; sprite_col_i < draw_w; sprite_col_i++)
        {
            uint8_t byte = data[((sprite_row_i + sprite_y_row_offset) * width) + sprite_x + sprite_col_i];
            uint8_t canvas_x = draw_x + sprite_col_i;
            for(uint8_t bit_i = 0; bit_i < n_bits; bit_i++)
            {
                if (byte & column_masks[bit_start + bit_i])
                {
                    if(invert)
                    {
                        uint8_t canvas_y = draw_y + bit_i;
                        if (!point_out_of_bounds(canvas_x, canvas_y, 0))
                        {
                            oled_write_pixel(canvas_x, canvas_y, false);
                        }
                    }
                    else
                    {
                        uint8_t canvas_y = draw_y + bit_i;
                        if (!point_out_of_bounds(canvas_x, canvas_y, 0))
                        {
                            oled_write_pixel(canvas_x, canvas_y, true);
                        }
                    }
                }
                else
                {
                    if(invert)
                    {
                        uint8_t canvas_y = draw_y + bit_i;
                        if (!point_out_of_bounds(canvas_x, canvas_y, 0))
                        {
                            oled_write_pixel(canvas_x, canvas_y, true);
                        }
                    }
                    else
                    {
                        uint8_t canvas_y = draw_y + bit_i;
                        if (!point_out_of_bounds(canvas_x, canvas_y, 0))
                        {
                            oled_write_pixel(canvas_x, canvas_y, false);
                        }
                    }
                }
            }
        }
        draw_y += n_bits;
    }
}

//画线
void oled_draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool invert)
{
    uint8_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x2 - x1; //计算坐标增量
    delta_y = y2 - y1;
    uRow = x1;
    uCol = y1;
    if(delta_x > 0)incx = 1; //设置单步方向
    else if(delta_x == 0)incx = 0; //垂直线
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }
    if(delta_y > 0)incy = 1;
    else if(delta_y == 0)incy = 0; //水平线
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }
    if( delta_x > delta_y)distance = delta_x; //选取基本增量坐标轴
    else distance = delta_y;
    for(t = 0; t <= distance + 1; t++ ) //画线输出
    {
        if(invert)
        {
            oled_write_pixel(uRow, uCol, false); //画点
        }
        else
        {
            oled_write_pixel(uRow, uCol, true); //画点
        }

        xerr += delta_x ;
        yerr += delta_y ;
        if(xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }
        if(yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}

void oled_draw_rectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool invert)
{
    if(x1 < x2 && y1 < y2)
    {
        if(x1 < OLED_DISPLAY_WIDTH && x2 < OLED_DISPLAY_WIDTH && y1 < OLED_DISPLAY_HEIGHT && y2 < OLED_DISPLAY_HEIGHT)
        {
            oled_draw_line(x1, y1, x2, y1, invert);
            oled_draw_line(x1, y1, x1, y2, invert);
            oled_draw_line(x2, y1, x2, y2, invert);
            oled_draw_line(x1, y2, x2, y2, invert);
        }
    }
}

uint8_t *oled_val;
void oled_draw_string(uint8_t x, uint8_t y, uint8_t *str, uint8_t len, bool invert)
{
    if(len > 0 && x < (OLED_DISPLAY_WIDTH - (len * OLED_FONT_WIDTH)) && y < (OLED_DISPLAY_HEIGHT - OLED_FONT_HEIGHT))
    {
        uint8_t x_ = x;
        for(int i = 0; i < len; i++)
        {
            uint8_t buf[6];
            x_ = x + OLED_FONT_WIDTH * i;
            for(int j = 0; j < OLED_FONT_WIDTH; j++)
            {
                buf[j] = pgm_read_byte(&font[str[i] * OLED_FONT_WIDTH + j]);
            }
            oled_draw_bitmap(buf, x_, y, OLED_FONT_WIDTH, OLED_FONT_HEIGHT, invert);
        }
    }
}

static uint16_t oled_pow(uint8_t m, uint8_t n)
{
    uint8_t result = 1;
    while(n--)result *= m;
    return result;
}

static uint8_t num_len(uint16_t n)
{
    uint8_t sum = 0, n_;
    n_ = n;
    while(n_)
    {
        sum++;
        n_ /= 10;
    }
    if(n == 0)
    {
        sum = 1;
    }
    return sum;
}

void oled_draw_num(uint8_t x, uint8_t y, uint16_t num, bool invert)
{

    uint8_t temp;
    uint8_t enshow = 0;
    uint8_t len = num_len(num);

    for(uint8_t t = 0; t < len; t++)
    {
        temp = (num / oled_pow(10, len - t - 1)) % 10;
        if(enshow == 0 && t < (len - 1))
        {
            if(temp == 0)
            {
                if(len > 1)
                {
                    uint8_t val = ' ';
                    oled_draw_string(x + OLED_FONT_WIDTH * t, y, &val, 1, invert);
                    continue;
                }
            }
            else enshow = 1;
        }
        uint8_t val1 = temp + '0';
        oled_draw_string(x + OLED_FONT_WIDTH * t, y, &val1, 1, invert);
    }
}