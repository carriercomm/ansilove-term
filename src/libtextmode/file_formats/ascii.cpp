#include "../textmode.h"
#include "ascii.h"
#include "screen.h"

image_data_t read_ascii_file(file_t& file, const size_t& file_size)
{
    serial_screen_t screen;
    uint8_t code;
    for(size_t i = 0; i < file_size; ++i)
    {
        code = file.read_byte();
        switch(code)
        {
        case '\n':
            screen.new_line();
            break;
        case '\r':
            break;
        default:
            screen.putc(code);
            break;
        }
    }

    return screen.get_image_data();
}

ascii_t::ascii_t(const std::string& filename)
    : textmode_t(filename)
{
    file_t file(filename);
    image_data = read_ascii_file(file, sauce.file_size);
    options.palette_type = palette_type_t::none;
    type = textmode_type_t::ascii;
}
