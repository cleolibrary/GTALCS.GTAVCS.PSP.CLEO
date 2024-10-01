#pragma once

#include "cffi.h"

namespace pkpy{

static constexpr float kEpsilon = 1e-4f;
inline static bool isclose(float a, float b){ return fabsf(a - b) < kEpsilon; }

struct Vec2{
    float x, y;
    Vec2() : x(0.0f), y(0.0f) {}
    Vec2(float x, float y) : x(x), y(y) {}
    Vec2(const Vec2& v) : x(v.x), y(v.y) {}

    Vec2 operator+(const Vec2& v) const { return Vec2(x + v.x, y + v.y); }
    Vec2& operator+=(const Vec2& v) { x += v.x; y += v.y; return *this; }
    Vec2 operator-(const Vec2& v) const { return Vec2(x - v.x, y - v.y); }
    Vec2& operator-=(const Vec2& v) { x -= v.x; y -= v.y; return *this; }
    Vec2 operator*(float s) const { return Vec2(x * s, y * s); }
    Vec2& operator*=(float s) { x *= s; y *= s; return *this; }
    Vec2 operator/(float s) const { return Vec2(x / s, y / s); }
    Vec2& operator/=(float s) { x /= s; y /= s; return *this; }
    Vec2 operator-() const { return Vec2(-x, -y); }
    bool operator==(const Vec2& v) const { return isclose(x, v.x) && isclose(y, v.y); }
    bool operator!=(const Vec2& v) const { return !isclose(x, v.x) || !isclose(y, v.y); }
    float dot(const Vec2& v) const { return x * v.x + y * v.y; }
    float cross(const Vec2& v) const { return x * v.y - y * v.x; }
    float length() const { return sqrtf(x * x + y * y); }
    float length_squared() const { return x * x + y * y; }
    Vec2 normalize() const { float l = length(); return Vec2(x / l, y / l); }
};

struct Vec3{
    float x, y, z;
    Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}

    Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    Vec3& operator+=(const Vec3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
    Vec3& operator-=(const Vec3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    Vec3 operator*(float s) const { return Vec3(x * s, y * s, z * s); }
    Vec3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
    Vec3 operator/(float s) const { return Vec3(x / s, y / s, z / s); }
    Vec3& operator/=(float s) { x /= s; y /= s; z /= s; return *this; }
    Vec3 operator-() const { return Vec3(-x, -y, -z); }
    bool operator==(const Vec3& v) const { return isclose(x, v.x) && isclose(y, v.y) && isclose(z, v.z); }
    bool operator!=(const Vec3& v) const { return !isclose(x, v.x) || !isclose(y, v.y) || !isclose(z, v.z); }
    float dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }
    Vec3 cross(const Vec3& v) const { return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
    float length() const { return sqrtf(x * x + y * y + z * z); }
    float length_squared() const { return x * x + y * y + z * z; }
    Vec3 normalize() const { float l = length(); return Vec3(x / l, y / l, z / l); }
};

struct Vec4{
    float x, y, z, w;
    Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    Vec4(const Vec4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

    Vec4 operator+(const Vec4& v) const { return Vec4(x + v.x, y + v.y, z + v.z, w + v.w); }
    Vec4& operator+=(const Vec4& v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
    Vec4 operator-(const Vec4& v) const { return Vec4(x - v.x, y - v.y, z - v.z, w - v.w); }
    Vec4& operator-=(const Vec4& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
    Vec4 operator*(float s) const { return Vec4(x * s, y * s, z * s, w * s); }
    Vec4& operator*=(float s) { x *= s; y *= s; z *= s; w *= s; return *this; }
    Vec4 operator/(float s) const { return Vec4(x / s, y / s, z / s, w / s); }
    Vec4& operator/=(float s) { x /= s; y /= s; z /= s; w /= s; return *this; }
    Vec4 operator-() const { return Vec4(-x, -y, -z, -w); }
    bool operator==(const Vec4& v) const { return isclose(x, v.x) && isclose(y, v.y) && isclose(z, v.z) && isclose(w, v.w); }
    bool operator!=(const Vec4& v) const { return !isclose(x, v.x) || !isclose(y, v.y) || !isclose(z, v.z) || !isclose(w, v.w); }
    float dot(const Vec4& v) const { return x * v.x + y * v.y + z * v.z + w * v.w; }
    float length() const { return sqrtf(x * x + y * y + z * z + w * w); }
    float length_squared() const { return x * x + y * y + z * z + w * w; }
    Vec4 normalize() const { float l = length(); return Vec4(x / l, y / l, z / l, w / l); }
};

struct Mat3x3{    
    union {
        struct {
            float        _11, _12, _13;
            float        _21, _22, _23;
            float        _31, _32, _33;
        };
        float m[3][3];
        float v[9];
    };

    Mat3x3() {}
    Mat3x3(float _11, float _12, float _13,
           float _21, float _22, float _23,
           float _31, float _32, float _33)
        : _11(_11), _12(_12), _13(_13)
        , _21(_21), _22(_22), _23(_23)
        , _31(_31), _32(_32), _33(_33) {}

    void set_zeros(){ for (int i=0; i<9; ++i) v[i] = 0.0f; }
    void set_ones(){ for (int i=0; i<9; ++i) v[i] = 1.0f; }
    void set_identity(){ set_zeros(); _11 = _22 = _33 = 1.0f; }

    static Mat3x3 zeros(){
        static Mat3x3 ret(0, 0, 0, 0, 0, 0, 0, 0, 0);
        return ret;
    }

    static Mat3x3 ones(){
        static Mat3x3 ret(1, 1, 1, 1, 1, 1, 1, 1, 1);
        return ret;
    }

    static Mat3x3 identity(){
        static Mat3x3 ret(1, 0, 0, 0, 1, 0, 0, 0, 1);
        return ret;
    }

    Mat3x3 operator+(const Mat3x3& other) const{ 
        Mat3x3 ret;
        for (int i=0; i<9; ++i) ret.v[i] = v[i] + other.v[i];
        return ret;
    }

    Mat3x3 operator-(const Mat3x3& other) const{ 
        Mat3x3 ret;
        for (int i=0; i<9; ++i) ret.v[i] = v[i] - other.v[i];
        return ret;
    }

    Mat3x3 operator*(float scalar) const{ 
        Mat3x3 ret;
        for (int i=0; i<9; ++i) ret.v[i] = v[i] * scalar;
        return ret;
    }

    Mat3x3 operator/(float scalar) const{ 
        Mat3x3 ret;
        for (int i=0; i<9; ++i) ret.v[i] = v[i] / scalar;
        return ret;
    }

    Mat3x3& operator+=(const Mat3x3& other){ 
        for (int i=0; i<9; ++i) v[i] += other.v[i];
        return *this;
    }

    Mat3x3& operator-=(const Mat3x3& other){ 
        for (int i=0; i<9; ++i) v[i] -= other.v[i];
        return *this;
    }

    Mat3x3& operator*=(float scalar){ 
        for (int i=0; i<9; ++i) v[i] *= scalar;
        return *this;
    }

    Mat3x3& operator/=(float scalar){ 
        for (int i=0; i<9; ++i) v[i] /= scalar;
        return *this;
    }

    Mat3x3 matmul(const Mat3x3& other) const{
        Mat3x3 ret;
        ret._11 = _11 * other._11 + _12 * other._21 + _13 * other._31;
        ret._12 = _11 * other._12 + _12 * other._22 + _13 * other._32;
        ret._13 = _11 * other._13 + _12 * other._23 + _13 * other._33;
        ret._21 = _21 * other._11 + _22 * other._21 + _23 * other._31;
        ret._22 = _21 * other._12 + _22 * other._22 + _23 * other._32;
        ret._23 = _21 * other._13 + _22 * other._23 + _23 * other._33;
        ret._31 = _31 * other._11 + _32 * other._21 + _33 * other._31;
        ret._32 = _31 * other._12 + _32 * other._22 + _33 * other._32;
        ret._33 = _31 * other._13 + _32 * other._23 + _33 * other._33;
        return ret;
    }

    Vec3 matmul(const Vec3& other) const{
        Vec3 ret;
        ret.x = _11 * other.x + _12 * other.y + _13 * other.z;
        ret.y = _21 * other.x + _22 * other.y + _23 * other.z;
        ret.z = _31 * other.x + _32 * other.y + _33 * other.z;
        return ret;
    }

    bool operator==(const Mat3x3& other) const{
        for (int i=0; i<9; ++i){
            if (!isclose(v[i], other.v[i])) return false;
        }
        return true;
    }

    bool operator!=(const Mat3x3& other) const{
        for (int i=0; i<9; ++i){
            if (!isclose(v[i], other.v[i])) return true;
        }
        return false;
    }

    float determinant() const{
        return _11 * _22 * _33 + _12 * _23 * _31 + _13 * _21 * _32
             - _11 * _23 * _32 - _12 * _21 * _33 - _13 * _22 * _31;
    }

    Mat3x3 transpose() const{
        Mat3x3 ret;
        ret._11 = _11;  ret._12 = _21;  ret._13 = _31;
        ret._21 = _12;  ret._22 = _22;  ret._23 = _32;
        ret._31 = _13;  ret._32 = _23;  ret._33 = _33;
        return ret;
    }

    bool inverse(Mat3x3& ret) const{
        float det = determinant();
        if (fabsf(det) < kEpsilon) return false;
        float inv_det = 1.0f / det;
        ret._11 = (_22 * _33 - _23 * _32) * inv_det;
        ret._12 = (_13 * _32 - _12 * _33) * inv_det;
        ret._13 = (_12 * _23 - _13 * _22) * inv_det;
        ret._21 = (_23 * _31 - _21 * _33) * inv_det;
        ret._22 = (_11 * _33 - _13 * _31) * inv_det;
        ret._23 = (_13 * _21 - _11 * _23) * inv_det;
        ret._31 = (_21 * _32 - _22 * _31) * inv_det;
        ret._32 = (_12 * _31 - _11 * _32) * inv_det;
        ret._33 = (_11 * _22 - _12 * _21) * inv_det;
        return true;
    }

    /*************** affine transformations ***************/
    static Mat3x3 trs(Vec2 t, float radian, Vec2 s){
        float cr = cosf(radian);
        float sr = sinf(radian);
        return Mat3x3(s.x * cr,   -s.y * sr,  t.x,
                      s.x * sr,   s.y * cr,   t.y,
                      0.0f,       0.0f,       1.0f);
    }

    bool is_affine() const{
        float det = _11 * _22 - _12 * _21;
        if(fabsf(det) < kEpsilon) return false;
        return _31 == 0.0f && _32 == 0.0f && _33 == 1.0f;
    }

    Vec2 translation() const { return Vec2(_13, _23); }
    float rotation() const { return atan2f(_21, _11); }
    Vec2 scale() const {
        return Vec2(
            sqrtf(_11 * _11 + _21 * _21),
            sqrtf(_12 * _12 + _22 * _22)
        );
    }

    Vec2 transform_point(Vec2 vec) const {
        return Vec2(_11 * vec.x + _12 * vec.y + _13, _21 * vec.x + _22 * vec.y + _23);
    }

    Vec2 transform_vector(Vec2 vec) const {
        return Vec2(_11 * vec.x + _12 * vec.y, _21 * vec.x + _22 * vec.y);
    }
};

struct PyVec2;
struct PyVec3;
struct PyVec4;
struct PyMat3x3;
PyObject* py_var(VM*, Vec2);
PyObject* py_var(VM*, const PyVec2&);
PyObject* py_var(VM*, Vec3);
PyObject* py_var(VM*, const PyVec3&);
PyObject* py_var(VM*, Vec4);
PyObject* py_var(VM*, const PyVec4&);
PyObject* py_var(VM*, const Mat3x3&);
PyObject* py_var(VM*, const PyMat3x3&);


struct PyVec2: Vec2 {
    PY_CLASS(PyVec2, linalg, vec2)

    PyVec2() : Vec2() {}
    PyVec2(const Vec2& v) : Vec2(v) {}
    PyVec2(const PyVec2& v) : Vec2(v) {}

    static void _register(VM* vm, PyObject* mod, PyObject* type);
};

struct PyVec3: Vec3 {
    PY_CLASS(PyVec3, linalg, vec3)

    PyVec3() : Vec3() {}
    PyVec3(const Vec3& v) : Vec3(v) {}
    PyVec3(const PyVec3& v) : Vec3(v) {}

    static void _register(VM* vm, PyObject* mod, PyObject* type);
};

struct PyVec4: Vec4{
    PY_CLASS(PyVec4, linalg, vec4)

    PyVec4(): Vec4(){}
    PyVec4(const Vec4& v): Vec4(v){}
    PyVec4(const PyVec4& v): Vec4(v){}

    static void _register(VM* vm, PyObject* mod, PyObject* type);
};

struct PyMat3x3: Mat3x3{
    PY_CLASS(PyMat3x3, linalg, mat3x3)

    PyMat3x3(): Mat3x3(){}
    PyMat3x3(const Mat3x3& other): Mat3x3(other){}
    PyMat3x3(const PyMat3x3& other): Mat3x3(other){}

    static void _register(VM* vm, PyObject* mod, PyObject* type);
};

inline PyObject* py_var(VM* vm, Vec2 obj){ return VAR_T(PyVec2, obj); }
inline PyObject* py_var(VM* vm, const PyVec2& obj){ return VAR_T(PyVec2, obj);}

inline PyObject* py_var(VM* vm, Vec3 obj){ return VAR_T(PyVec3, obj); }
inline PyObject* py_var(VM* vm, const PyVec3& obj){ return VAR_T(PyVec3, obj);}

inline PyObject* py_var(VM* vm, Vec4 obj){ return VAR_T(PyVec4, obj); }
inline PyObject* py_var(VM* vm, const PyVec4& obj){ return VAR_T(PyVec4, obj);}

inline PyObject* py_var(VM* vm, const Mat3x3& obj){ return VAR_T(PyMat3x3, obj); }
inline PyObject* py_var(VM* vm, const PyMat3x3& obj){ return VAR_T(PyMat3x3, obj); }

template<> inline Vec2 py_cast<Vec2>(VM* vm, PyObject* obj) { return CAST(PyVec2&, obj); }
template<> inline Vec3 py_cast<Vec3>(VM* vm, PyObject* obj) { return CAST(PyVec3&, obj); }
template<> inline Vec4 py_cast<Vec4>(VM* vm, PyObject* obj) { return CAST(PyVec4&, obj); }
template<> inline Mat3x3 py_cast<Mat3x3>(VM* vm, PyObject* obj) { return CAST(PyMat3x3&, obj); }

template<> inline Vec2 _py_cast<Vec2>(VM* vm, PyObject* obj) { return _CAST(PyVec2&, obj); }
template<> inline Vec3 _py_cast<Vec3>(VM* vm, PyObject* obj) { return _CAST(PyVec3&, obj); }
template<> inline Vec4 _py_cast<Vec4>(VM* vm, PyObject* obj) { return _CAST(PyVec4&, obj); }
template<> inline Mat3x3 _py_cast<Mat3x3>(VM* vm, PyObject* obj) { return _CAST(PyMat3x3&, obj); }

inline void add_module_linalg(VM* vm){
    PyObject* linalg = vm->new_module("linalg");
    PyVec2::register_class(vm, linalg);
    PyVec3::register_class(vm, linalg);
    PyVec4::register_class(vm, linalg);
    PyMat3x3::register_class(vm, linalg);
}

static_assert(sizeof(Py_<PyMat3x3>) <= 64);

}   // namespace pkpy