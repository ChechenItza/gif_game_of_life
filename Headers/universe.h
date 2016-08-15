#ifndef UNIVERSE.H
#define UNVERSE_H

class Universe
{
public:
    Universe(int, int);
    bool* operator[](int);
    void nextGen();

private:
    const int _WIDTH, _HEIGHT;
    bool** _grid;
};

#endif //UNIVERSE_H
