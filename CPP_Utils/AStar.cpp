#include <AStar.h>
#include <algorithm>

using namespace std;

bool CompareNodeOnHeuristic(Node a, Node b)
{
	return a.heuristic < b.heuristic;
}

vector<vector<size_t>> SimpleGetNeighbours(const vector<string>& map, const vector<size_t> pos)
{
	vector<vector<size_t>> neighbours;
	if (pos[0] > 0)
	{
		neighbours.push_back({ pos[0] - 1,pos[1] });
	}
	if (pos[1] > 0)
	{
		neighbours.push_back({ pos[0],pos[1] - 1 });
	}
	if (pos[0] < map[pos[1]].size() - 1)
	{
		neighbours.push_back({ pos[0] + 1,pos[1] });
	}
	if (pos[1] < map.size() - 1)
	{
		neighbours.push_back({ pos[0],pos[1] + 1 });
	}
	return neighbours;
}
