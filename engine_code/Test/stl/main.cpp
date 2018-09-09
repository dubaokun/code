#include <iostream>
#include <deque>

main ()
{
  unsigned int i;
  std::deque<int> foo (3,100);   // three ints with a value of 100
  std::deque<int> bar (5,200);   // five ints with a value of 200

	std::cout << "before foo contains:";
  for (std::deque<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  std::cout << "before bar contains:";
  for (std::deque<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';


  foo.swap(bar);

  std::cout << "swap foo contains:";
  for (std::deque<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  std::cout << "swap bar contains:";
  for (std::deque<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
