#include "vector.h"
#include "complex.h"

// Curiously Recursive Template Parameter
template <class FinalType, typename num_type = float>
class Rotator {
  public :
    static const FinalType identity;
  
    virtual Vector3<num_type> rotate(const Vector3<num_type>&) const = 0;
    virtual Vector3<num_type> operator*(const Vector3<num_type>& vec) const {
      return rotate(vec);
    }
    
    virtual FinalType normalized() const = 0;
    virtual FinalType inverse() const = 0;
    virtual Vector3<num_type> unrotate(const Vector3<num_type>& vec) const {
      return this->inverse().rotate(vec);
    }
    
    virtual FinalType compose(const FinalType&) const = 0;
    virtual FinalType operator*(const FinalType& rot) const {
      return compose(rot);
    }
    // virtual FinalType& operator*=(const FinalType& rot) {
      // *this = compose(rot);
      // return *this;
    // }
    virtual FinalType rotateFromTo(const Vector3<num_type>&, const Vector3<num_type>&) const = 0;
};

template <typename num_type = float>
class AngleAxisRotator : public virtual Rotator<AngleAxisRotator<num_type>, num_type> {
  public :
    num_type angle;
    Vector3<num_type> axis;
    
    AngleAxisRotator() {
      angle = 0;
      axis = Vector3<num_type>();
    }
    template <typename other_num_type>
    AngleAxisRotator(other_num_type ang,const Vector3<other_num_type>& a) {
       angle = ang; axis = a;
    }
    template <typename other_num_type>
    AngleAxisRotator(other_num_type ang, other_num_type x, other_num_type y, other_num_type z) {
       angle = ang; axis = Vector3<num_type>(x,y,z);
    }
    template <typename other_num_type>
    AngleAxisRotator<num_type>& operator=(const AngleAxisRotator<other_num_type>& aar) {
       angle = aar.angle; axis = aar.axis;
       return this;
    }
    template <typename other_num_type>
    AngleAxisRotator(AngleAxisRotator<other_num_type>& aar) {
      *this = aar;
    }
    
    // Identity element
    static const AngleAxisRotator identity;
    
    // Virtual function implementations
    Vector3<num_type> rotate(const Vector3<num_type>& vec) const {
      if (axis.sqrMagnitude() == 0)
        return Vector3<num_type>();
      // Using Rodrigues' Rotation Formula
      // Resolve vec into parallel and perpendicular components and use vector triple product for derivation
      return axis.magnitude() * vec * cos(angle)
           + axis * axis.dotProduct(vec) * (1 - cos(angle)) / axis.magnitude()
           + axis.crossProduct(vec) * sin(angle);
    }
    AngleAxisRotator<num_type> normalized() const {
      return AngleAxisRotator<num_type>(angle, axis.normalized());
    }
    AngleAxisRotator<num_type> inverse() const {
      return AngleAxisRotator(-angle, axis / axis.sqrMagnitude());
      // Alternate :
      // return AngleAxisRotator(angle, -axis / axis.sqrMagnitude());
    }
    AngleAxisRotator<num_type> compose(const AngleAxisRotator<num_type>& aar) const {
      // TODO : Not be so cheap in the method of calculation
      Vector3<num_type> vec = Vector3<num_type>::right, rot_vec = rotate(aar.rotate(Vector3<num_type>::right));
      if (vec.normalized() != rot_vec.normalized())
        return rotateFromTo(vec, rot_vec);
      else {
        vec = Vector3<num_type>::up;
        rot_vec = rotate(aar.rotate(Vector3<num_type>::right));
        return rotateFromTo(vec, rot_vec);
      }
    }
    AngleAxisRotator<num_type> rotateFromTo(const Vector3<num_type>& vec1, const Vector3<num_type>& vec2) const {
      return AngleAxisRotator(vec1.angleTo(vec2), vec1.crossProduct(vec2) / vec1.sqrMagnitude());
    }
};
template <typename num_type> const AngleAxisRotator<num_type> AngleAxisRotator<num_type>::identity(0, 1, 0, 0);


template <typename num_type = float>
class RotationMatrix : virtual public Rotator<RotationMatrix<num_type>, num_type> {
  public :
    num_type matrix[3][3];
    
