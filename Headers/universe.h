#ifndef UNIVERSE_H
#define UNIVERSE_H
#include <vector>

using std::vector;
using std::size_t;

class universe
{
public:
	// массив размером w*h. хранится по строкам слева направо, т. о. точка с координатами (x, y) лежит в y*w+x.
	typedef vector<bool> data_array;
	typedef data_array::reference cell_ref;

	universe(int, int);
	cell_ref operator()(int x, int y);
	bool get(int x, int y);
	void set(int x, int y);
	void unset(int x, int y);
	void set(int x, int y, bool value);
	void next_gen();
	void fill_at_random();

private:
	const int w, h;
	// в одном из массивов — текущее поколение, в другом — следующее
	data_array data1, data2;
	bool flipped;

	data_array& data();
	data_array& dest();

	bool rangecheck(int x, int y);
	size_t cell_offset(int x, int y);
	int alive_neighbors(int x, int y, size_t offset);
	bool cell_will_live(bool alive_itself, int alive_neighbors);
};

#endif //UNIVERSE_H
