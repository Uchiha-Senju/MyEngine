#if !defined(MATH_H_INCLUDED)
  #define MATH_H_INCLUDED

  #include <math.h>
  #include <limits>

  template <typename num_type = float>
  class Complex {
    public :
      num_type re;
      num_type im;
      
      Complex() {re = 0; im = 0;}
      
      template <typename other_num_type>
      Complex(other_num_type a, other_num_type b) {re = a; im = b;}
      template <typename other_num_type>
      Complex<num_type>& operator=(const Complex<other_num_type>& z) {
        re = z.re; im = re.im;
        return *this;
      }
      template <typename other_num_type>
      Complex(const Complex<other_num_type>& z) {
        *this = z;
      }
      
      num_type real() const {
        return re;
      }
      num_type imaginary() const {
        return im;
      }
      template <typename other_num_type>
      bool equals(const Complex<other_num_type>& z) const {
        return re == z.re and im == z.im;
      }
      operator bool() const{
        return re == num_type(0)
               and im == num_type(0);
      }
      // Typical functions
      num_type sqrMagnitude() const {
        return re * re + im * im;
      }
      num_type magnitude() const {
        return sqrt(sqrMagnitude());
      }
      num_type arg() const {
        if (re == 0) {
          if (im == 0)
            return 0;
          else 
            return acos(0) * (im > 0) ? 1 : -1;
        } else if (re > 0) 
          return atan(im/re);
        else
          return atan(im/re) + acos(-1) * (im > 0) ? 1 : -1;
      }
      
      template <typename other_num_type>
      Complex<num_type> add(const Complex<other_num_type>& z) const {
        return Complex<num_type>(re + z.re, re + z.im);
      }
      template <typename other_num_type>
      Complex<num_type> add(other_num_type z) const {
        return Complex<num_type>(re + z, im);
      }
      template <typename other_num_type>
      Complex<num_type> subtract(const Complex<other_num_type>& z) const {
        return Complex<num_type>(re - z.re, re - z.im);
      }
      template <typename other_num_type>
      Complex<num_type> subtract(other_num_type z) const {
        return Complex<num_type>(re - z, im);
      }
      Complex<num_type> conjugate() const {
        return Complex<num_type>(re, -im);
      }
      template <typename other_num_type>
      Complex<num_type> multiply(const Complex<other_num_type>& z) const {
        return Complex<num_type>(re * z.re - im * z.im, re * z.im + z.re * im);
      }
      template <typename other_num_type>
      Complex<num_type> multiply(other_num_type z) const {
        return Complex<num_type>(re * z, im * z);
      }
      template <typename other_num_type>
      Complex<num_type> divide(other_num_type z) const {
        if (z == 0)
          return Complex(std::numeric_limits<num_type>::quiet_NaN(), std::numeric_limits<num_type>::quiet_NaN());
        return Complex<num_type>(re / z, im / z);
      }
      template <typename other_num_type>
      Complex<num_type> divide(const Complex<other_num_type>& z) const {
        if (z.re == 0 and z.im == 0)
          return Complex(std::numeric_limits<num_type>::quiet_NaN(), std::numeric_limits<num_type>::quiet_NaN());
        return multiply(z.conjugate().divide(z.sqrMagnitude));
      }
      Complex<num_type> normalized() const {
        if (sqrMagnitude() != 0)
          return divide(magnitude());
        return Complex<num_type>();
      }
      Complex<num_type> cheapNormalized() const {
        if (sqrMagnitude() != 0)
          return divide(sqrMagnitude());
        return Complex<num_type>();
      }
      // Operators
      template <typename other_num_type>
      Complex<num_type> operator+(const Complex<other_num_type>& z) const {return add(z);}
      template <typename other_num_type>
      Complex<num_type> operator+(other_num_type z) const {return add(z);}
      template <typename other_num_type>
      friend Complex<num_type> operator+(other_num_type z1, const Complex<other_num_type>& z2) {return z2 + z1;}
      template <typename other_num_type>
      Complex<num_type> operator-(const Complex<other_num_type>& z) const {return subtract(z);}
      template <typename other_num_type>
      Complex<num_type> operator-(other_num_type z) const {return subtract(z);}
      template <typename other_num_type>
      friend Complex<num_type> operator-(other_num_type z1, const Complex<other_num_type>& z2) {return z2 - z1;}
      template <typename other_num_type>
      Complex<num_type> operator*(const Complex<other_num_type>& z) const {return multiply(z);}
      template <typename other_num_type>
      Complex<num_type> operator*(other_num_type z) const {return multiply(z);}
      template <typename other_num_type>
      friend Complex<num_type> operator*(other_num_type z1, const Complex<other_num_type>& z2) {return z2 * z1;}
      template <typename other_num_type>
      Complex<num_type> operator/(const Complex<other_num_type>& z) {return divide(z);}
      template <typename other_num_type>
      Complex<num_type> operator/(other_num_type z) const {return divide(z);}
      template <typename other_num_type>
      friend Complex<num_type> operator/(other_num_type z1, const Complex<other_num_type>& z2) {return z2.conjugate() * z1 / z2.sqrMagnitude();}
      
      template <typename other_num_type>
      Complex<num_type>& operator+=(const Complex<other_num_type>& z) { return *this = add(z);}
      template <typename other_num_type>
      Complex<num_type>& operator+=(other_num_type z) { return *this = add(z);}
      template <typename other_num_type>
      Complex<num_type>& operator-=(const Complex<other_num_type>& z) { return *this = subtract(z);}
      template <typename other_num_type>
      Complex<num_type>& operator-=(other_num_type z) { return *this = subtract(z);}
      template <typename other_num_type>
      Complex<num_type>& operator*=(const Complex<other_num_type>& z) { return *this = multiply(z);}
      template <typename other_num_type>
      Complex<num_type>& operator*=(other_num_type z) { return *this = multiply(z);}
      template <typename other_num_type>
      Complex<num_type>& operator/=(const Complex<other_num_type>& z) { return *this = divide(z);}
      template <typename other_num_type>
      Complex<num_type>& operator/=(other_num_type z) { return *this = divide(z);}
      
      Complex<num_type> operator~() const {return conjugate();}
      Complex<num_type> operator-() const {return Complex(-re,-im);}
      
      template <typename other_num_type>
      bool operator==(const Complex<other_num_type>& z) const {return equals(z);}
      template <typename other_num_type>
      bool operator!=(const Complex<other_num_type>& q) const {return not equals(q);}
      
      // One subscript output with mutable return type, another with const
      num_type operator[](int i) const {
        if (i < 0)
          i = i % 4 + 4;
        else
          i = i % 4;
        if (i == 0)
          return this->re;
        else if (i == 1)
          return this->im;
      }
      num_type& operator[](int i) {
        if (i < 0)
          i = i % 4 + 4;
        else
          i = i % 4;
        if (i == 0)
          return this->re;
        else if (i == 1)
          return this->im;
      }
  };

  template <typename num_type = float>
  class Quaternion {
    public:
      num_type w;
      num_type x;
      num_type y;
      num_type z;
    
      Quaternion() {w = 0; x = 0; y = 0; z = 0;}
      template <typename other_num_type>
      Quaternion(other_num_type a, other_num_type b, other_num_type c, other_num_type d) {
        w = a; x = b; y = c; z = d;
      }
      template <typename other_num_type>
      Quaternion(const Complex<other_num_type>& z1, const Complex<other_num_type>& z2) {
        w = z1.re; x = z1.im;
        y = z2.re; z = z2.im;
      }
      template <typename other_num_type>
      Quaternion<num_type>& operator=(const Quaternion<other_num_type>& q) {
        w = q.w; x = q.x; y = q.y; z = q.z;
        return *this;
      }
      template <typename other_num_type>
      Quaternion(const Quaternion<other_num_type>& q) {
        *this = q;
      }
      
      num_type scalar() const {
        return w;
      }
      Quaternion<num_type> vector() const {
        return Quaternion(0, x, y, z);
      }
      Complex<num_type> complex1() const {
        return Complex<num_type>(w,x);
      }
      Complex<num_type> complex2() const {
        return Complex<num_type>(y,z);
      }
      template <typename other_num_type>
      bool equals(const Quaternion<other_num_type>& q) const {
        return w == q.w and x == q.x and y == q.y and z == q.z;
      }
      operator bool const () {
        return w == num_type(0)
               and x == num_type(0)
               and y == num_type(0)
               and z == num_type(0);
      }
      // Typical functions
      num_type sqrMagnitude() const {
        return w * w + x * x + y * y + z * z;
      }
      num_type magnitude() const {
        return sqrt(sqrMagnitude());
      }
      template <typename other_num_type>
      Quaternion<num_type> add(const Quaternion<other_num_type>& q) const {
        return Quaternion<num_type>(w + q.w, x + q.x, y + q.y, z + q.z);
      }
      template <typename other_num_type>
      Quaternion<num_type> add(other_num_type q) const {
        return Quaternion<num_type>(w + q, x, y, z);
      }
      template <typename other_num_type>
      Quaternion<num_type> subtract(const Quaternion<other_num_type>& q) const {
        return Quaternion<num_type>(w - q.w, x - q.x, y - q.y, z - q.z);
      }
      template <typename other_num_type>
      Quaternion<num_type> subtract(other_num_type q) const {
        return Quaternion<num_type>(w - q, x, y, z);
      }
      Quaternion<num_type> conjugate() const {
        return Quaternion<num_type>(w, -x, -y, -z);
      }
      template <typename other_num_type>
      Quaternion<num_type> multiply(const Quaternion<other_num_type>& q) const {
        return Quaternion<num_type>(w * q.w - x * q.x - y * q.y - z * q.z,
                                    w * q.x + x * q.w + y * q.z - z * q.y,
                                    w * q.y + y * q.w + z * q.x - x * q.z,
                                    w * q.z + z * q.w + x * q.y - y * q.x);
      }
      template <typename other_num_type>
      Quaternion<num_type> multiply(other_num_type q) const {
        return Quaternion<num_type>(w * q, x * q, y * q, z * q);
      }
      template <typename other_num_type>
      Quaternion<num_type> divide(other_num_type q) const {
        if (q == 0)
          return Quaternion(std::numeric_limits<num_type>::quiet_NaN(),
                            std::numeric_limits<num_type>::quiet_NaN(),
                            std::numeric_limits<num_type>::quiet_NaN(),
                            std::numeric_limits<num_type>::quiet_NaN());
        return Quaternion<num_type>(w / q, x / q, y / q, z / q);
      }
      Quaternion<num_type> inverse() const {
        if (sqrMagnitude() == 0)
          return Quaternion(std::numeric_limits<num_type>::quiet_NaN(),
                            std::numeric_limits<num_type>::quiet_NaN(),
                            std::numeric_limits<num_type>::quiet_NaN(),
                            std::numeric_limits<num_type>::quiet_NaN());
        return conjugate().divide(sqrMagnitude());
      }
      Quaternion<num_type> normalized() const {
        if (sqrMagnitude() != 0)
          return divide(magnitude());
        return Quaternion<num_type>();
      }
      Quaternion<num_type> cheapNormalized() const {
        if (sqrMagnitude() != 0)
          return divide(sqrMagnitude());
        return Quaternion<num_type>();
      }
      // Operators
      template <typename other_num_type>
      Quaternion<num_type> operator+(const Quaternion<other_num_type>& q) const {return add(q);}
      template <typename other_num_type>
      Quaternion<num_type> operator+(other_num_type q) const {return add(q);}
      template <typename other_num_type>
      friend Quaternion<num_type> operator+(other_num_type q1, const Quaternion<other_num_type>& q2) {return q2 + q1;}
      template <typename other_num_type>
      Quaternion<num_type> operator-(const Quaternion<other_num_type>& q) const {return subtract(q);}
      template <typename other_num_type>
      Quaternion<num_type> operator-(other_num_type q) const {return subtract(q);}
      template <typename other_num_type>
      friend Quaternion<num_type> operator-(other_num_type q1, const Quaternion<other_num_type>& q2) {return q2 - q1;}
      template <typename other_num_type>
      Quaternion<num_type> operator*(const Quaternion<other_num_type>& q) const {return multiply(q);}
      template <typename other_num_type>
      Quaternion<num_type> operator*(other_num_type q) const {return multiply(q);}
      template <typename other_num_type>
      friend Quaternion<num_type> operator*(other_num_type q1, const Quaternion<other_num_type>& q2) {return q2 * q1;}
      
      template <typename other_num_type>
      Quaternion<num_type>& operator+=(const Quaternion<other_num_type>& q) { return *this = add(q);}
      template <typename other_num_type>
      Quaternion<num_type>& operator+=(other_num_type q) { return *this = add(q);}
      template <typename other_num_type>
      Quaternion<num_type>& operator-=(const Quaternion<other_num_type>& q) { return *this = subtract(q);}
      template <typename other_num_type>
      Quaternion<num_type>& operator-=(other_num_type q) { return *this = subtract(q);}
      template <typename other_num_type>
      Quaternion<num_type>& operator*=(const Quaternion<other_num_type>& q) { return *this = multiply(q);}
      template <typename other_num_type>
      Quaternion<num_type>& operator*=(other_num_type q) { return *this = multiply(q);}
      
      Quaternion<num_type> operator~() const {return conjugate();}
      Quaternion<num_type> operator+() const {return Quaternion(w,x,w,z);}
      Quaternion<num_type> operator-() const {return Quaternion(-w,-x,-w,-z);}
      
      template <typename other_num_type>
      bool operator==(const Quaternion<other_num_type>& q) const {return equals(q);}
      template <typename other_num_type>
      bool operator!=(const Quaternion<other_num_type>& q) const {return not equals(q);}
      
      // One subscript output with mutable return type, another with const
      num_type operator[](int i) const {
        if (i < 0)
          i = i % 4 + 4;
        else
          i = i % 4;
        if (i == 0)
          return w;
        else if (i == 1)
          return x;
        else if (i == 2)
          return y;
        else if (i == 3)
          return z;
      }
      num_type& operator[](int i) {
        if (i < 0)
          i = i % 4 + 4;
        else
          i = i % 4;
        if (i == 0)
          return w;
        else if (i == 1)
          return x;
        else if (i == 2)
          return y;
        else if (i == 3)
          return z;
      }
  };

#endif
