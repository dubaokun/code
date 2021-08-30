#include <iostream>

using namespace std;

int main(void)
{
  int matrix[4][3] = {{1,2,3},{4,5,6},{7,8,9},{10,11,12}};

  for(int i = 0; i < 3; ++i)
  {
      if(i % 2 == 0) {
        for(int j = 0; j < 4; ++j) {
            cout << matrix[j][i] << " ";
          }
      }
      else {
        for(int j = 3; j >=0; --j) {
            cout << matrix[j][i] << " ";
        }
      }
  }
  cout << endl;
  return 0;
}
