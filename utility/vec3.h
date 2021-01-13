#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

// Class defining vec3 variables and methods
class vec3 {
public:

    // Constructors
    vec3() : e{ 0,0,0 } {}
    vec3(float e0, float e1, float e2) : e{ e0, e1, e2 } {}

    // Functions defining components of vector
    float x() const { 
        return e[0]; 
    }
    float y() const { 
        return e[1]; 
    }
    float z() const { 
        return e[2]; 
    }

    // Function defining additive inverse of vector
    vec3 operator-() const { 
        return vec3(-e[0], -e[1], -e[2]); 
    }

    // Function enabling indexing of vectors (eg. vector[1] returns second element and so on)
    float operator[](int i) const { 
        return e[i]; 
    }
    float& operator[](int i) { 
        return e[i]; 
    }

    // Function defining addition of two vectors with += operator
    vec3& operator+=(const vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    // Function defining multiplication of scalar to vector
    vec3& operator*=(const float t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    // Function defining division of a vector by scalar
    vec3& operator/=(const float t) {
        return *this *= 1 / t;
    }

    // Function defining length or magnitude of a vector
    float length() const {
        return sqrt(length_squared());
    }

    // Function defining square of magnitude of the vector
    float length_squared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

public:
    float e[3];
};

// type aliases for vec3

// using point3 = vec3;
// using color = vec3;

typedef vec3 point3;
typedef vec3 color;

// Defining operations on two vec3 objects

// Writing out a vector's content
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// element wise multiplication
inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// scalar multiplication
inline vec3 operator*(const float t, const vec3& u) {
    return vec3(t * u.e[0], t * u.e[1], t * u.e[2]);
}

inline vec3 operator*(const vec3& v, float t) {
    return t * v;
}

// scalar division
inline vec3 operator/(const vec3& v, float t) {
    return 1 / t * v;
}

inline float dot(const vec3& v, const vec3& u) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& v, const vec3& u) {
    return vec3(v.e[1] * u.e[2] - u.e[1] * v.e[2],
                v.e[2] * u.e[0] - u.e[2] * v.e[0],
                v.e[0] * u.e[1] - u.e[0] * v.e[1]);
}

inline vec3 normalize(const vec3& v) {
    return v / v.length();
}

#endif