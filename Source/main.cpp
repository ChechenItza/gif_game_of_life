#include <string>
#include <iostream>
#include <Magick++.h>
#include <list>
#include "universe.h"


int main(int argc, const char** argv)
{
//Arguments test
    if (argc != 3 + 1)
        throw;

    int width, height, count;
    try {
        width = std::stoi(argv[1]);
        height = std::stoi(argv[2]);
        count = std::stoi(argv[3]);
    }
    catch (...){
        throw;
    }

//Make gif
    //cell size
    const int cell_size = 10;
    //create container for snapshots
    std::list<Magick::Image> image_list;
    //create universe
    Universe universe(width, height);
    for (int i = 0; i < count; i++) {
        Magick::Image grid_image(Magick::Geometry(width*cell_size, height*cell_size), Magick:: Color("white"));
        grid_image.fillColor("black");
        grid_image.animationDelay(10);
        grid_image.compressType(Magick::BZipCompression);
        grid_image.quality(100);

        //create next generation
        universe.nextGen();
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                //if cell is alive draw it as a black %cell_size sized black rectangle
                if (universe[y][x])
                    grid_image.draw(Magick::DrawableRectangle(y*cell_size,x*cell_size, y*cell_size+cell_size,x*cell_size+cell_size));
            }
        }
        //add snapshot to the container
        image_list.push_back(grid_image);
        std::cout << i << " iterations are completed" << std::endl;
    }
    //animate snapshots and save them as a gif
    Magick::animateImages(image_list.begin(), image_list.end());
    Magick::writeImages(image_list.begin(), image_list.end(), "Output/hey.gif");

    return 0;
}