    RotationMatrix() {
      // Identity matrix      
      matrix[0][0] = 1;
      matrix[0][1] = 0;
      matrix[0][2] = 0;
      
      matrix[1][0] = 0;
      matrix[1][1] = 1;
      matrix[1][2] = 0;
      
      matrix[2][0] = 0;
      matrix[2][1] = 0;
      matrix[2][2] = 1;
    }
    template <typename other_num_type>
    RotationMatrix(other_num_type alpha = 0, other_num_type beta = 0, other_num_type gamma = 0, other_num_type mag = 1) {
      // alpha (roll) : rotation angle in YZ plane i.e. around X
      // beta (pitch) : rotation angle in ZX plane i.e. around Y
      // gamma (yaw) : rotation angle in XY plane i.e. around Z
      // Order : XY * ZX * YZ * vec
      num_type c_a = cos(alpha), s_a = sin(alpha),
               c_b = cos(beta), s_b = sin(beta),
               c_g = cos(gamma), s_g = sin(gamma);
      
      matrix[0][0] = c_b * c_g;
      matrix[0][1] = s_a * s_b * c_g - c_a * s_g;
      matrix[0][2] = c_a * s_b * c_g + s_a * s_g;
      
      matrix[1][0] = c_b * s_g;
      matrix[1][1] = s_a * s_b * s_g + c_a * c_g;
      matrix[1][2] = c_a * s_b * s_g - s_a * c_g;
      
      matrix[2][0] = - s_b;
      matrix[2][1] = s_a * c_b;
      matrix[2][2] = c_a * c_b;
      
      for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
          matrix[i][j] = matrix[i][j] * mag;
    }
    template <typename other_num_type>
    RotationMatrix<num_type>& operator=(const RotationMatrix<other_num_type>& rot) {
      for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
          matrix[i][j] = rot.matrix[i][j];
      return *this;
    }
    template <typename other_num_type>
    RotationMatrix(const RotationMatrix<other_num_type>& rot){
      *this = rot;
    }
    template <typename other_num_type>
    RotationMatrix(other_num_type angle, Vector3<other_num_type>& axis) {
      other_num_type c = cos(angle);
      other_num_type s = sin(angle);
      other_num_type mag = axis.magnitude();
      other_num_type c_1 = 1 - c;
      // Matrix-ified Rodriegues Rotation formula 
      matrix[0][0] = mag * c + axis.x * axis.x * c_1 / mag;
      matrix[0][1] = axis.x * axis.y * c_1 / mag - axis.z * s;
      matrix[0][2] = axis.z * axis.x * c_1 / mag + axis.y * s;
      
      matrix[1][0] = axis.x * axis.y * c_1 / mag + axis.z * s;
      matrix[1][1] = mag * c + axis.y * axis.y * c_1 / mag;
      matrix[1][2] = axis.y * axis.z * c_1 / mag - axis.x * s;
      
      matrix[2][0] = axis.z * axis.x * c_1 / mag - axis.y * s;
      matrix[2][1] = axis.y * axis.z * c_1 / mag + axis.x * s;
      matrix[2][2] = mag * c + axis.z * axis.z * c_1 / mag;
    }
    // Convertors
    template <typename other_num_type>
    RotationMatrix(AngleAxisRotator<other_num_type>& aar) : RotationMatrix(aar.angle, aar.axis) {}
    template <typename other_num_type>
    operator AngleAxisRotator<other_num_type>() {
      // TODO : improve the function, you know it can be
      other_num_type e_val, angle;
      
      // Eigenvalue is simply the 'magnitude' of the rotation
      e_val = sqrt(matrix[0][0] * matrix[0][0] + matrix[1][0] * matrix[1][0] + matrix[2][0] * matrix[2][0]);
      
      Vector3<other_num_type> e_vec, v1 = Vector3(matrix[0][0] - e_val, matrix[0][1], matrix[0][2]),
                                     v2 = Vector3(matrix[1][0], matrix[1][1] - e_val, matrix[1][2]),
                                     v3 = Vector3(matrix[2][0], matrix[2][1], matrix[2][2] - e_val);
      // ERR: MAGIC NUMBER ALERT
      // Check to see if v1 is approximately zero
      if (v1.sqrMagnitude() > 0.000001 and v2.sqrMagnitude() > 0.000001) {
        e_vec = v1.crossProduct(v2);
        v2 = rotate(v1);
        angle = v1.angleTo(v2);
        if (v1.crossProduct(v2).dotProduct(e_vec) < 0);
          angle *= -1;
      } else if (v2.sqrMagnitude() > 0.000001) {
        e_vec = v2.crossProduct(v3);
        v3 = rotate(v2);
        angle = v2.angleTo(v3);
        if (v2.crossProduct(v3).dotProduct(e_vec) < 0);
          angle *= -1;
      } else {
        e_vec = v3.crossProduct(v1);
        v1 = rotate(v3);
        angle = v3.angleTo(v1);
        if (v3.crossProduct(v1).dotProduct(e_vec) < 0);
          angle *= -1;
      }
      
      return AngleAxisRotator(angle, e_vec.setMagnitude(e_val));
    }
    
    // Identity element
    const static RotationMatrix identity;
    
