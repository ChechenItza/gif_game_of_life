#include "stdafx.h"
#include "universe.h"
#include "rand.h"
#include <assert.h>

universe::universe(int width, int height) :
    w(width), h(height), data1(w*h, false), data2(data1), flipped(false)
{
}

universe::cell_ref universe::operator()(int x, int y)
{
	return data()[cell_offset(x, y)];
}

bool universe::get(int x, int y)
{
	return rangecheck(x, y) ? (*this)(x, y) : false;
}

void universe::set(int x, int y)
{
	set(x, y, true);
}

void universe::set(int x, int y, bool value)
{
	if (rangecheck(x, y)) (*this)(x, y) = value;
}

void universe::unset(int x, int y)
{
	set(x, y, false);
}

void universe::next_gen()
{
	data_array& data = this->data();
	data_array& dest = this->dest();

	size_t offset = 0; // чтобы постоянно не пересчитывать... можно сделать итератор
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++, offset++)
		{
			bool alive = data[offset];
			int neighbors = alive_neighbors(x, y, offset);
			dest[offset] = cell_will_live(alive, neighbors);
		}

	assert(offset == w*h);
	flipped = !flipped;
}

void universe::fill_at_random()
{
	data_array& data = this->data();
	std::fill(data.begin(), data.end(), false);

	for (int y = 0; y < h; y++)
	{
		int n = rnd::randomize(w / 2);

		for (int i = 0; i < n; i++)
			set(rnd::randomize(w), y);
	}
}

universe::data_array& universe::data()
{
	return flipped ? data2 : data1;
}

universe::data_array& universe::dest()
{
	return flipped ? data1 : data2;
}

bool universe::rangecheck(int x, int y)
{
	return x >= 0 && y >= 0 && x < w && y < h;
}

std::size_t universe::cell_offset(int x, int y)
{
	return y * w + x;
}

int universe::alive_neighbors(int x, int y, size_t offset)
{
	assert(offset == cell_offset(x, y));
	data_array& data = this->data();
	bool lt = x > 0, rt = x + 1 < w, up = y > 0, dn = y + 1 < h;
	int count = 0;

	if (lt && data[offset-1 /*x-1, y*/]) count++;
	if (up && data[offset-w /*x, y-1*/]) count++;
	if (rt && data[offset+1 /*x+1, y*/]) count++;
	if (dn && data[offset+w /*x, y+1*/]) count++;
	if (lt && up && data[offset-w-1 /*x-1, y-1*/]) count++;
	if (lt && dn && data[offset+w-1 /*x-1, y+1*/]) count++;
	if (rt && up && data[offset-w+1 /*x+1, y-1*/]) count++;
	if (rt && dn && data[offset+w+1 /*x+1, y+1*/]) count++;
	return count;
}

bool universe::cell_will_live(bool alive_itself, int alive_neighbors)
{
	return alive_itself ? alive_neighbors == 2 || alive_neighbors == 3
	                    : alive_neighbors == 3;
}
