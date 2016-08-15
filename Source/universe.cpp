#include "universe.h"
#include "rand.h"

Universe::Universe(int width, int height) :
    _WIDTH{width},
    _HEIGHT{height}
{
    //initialize grid
    _grid = new bool*[_HEIGHT];
    for (int i = 0; i < _HEIGHT; i++) {
        _grid[i] = new bool[_WIDTH];
        for (int x = 0; x < rnd::randomize(_WIDTH / 2); x++) {
            _grid[i][rnd::randomize(_WIDTH)] = 1;
        }
    }
}

bool* Universe::operator[](int y)
{
    return _grid[y];
}

void Universe::nextGen()
{
//Create new generation
    for (int y = 0; y < _HEIGHT; y++) {
        for (int x = 0; x < _WIDTH; x++) {
        //Count neighbour alive cells {{{
            int alive_cells = 0;
            //top-left corner cell
            if (y == 0 && x == 0) {
                alive_cells += _grid[y+1][x];
                alive_cells += _grid[y][x+1];
                alive_cells += _grid[y+1][x+1];
            //bottom-left corner cell
            } else if (y == _HEIGHT - 1 && x == 0) {
                alive_cells += _grid[y-1][x];
                alive_cells += _grid[y][x+1];
                alive_cells += _grid[y-1][x+1];
            //top-right corner cell
            } else if (y == 0 && x == _WIDTH - 1) {
                alive_cells += _grid[y][x-1];
                alive_cells += _grid[y+1][x-1];
                alive_cells += _grid[y+1][x];
            //bottom-right corner cell
            } else if (y == _HEIGHT - 1 && x == _WIDTH - 1) {
                alive_cells += _grid[y][x-1];
                alive_cells += _grid[y-1][x-1];
                alive_cells += _grid[y-1][x];
            //wrap left line cells
            } else if (x == 0) {
                alive_cells += _grid[y+1][_WIDTH-1];
                alive_cells += _grid[y-1][_WIDTH-1];
                alive_cells += _grid[y][_WIDTH-1];

                alive_cells += _grid[y+1][x];
                alive_cells += _grid[y-1][x];
                alive_cells += _grid[y][x+1];
                alive_cells += _grid[y+1][x+1];
                alive_cells += _grid[y-1][x+1];
            //wrap top line cells
            } else if (y == 0) {
                alive_cells += _grid[_HEIGHT-1][x-1];
                alive_cells += _grid[_HEIGHT-1][x];
                alive_cells += _grid[_HEIGHT-1][x+1];

                alive_cells += _grid[y][x-1];
                alive_cells += _grid[y][x+1];
                alive_cells += _grid[y+1][x];
                alive_cells += _grid[y+1][x-1];
                alive_cells += _grid[y+1][x+1];
            //wrap right line cells
            } else if (x == _WIDTH - 1) {
                alive_cells += _grid[y+1][0];
                alive_cells += _grid[y-1][0];
                alive_cells += _grid[y][0];

                alive_cells += _grid[y+1][x];
                alive_cells += _grid[y-1][x];
                alive_cells += _grid[y][x-1];
                alive_cells += _grid[y+1][x-1];
                alive_cells += _grid[y-1][x-1];
            //wrap bottom line cells
            } else if (y == _HEIGHT - 1) {
                alive_cells += _grid[0][x-1];
                alive_cells += _grid[0][x];
                alive_cells += _grid[0][x+1];

                alive_cells += _grid[y][x-1];
                alive_cells += _grid[y][x+1];
                alive_cells += _grid[y][x];
                alive_cells += _grid[y-1][x-1];
                alive_cells += _grid[y-1][x+1];
            //center cells
            } else {
                alive_cells += _grid[y][x-1];
                alive_cells += _grid[y-1][x-1];
                alive_cells += _grid[y+1][x-1];
                alive_cells += _grid[y+1][x];
                alive_cells += _grid[y-1][x];
                alive_cells += _grid[y][x+1];
                alive_cells += _grid[y+1][x+1];
                alive_cells += _grid[y-1][x+1];
            }
        //}}}


        //Apply the rules
            if (!_grid[y][x] && alive_cells == 3)
                _grid[y][x] = true;
            else if (_grid[y][x] && alive_cells > 3)
                _grid[y][x] = false;
            else if (_grid[y][x] && alive_cells >= 2)
                _grid[y][x] = true;
            else if (_grid[y][x] && alive_cells < 2)
                _grid[y][x] = false;
        }
    }
}
