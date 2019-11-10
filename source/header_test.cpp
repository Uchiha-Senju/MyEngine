#include "all_math.h"
#include <iostream>
#include <iomanip>
using namespace std;


int main() {
  QuaternionRotator<long double> rot(2.09439510239, Vector3<double>(1,1,1));
  rot = rot.normalized();
  Vector3<long double> vec = Vector3(2,3,4);
  
  vec = (RotationMatrix<long double>)rot * vec;
  cout << "vec = ";
  for (int i = 0; i < 3; ++i)
    cout << setprecision(10) << vec[i] << ", ";
  cout << vec.sqrMagnitude();
  cout << "\n\n";
  
  vec = (AngleAxisRotator<long double>)rot * vec;
  cout << "vec = ";
  for (int i = 0; i < 3; ++i)
    cout << setprecision(10) << vec[i] << ", ";
  cout << vec.sqrMagnitude();
  cout << "\n\n";
  
  vec = rot * vec;
  cout << "vec = ";
  for (int i = 0; i < 3; ++i)
    cout << setprecision(10) << vec[i] << ", ";
  cout << vec.sqrMagnitude();
  cout << "\n\n";
}
