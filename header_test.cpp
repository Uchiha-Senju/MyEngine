#include "rotator.h"
#include <iostream>
#include <iomanip>
using namespace std;


int main() {
  AngleAxisRotator<long double> rot(2.0943951, Vector3<double>(1,1,1));
  Vector3 vec = Vector3(2,3,4);
  
  vec = rot * vec;
  cout << "vec = ";
  for (int i = 0; i < 3; ++i)
    cout << setprecision(10) << vec[i] << ", ";
  cout << vec.sqrMagnitude();
  cout << "\n\n";
  
  vec = rot.inverse() * vec;
  cout << "vec = ";
  for (int i = 0; i < 3; ++i)
    cout << setprecision(100) << vec[i] << ", ";
  cout << vec.sqrMagnitude();
  cout << "\n\n";
  
  vec = rot.normalized() * vec;
  cout << "vec = ";
  for (int i = 0; i < 3; ++i)
    cout << setprecision(10) << vec[i] << ", ";
  cout << vec.sqrMagnitude();
  cout << "\n\n";
}
