#include <iostream>
#include <deque>

using namespace std;

int main(int argc, char ** argv)
{
	std::deque<bool> wtids(1, true);

	cout << wtids.size() << endl;
	
	return 0;
}
