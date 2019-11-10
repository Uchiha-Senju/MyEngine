#if !defined(VECTOR_H_INCLUDED)
  #define VECTOR_H_INCLUDED
  
  #include <math.h>
  #include <limits>

  template <typename num_type = float>
  class Vector2 {
    public: 
      num_type x,y;
      
      Vector2 () {
        x = 0;
        y = 0;
      }
      template <typename other_num_type>
      Vector2(other_num_type n) {
        x = n; y = n;
      }
      template <typename other_num_type>
      Vector2(other_num_type x, other_num_type y) {
        this->x = x; this->y = y;
      }
      template <typename other_num_type>
      Vector2<num_type>& operator=(const Vector2<other_num_type>& vec) {
        x = num_type(vec.x); y = num_type(vec.y);
        return *this;
      }
      template <typename other_num_type>
      Vector2(const Vector2<other_num_type>& vec) {
        *this = vec;
      }
      
      // Static members
      static const Vector2<num_type> forward;
      static const Vector2<num_type> backward;
      static const Vector2<num_type> left;
      static const Vector2<num_type> right;
      
      // Traditional functions
      template <typename other_num_type>
      bool equals (const Vector2<other_num_type>& e) const {
        if (e.x == x and e.y == y) 
          return true;
        return false;
      }
      operator bool() const {
        return x == 0 and y == 0;
      }
      num_type sqrMagnitude() const {
        return (x*x + y*y);
      }
      num_type magnitude() const {
        return sqrt( sqrMagnitude() );
      }
      template <typename other_num_type>
      Vector2<num_type> add(const Vector2<other_num_type>& a) const {
        Vector2<num_type> new_vec;
        new_vec.x = x + a.x;
        new_vec.y = y + a.y;
        return new_vec;
      }
      template <typename other_num_type>
      Vector2<num_type> scale(other_num_type s) const {
        Vector2<num_type> scaled_vec;
        scaled_vec.x = x * s;
        scaled_vec.y = y * s;
        return scaled_vec;
      }
      template <typename other_num_type>
      Vector2<num_type> from(const Vector2<other_num_type>& s) const {
        Vector2<num_type> new_vec;
        new_vec.x = x - s.x;
        new_vec.y = y - s.y;
        return new_vec;
      }
      Vector2<num_type> normalized() const {
        if (sqrMagnitude() != 0) 
          return scale(1/magnitude());
        return Vector2<num_type>();
      }
      Vector2<num_type> cheapNormalized() const {
        if (sqrMagnitude() != 0) 
          return scale(1/sqrMagnitude());
        return Vector2<num_type>();
      }
      template <typename other_num_type>
      Vector2<num_type> setMagnitude(other_num_type m) const {
        return scale( m / magnitude() );
      }
      template <typename other_num_type>
      Vector2<num_type> clamp(other_num_type m) const {
        if (sqrMagnitude() > m*m) 
          return setMagnitude(m);
        else
          return *this;
      }
      template <typename other_num_type>
      num_type dotProduct(const Vector2<other_num_type>& d) const {
        return (x * d.x + y * d.y);
      }
      template <typename other_num_type>
      num_type crossProduct(const Vector2<other_num_type>& c) const {
        return (x * c.y - y * c.x);
      }
      template <typename other_num_type>
      num_type angleFrom(const Vector2<other_num_type>& a) const {
        num_type dot = normalized().dotProduct(a.normalized());
        return acos(dot);
      }
      // Operator function definitions
      template <typename other_num_type>
      Vector2<num_type> operator+(const Vector2<other_num_type>& a) const { return add(a);}
      template <typename other_num_type>
      Vector2<num_type> operator-(const Vector2<other_num_type>& s) const { return from(s);}
      template <typename other_num_type>
      Vector2<num_type> operator*(other_num_type m) { return scale(m);}
      template <typename other_num_type>
      friend Vector2<num_type> operator*(other_num_type m, const Vector2<other_num_type>& vec) { return vec * m;}
      template <typename other_num_type>
      Vector2<num_type> operator/(other_num_type d) {
        if (d == 0) 
          return Vector2<num_type>(std::numeric_limits<num_type>::quiet_NaN());
        return *this * (1/d);
      }
      
      template <typename other_num_type>
      bool operator==(const Vector2<other_num_type>& e) const { return equals(e);}
      template <typename other_num_type>
      bool operator!=(const Vector2<other_num_type>& e) const { return not equals(e);}
      template <typename other_num_type>
      bool operator>(const Vector2<other_num_type>& c) const { return sqrMagnitude() > c.sqrMagnitude();}
      template <typename other_num_type>
      bool operator<(const Vector2<other_num_type>& c) const { return sqrMagnitude() < c.sqrMagnitude();}
      template <typename other_num_type>
      bool operator>=(const Vector2<other_num_type>& c) const { return sqrMagnitude() >= c.sqrMagnitude();}
      template <typename other_num_type>
      bool operator<=(const Vector2<other_num_type>& c) const { return sqrMagnitude() <= c.sqrMagnitude();}
      
      template <typename other_num_type>
      Vector2<num_type>& operator+=(const Vector2<other_num_type>& a) { return *this = add(a);}
      template <typename other_num_type>
      Vector2<num_type>& operator-=(const Vector2<other_num_type>& s) { return *this = add(s);}
      template <typename other_num_type>
      Vector2<num_type>& operator*=(other_num_type m) { return *this = scale(m);}
      template <typename other_num_type>
      Vector2<num_type>& operator/=(other_num_type d) { return *this = operator/(d);}
      
      // One subscript output with mutable return type, another with const
      num_type operator[](int i) const {
        if (i < 0)
          i = i % 2 + 2;
        else
          i = i % 2;
        if (i == 0)
          return x;
        else if (i == 1)
          return y;
      }
      num_type& operator[](int i) {
        if (i < 0)
          i = i % 2 + 2;
        else
          i = i % 2;
        if (i == 0)
          return x;
        else if (i == 1)
          return y;
      }
  };
  template <typename num_type> const Vector2<num_type> Vector2<num_type>::left(-1, 0);
  template <typename num_type> const Vector2<num_type> Vector2<num_type>::right(1, 0);
  template <typename num_type> const Vector2<num_type> Vector2<num_type>::forward(0, 1);
  template <typename num_type> const Vector2<num_type> Vector2<num_type>::backward(0, -1);

  template <typename num_type = float>
  class Vector3 {
    public:
      num_type x, y, z;
      
      Vector3 () {
        x = 0;
        y = 0;
        z = 0;
      }
      template <typename other_num_type>
      Vector3 (other_num_type n) {
        x = n; y = n; z = n;
      }
      template <typename other_num_type>
      Vector3 (other_num_type x, other_num_type y, other_num_type z) {
        this->x = x; this->y = y; this->z = z;
      }
      template <typename other_num_type>
      Vector3 (const Vector2<other_num_type>& vec) {
        x = vec.x; y = vec.y; z = 0;
      }
      template <typename other_num_type>
      Vector3<num_type>& operator=(const Vector3<other_num_type>& vec) {
        x = vec.x; y = vec.y; z = vec.z;
        return *this;
      }
      template <typename other_num_type>
      Vector3 (const Vector3<other_num_type>& vec) {
        *this = vec;
      }
      
      // Static members
      static const Vector3<num_type> up;
      static const Vector3<num_type> down;
      static const Vector3<num_type> left;
      static const Vector3<num_type> right;
      static const Vector3<num_type> forward;
      static const Vector3<num_type> backward;
      
      // Traditional functions
      template <typename other_num_type>
      bool equals(const Vector3<other_num_type>& e) const {
        if (e.x == x && e.y == y && e.z == z)
          return true;
        return false;
      }
      operator bool() const {
        return x == 0 and y == 0 and z == 0;
      }
      num_type sqrMagnitude() const {
        return (x*x + y*y + z*z);
      }
      num_type magnitude() const {
        return sqrt( sqrMagnitude() );
      }
      template <typename other_num_type>
      Vector3<num_type> add(const Vector3<other_num_type>& a) const {
        Vector3<num_type> new_vec;
        new_vec.x = x + a.x;
        new_vec.y = y + a.y;
        new_vec.z = z + a.z;
        return new_vec;
      }
      template <typename other_num_type>
      Vector3<num_type> scale(other_num_type s) const {
        Vector3<num_type> new_vec;
        new_vec.x = x * s;
        new_vec.y = y * s;
        new_vec.z = z * s;
        return new_vec;
      }
      template <typename other_num_type>
      Vector3<num_type> from(const Vector3<other_num_type>& s) const {
        return add(s.scale(-1));
      }
      Vector3<num_type> normalized() const {
        if (sqrMagnitude() != 0) 
          return scale(1/magnitude());
        return Vector3<num_type>();
      }
      Vector3<num_type> cheapNormalized() const {
        if (sqrMagnitude() != 0) 
          return scale(1/sqrMagnitude());
        return Vector3<num_type>();
      }
      template <typename other_num_type>
      Vector3<num_type> setMagnitude(other_num_type m) const {
        return scale( m / magnitude() );
      }
      template <typename other_num_type>
      Vector3<num_type> clamp(other_num_type m) const {
        if (sqrMagnitude() > m*m) 
          return setMagnitude(m);
        else
          return *this;
      }
      template <typename other_num_type>
      num_type dotProduct(const Vector3<other_num_type>& d) const {
        return (x * d.x + y * d.y + z * d.z);
      }
      template <typename other_num_type>
      Vector3<num_type> crossProduct(const Vector3<other_num_type>& c) const {
        Vector3<num_type> new_vec;
        new_vec.x = (y * c.z - z * c.y);
        new_vec.y = (z * c.x - x * c.z);
        new_vec.z = (x * c.y - y * c.x);
        return new_vec;
      }
      template <typename other_num_type>
      num_type angleTo(const Vector3<other_num_type>& a) const {
        num_type dot = normalized().dotProduct(a.normalized());
        return acos(dot);
      }
      // Operator function definitions
      template <typename other_num_type>
      Vector3<num_type> operator+(const Vector3<other_num_type>& a) const { return add(a);}
      template <typename other_num_type>
      Vector3<num_type> operator-(const Vector3<other_num_type>& s) const { return from(s);}
      template <typename other_num_type>
      Vector3<num_type> operator*(other_num_type m) const { return scale(m);}
      template <typename other_num_type>
      friend Vector3<num_type> operator*(other_num_type m, const Vector3<other_num_type>& vec) { return vec * m;}
      template <typename other_num_type>
      Vector3<num_type> operator/(other_num_type d) const {
        if (d == 0) 
          return Vector3<num_type>(std::numeric_limits<num_type>::quiet_NaN());
        return *this * (1/d);
      }
      
      template <typename other_num_type>
      bool operator==(const Vector3<other_num_type>& e) const { return equals(e);}
      template <typename other_num_type>
      bool operator!=(const Vector3<other_num_type>& e) const { return not equals(e);}
      template <typename other_num_type>
      bool operator>(const Vector3<other_num_type>& c) const { return sqrMagnitude() > c.sqrMagnitude();}
      template <typename other_num_type>
      bool operator<(const Vector3<other_num_type>& c) const { return sqrMagnitude() < c.sqrMagnitude();}
      template <typename other_num_type>
      bool operator>=(const Vector3<other_num_type>& c) const { return sqrMagnitude() >= c.sqrMagnitude();}
      template <typename other_num_type>
      bool operator<=(const Vector3<other_num_type>& c) const { return sqrMagnitude() <= c.sqrMagnitude();}
      
      template <typename other_num_type>
      Vector3<num_type>& operator+=(const Vector3<other_num_type>& a) { return *this = add(a);}
      template <typename other_num_type>
      Vector3<num_type>& operator-=(const Vector3<other_num_type>& s) { return *this = add(s);}
      template <typename other_num_type>
      Vector3<num_type>& operator*=(other_num_type m) { return *this = scale(m);}
      template <typename other_num_type>
      Vector3<num_type>& operator/=(other_num_type d) { return *this = operator/(d);}
      
      // One subscript output with mutable return type, another with const
      num_type operator[](int i) const {
        if (i < 0)
          i = i % 3 + 3;
        else
          i = i % 3;
        if (i == 0)
          return x;
        else if (i == 1)
          return y;
        else if (i == 2)
          return z;
      }
      num_type& operator[](int i) {
        if (i < 0)
          i = i % 3 + 3;
        else
          i = i % 3;
        if (i == 0)
          return x;
        else if (i == 1)
          return y;
        else if (i == 2)
          return z;
      }
  };
  template <typename num_type> const Vector3<num_type> Vector3<num_type>::up(0, 0, 1);
  template <typename num_type> const Vector3<num_type> Vector3<num_type>::down(0, 0, -1);
  template <typename num_type> const Vector3<num_type> Vector3<num_type>::left(-1, 0, 0);
  template <typename num_type> const Vector3<num_type> Vector3<num_type>::right(1, 0, 0);
  template <typename num_type> const Vector3<num_type> Vector3<num_type>::forward(0, 1, 0);
  template <typename num_type> const Vector3<num_type> Vector3<num_type>::backward(0, -1, 0);

#endif
