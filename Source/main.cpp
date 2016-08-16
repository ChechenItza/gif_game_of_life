#include <string>
#include <iostream>
#include <Magick++.h>
#include <list>
#include "universe.h"

int main(int argc, const char** argv)
{
    if (argc != 3 + 1)
        throw;

    int width, height, count;
    width = std::stoi(argv[1]);
    height = std::stoi(argv[2]);
    count = std::stoi(argv[3]);

    universe universe(width, height);
    universe.fill_at_random();
    
    const int cell_size = 10;
    std::list<Magick::Image> image_list;

    for (int i = 0; i < count; i++)
    {
        Magick::Image grid_image(Magick::Geometry(width*cell_size, height*cell_size), Magick:: Color("white"));
        grid_image.fillColor("black");
        grid_image.animationDelay(10);
        grid_image.compressType(Magick::BZipCompression);
        grid_image.quality(100);

        universe.next_gen();
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (universe(x, y))
                {
                    int base_x = x * cell_size;
                    int base_y = y * cell_size;
                    grid_image.draw(Magick::DrawableRectangle(base_x, base_y, base_x + cell_size - 1, base_y + cell_size - 1));
                }
            }
        }
        image_list.push_back(grid_image);
        std::cout << i << " iterations are completed" << std::endl;
    }
    Magick::animateImages(image_list.begin(), image_list.end());
    Magick::writeImages(image_list.begin(), image_list.end(), "Output/hey.gif");

    return 0;
}
