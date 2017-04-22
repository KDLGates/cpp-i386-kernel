#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <stddef.h>
#include <stdint.h>

#include <inline_asm.hpp>

#include <string.hpp>
#include <basic_string_view.hpp>
#include <algorithm.hpp>

struct vga_index_register {
    static constexpr auto low_byte = 15u;
    static constexpr auto high_byte = 14u;
    static constexpr auto underline_location = 0x3D4u; 
};

enum class color : uint8_t {
	black = 0,
	blue = 1,
	green = 2,
	cyan = 3,
	red = 4,
	magenta = 5,
	brown = 6,
	light_grey = 7,
	dark_grey = 8,
	light_blue = 9,
	light_green = 10,
	light_cyan = 11,
	light_red = 12,
	light_magenta = 13,
	light_brown = 14,
	white = 15,
};

struct colored_char {
    char code_byte;
    color attribute;

    operator uint16_t() const {
        return (code_byte |
            static_cast<uint16_t>(attribute) << 8);
    }
};
 
class Terminal {
    size_t row_;
    size_t column_;
    color color_;
    uint16_t *buffer_;
public:
    Terminal() 
        : row_(0), column_(0),
          color_(make_color(color::white, color::black)),
          buffer_(reinterpret_cast<uint16_t*>(0xB8000))
    { 
        clear();
    }

    static constexpr size_t columns = 80;
    static constexpr size_t rows = 25;

    static color make_color(color fg, color bg) {
        return static_cast<color>(
                static_cast<uint8_t>(fg) 
                | (static_cast<uint8_t>(bg) << 4)
            );
    }
    
    static colored_char make_colored_char(char code_byte, color attribute) {
        return { code_byte, attribute };
    }

    void set_color(color c) {
        color_ = c;
    }

    void write_char_at(char c, color color, size_t x, size_t y) {
        const size_t index = y * columns + x;
        buffer_[index] = make_colored_char(c, color);
    }

    void put_char(char c) {
        if (c == '\n') {
            column_ = 0;
            row_++;
        } else {
            write_char_at(c, color_, column_, row_);
            column_++;
        }

        if (column_ == columns) {
            column_ = 0;
            ++row_;
        }

        if (row_ == rows) {
            row_ = rows - 1;

            // Copy each line upwards
            for (auto y = 0u; y < rows; y++) {
                auto next_line_start    = (y + 1) * columns;
                auto next_line_end      = ((y + 1) * columns) + columns;
                auto current_line_start = y * columns;

                copy(buffer_ + next_line_start,
                        buffer_ + next_line_end,
                        buffer_ + current_line_start);
            }

            clear_line(rows - 1);

            
        }

        move_cursor();
    }
    
    void write(string_view data) {
        for (size_t i = 0; i < data.length(); i++) {
            put_char(data[i]);
        }
    }

    void clear() {
        for (auto y = 0u; y < rows; ++y) {
            for (auto x = 0u; x < columns; ++x) {
                write_char_at(' ', make_color(color::white, color::black), x, y);
            }
        }
    }

    void clear_line(size_t row) {
        for (auto x = 0u; x < columns; ++x) {
            write_char_at(' ', make_color(color::white, color::black), x, row);
        }
    }

    void move_cursor() {
        auto position = (row_ * columns) + column_;

        outb(vga_index_register::underline_location, vga_index_register::high_byte);
        outb(vga_index_register::underline_location + 1, static_cast<uint8_t>(position >> 8));

        outb(vga_index_register::underline_location, vga_index_register::low_byte);
        outb(vga_index_register::underline_location + 1, static_cast<uint8_t>(position));
    }
};

#endif