    // Virtual function implementations
    Vector3<num_type> rotate(const Vector3<num_type>& vec) const {
      Vector3<num_type> rot_vec = Vector3<num_type>();
      for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
          rot_vec[i] += vec[j] * matrix[i][j];
      return rot_vec;
    }
    RotationMatrix<num_type> normalized() const {
      num_type mag = matrix[0][0] * matrix[0][0] + matrix[1][0] * matrix[1][0] + matrix[2][0] * matrix[2][0];
      mag = sqrt(mag);
      RotationMatrix<num_type> rot_mat;
      for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
          rot_mat.matrix[i][j] = matrix[i][j] / mag;
      return rot_mat;
    }
    RotationMatrix<num_type> inverse() const {
      // It is a composition of pseudo-orthogonal matrices i.e.
      // A^T = A^-1 / sqr(mag)
      num_type sqr_mag = matrix[0][0] * matrix[0][0] + matrix[1][0] * matrix[1][0] + matrix[2][0] * matrix[2][0];
      RotationMatrix<num_type> rot_mat;
      for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
          rot_mat.matrix[i][j] = matrix[j][i] / sqr_mag;
      return rot_mat;
    }
    RotationMatrix<num_type> compose(const RotationMatrix<num_type>& mat) const {
      RotationMatrix<num_type> new_mat = RotationMatrix();
      for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
          new_mat.matrix[i][j] = 0;
          for (int k = 0; k < 3; ++k)
            new_mat.matrix[i][j] += mat.matrix[i][k] * matrix[k][j];
        }
      return new_mat;
    }
    RotationMatrix<num_type> rotateFromTo(const Vector3<num_type>& v1, const Vector3<num_type>& v2) const {
      return RotationMatrix<num_type>(v1.angleTo(v2), v1.crossProduct(v2) / v1.sqrMagnitude());
    }
    
};
template <typename num_type> const RotationMatrix<num_type> RotationMatrix<num_type>::identity(0,0,0,1);

template <typename num_type = float>
class QuaternionRotator : virtual public Rotator<QuaternionRotator<num_type>, num_type>, public Quaternion<num_type> {
  public :
    QuaternionRotator() {
      Quaternion(1, 0, 0, 0);
    }
    operator Quaternion<num_type>() const {
      return Quaternion<num_type>(this->w,this->x,this->y,this->z);
    }
    template <typename other_num_type>
    QuaternionRotator(const Quaternion<other_num_type>& q) : Quaternion<num_type>(q) {}
    template <typename other_num_type>
    QuaternionRotator(other_num_type angle, const Vector3<other_num_type>& axis) {
      num_type m = sqrt(axis.magnitude());
      if (m != 0) {
        this->w = cos(angle / 2) * m;
        num_type s = sin(angle / 2);
        this->x = s * axis.x / m;
        this->y = s * axis.y / m;
        this->z = s * axis.z / m;
      } else {
        QuaternionRotator();
      }
    }
    template <typename other_num_type>
    QuaternionRotator<num_type>& operator=(const QuaternionRotator<other_num_type>& q) {
      Quaternion<num_type>::operator=(q);
      return *this;
    }
    template <typename other_num_type>
    QuaternionRotator(const QuaternionRotator<other_num_type>& q) {
      *this = q;
    }
    
    // Convertors
    template <typename other_num_type>
    QuaternionRotator(const AngleAxisRotator<other_num_type>& aar) : QuaternionRotator(aar.angle, aar.axis) {}
    template <typename other_num_type>
    QuaternionRotator(const RotationMatrix<other_num_type>& rot_mat) : QuaternionRotator(AngleAxisRotator<num_type>(rot_mat)) {}
    template <typename other_num_type>
    operator AngleAxisRotator<other_num_type>() {
      num_type mag = this->magnitude();
      num_type half_angle = acos(this->w / mag);
      return AngleAxisRotator<num_type>(2 * half_angle, Vector3(this->x, this->y, this->z) * mag / sin(half_angle));
    }
    template <typename other_num_type>
    operator RotationMatrix<other_num_type>() {
      return RotationMatrix<num_type>(AngleAxisRotator<num_type>(*this));
    }
    
    // Identity element
    const static QuaternionRotator identity;
    
    // Virtual function implementations
    Vector3<num_type> rotate(const Vector3<num_type>& vec) const {
      Quaternion<num_type> fin_vector = (Quaternion<num_type>)(*this)
                                      * Quaternion<num_type>(num_type(0), vec.x, vec.y, vec.z)
                                      * (Quaternion<num_type>)~(*this);
      return Vector3<num_type>(fin_vector.x, fin_vector.y, fin_vector.z);
    }
    QuaternionRotator<num_type> inverse() const {
      return Quaternion<num_type>::inverse();
    }
    QuaternionRotator<num_type> compose(const QuaternionRotator<num_type>& q) const {
      return Quaternion(q) * Quaternion(*this);
    }
    QuaternionRotator<num_type> rotateFromTo(const Vector3<num_type>& vec1, const Vector3<num_type>& vec2) const {
      return QuaternionRotator<num_type>(vec1.angleTo(vec2), vec1.crossProduct(vec2).normalized());
    }
};
template <typename num_type> const QuaternionRotator<num_type> QuaternionRotator<num_type>::identity(1, 0, 0, 0);
