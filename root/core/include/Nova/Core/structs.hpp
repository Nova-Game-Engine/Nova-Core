#pragma once
#include <cglm/cam.h>
#include <cglm/cglm.h>
#include <cglm/clipspace/persp_rh_no.h>
#include <cglm/euler.h>
#include <cglm/quat.h>
#include <cglm/types.h>
#include <cglm/vec3.h>

// just a wrapper for cglm
namespace Nova::Core {
    struct Vec2 {
        vec2 v;

        Vec2() { glm_vec2_zero(v); }
        Vec2(float x, float y) { v[0] = x; v[1] = y; }
        Vec2(const vec2 other) { glm_vec2_copy(const_cast<float*>(other), v); }

        operator vec2&() { return v; }
        operator const vec2&() const { return v; }

        float& operator[](size_t i) { return v[i]; }
        const float& operator[](size_t i) const { return v[i]; }

        Vec2 operator+(const Vec2& rhs) const {
            Vec2 out;
            glm_vec2_add(const_cast<float*>(v),
                        const_cast<float*>(rhs.v),
                        out.v);
            return out;
        }

        Vec2 operator-(const Vec2& rhs) const {
            Vec2 out;
            glm_vec2_sub(const_cast<float*>(v),
                        const_cast<float*>(rhs.v),
                        out.v);
            return out;
        }

        Vec2 operator*(float s) const {
            Vec2 out;
            glm_vec2_scale(const_cast<float*>(v), s, out.v);
            return out;
        }

        Vec2 operator/(float s) const {
            Vec2 out;
            glm_vec2_scale(const_cast<float*>(v), 1.0f / s, out.v);
            return out;
        }

        Vec2& operator+=(const Vec2& rhs) {
            glm_vec2_add(v, const_cast<float*>(rhs.v), v);
            return *this;
        }

        Vec2& operator-=(const Vec2& rhs) {
            glm_vec2_sub(v, const_cast<float*>(rhs.v), v);
            return *this;
        }

        Vec2& operator*=(float s) {
            glm_vec2_scale(v, s, v);
            return *this;
        }

        Vec2& operator/=(float s) {
            glm_vec2_scale(v, 1.0f / s, v);
            return *this;
        }

        float length() const {
            return glm_vec2_norm(const_cast<float*>(v));
        }

        Vec2 normalized() const {
            Vec2 out;
            glm_vec2_normalize_to(const_cast<float*>(v), out.v);
            return out;
        }

        void normalize() {
            glm_vec2_normalize(v);
        }
    };

    struct Vec3 {
        vec3 v;

        Vec3() {glm_vec3_zero(v);}
        Vec3(float x, float y, float z) {v[0] = x;v[1] = y;v[2] = z;}
        Vec3(const vec3 other) {
            glm_vec3_copy(const_cast<float*>(other), v);
        }

        operator vec3&() {return v;}
        operator const vec3&() const {return v;}

        float& operator[](size_t i) {return v[i];}
        const float& operator[](size_t i) const {return v[i];}

        Vec3 operator+(const Vec3& rhs) const {
            Vec3 out;
            glm_vec3_add(const_cast<float*>(v),
                        const_cast<float*>(rhs.v),
                        out.v);
            return out;
        }

        Vec3 operator-(const Vec3& rhs) const {
            Vec3 out;
            glm_vec3_sub(const_cast<float*>(v),
                        const_cast<float*>(rhs.v),
                        out.v);
            return out;
        }

        Vec3 operator*(float s) const {
            Vec3 out;
            glm_vec3_scale(const_cast<float*>(v), s, out.v);
            return out;
        }

        Vec3 operator/(float s) const {
            Vec3 out;
            glm_vec3_scale(const_cast<float*>(v), 1.0f / s, out.v);
            return out;
        }

        Vec3& operator+=(const Vec3& rhs) {
            glm_vec3_add(v, const_cast<float*>(rhs.v), v);
            return *this;
        }

        Vec3& operator-=(const Vec3& rhs) {
            glm_vec3_sub(v, const_cast<float*>(rhs.v), v);
            return *this;
        }

        Vec3& operator*=(float s) {
            glm_vec3_scale(v, s, v);
            return *this;
        }

        Vec3& operator/=(float s) {
            glm_vec3_scale(v, 1.0f / s, v);
            return *this;
        }

        float length() const {
            return glm_vec3_norm(const_cast<float*>(v));
        }

        Vec3 normalized() const {
            Vec3 out;
            glm_vec3_normalize_to(const_cast<float*>(v), out.v);
            return out;
        }

        void normalize() {
            glm_vec3_normalize(v);
        }
    };

    struct alignas(16) Vec4 {
        alignas(16) vec4 v;

        Vec4() { glm_vec4_zero(v); }
        Vec4(float x, float y, float z, float w) {
            v[0] = x; v[1] = y; v[2] = z; v[3] = w;
        }
        Vec4(const vec4 other) { glm_vec4_copy(const_cast<float*>(other), v); }

        operator vec4&() { return v; }
        operator const vec4&() const { return v; }

        float& operator[](size_t i) { return v[i]; }
        const float& operator[](size_t i) const { return v[i]; }

        Vec4 operator+(const Vec4& rhs) const {
            Vec4 out;
            glm_vec4_add(const_cast<float*>(v),
                        const_cast<float*>(rhs.v),
                        out.v);
            return out;
        }

        Vec4 operator-(const Vec4& rhs) const {
            Vec4 out;
            glm_vec4_sub(const_cast<float*>(v),
                        const_cast<float*>(rhs.v),
                        out.v);
            return out;
        }

        Vec4 operator*(float s) const {
            Vec4 out;
            glm_vec4_scale(const_cast<float*>(v), s, out.v);
            return out;
        }

        Vec4 operator/(float s) const {
            Vec4 out;
            glm_vec4_scale(const_cast<float*>(v), 1.0f / s, out.v);
            return out;
        }

        Vec4& operator+=(const Vec4& rhs) {
            glm_vec4_add(v, const_cast<float*>(rhs.v), v);
            return *this;
        }

        Vec4& operator-=(const Vec4& rhs) {
            glm_vec4_sub(v, const_cast<float*>(rhs.v), v);
            return *this;
        }

        Vec4& operator*=(float s) {
            glm_vec4_scale(v, s, v);
            return *this;
        }

        Vec4& operator/=(float s) {
            glm_vec4_scale(v, 1.0f / s, v);
            return *this;
        }

        float length() const {
            return glm_vec4_norm(const_cast<float*>(v));
        }

        Vec4 normalized() const {
            Vec4 out;
            glm_vec4_normalize_to(const_cast<float*>(v), out.v);
            return out;
        }

        void normalize() {
            glm_vec4_normalize(v);
        }
    };

    struct alignas(16) Mat4 {
        alignas(16) mat4 m;

        Mat4() {
            glm_mat4_identity(m);
        }

        Mat4(const mat4& other) {
            glm_mat4_copy(const_cast<mat4&>(other), m);
        }




        operator mat4&() { return m; }
        operator const mat4&() const { return m; }

        float* operator[](size_t i) { return m[i]; }
        const float* operator[](size_t i) const { return m[i]; }

        // Matrix multiplication
        Mat4 operator*(const Mat4& rhs) const {
            Mat4 out;
            glm_mat4_mul(const_cast<mat4&>(m),
                        const_cast<mat4&>(rhs.m),
                        out.m);
            return out;
        }

        Mat4& operator*=(const Mat4& rhs) {
            mat4 tmp;
            glm_mat4_mul(m, const_cast<mat4&>(rhs.m), tmp);
            glm_mat4_copy(tmp, m);
            return *this;
        }

        Vec3 operator*(const Vec3& v) const {
            Vec3 out;
            glm_mat4_mulv3(
                const_cast<mat4&>(m),
                const_cast<float*>(v.v),
                1.0f,
                out.v
            );
            return out;
        }

        Vec4 operator*(const Vec4& v) const {
            Vec4 out;
            glm_mat4_mulv(
                const_cast<mat4&>(m),
                const_cast<float*>(v.v),
                out.v
            );
            return out;
        }

        static Mat4 translation(const Vec3& t) {
            Mat4 out;
            glm_translate_make(out.m, const_cast<float*>(t.v));
            return out;
        }

        static Mat4 scale(const Vec3& s) {
            Mat4 out;
            glm_scale_make(out.m, const_cast<float*>(s.v));
            return out;
        }

        static Mat4 rotation(float angleRad, const Vec3& axis) {
            Mat4 out;
            glm_rotate_make(out.m, angleRad, const_cast<float*>(axis.v));
            return out;
        }

        Mat4 transposed() const {
            Mat4 out;
            glm_mat4_transpose_to(const_cast<mat4&>(m), out.m);
            return out;
        }

        void transpose() {
            glm_mat4_transpose(m);
        }

        Mat4 inverted() const {
            Mat4 out;
            glm_mat4_inv(const_cast<mat4&>(m), out.m);
            return out;
        }

        void invert() {
            glm_mat4_inv(m, m);
        }

        Vec3 transformDirection(const Vec3& v) const {
            Vec3 out;
            glm_mat4_mulv3(const_cast<mat4&>(m),
                            const_cast<float*>(v.v),
                            0.0f,
                            out.v);
            return out;
        }

        static Mat4 lookAt(const Vec3& eye, const Vec3& center, const Vec3& up) {
            Mat4 out;
            glm_lookat(const_cast<float*>(eye.v), const_cast<float*>(center.v), const_cast<float*>(up.v), out.m);
            return out;
        }

        static Mat4 perspective(float fovy, float aspect, float near, float far) {
            Mat4 out;
            glm_perspective(fovy, aspect, near, far, out.m);
            return out;
        }

    };

    struct alignas(16) Quat {
        alignas(16) versor q;

        Quat() {
            glm_quat_identity(q);
        }

        Quat(float x, float y, float z, float w) {
            q[0] = x; q[1] = y; q[2] = z; q[3] = w;
        }

        Quat(const versor other) {
            glm_quat_copy(const_cast<float*>(other), q);
        }

        operator versor&() { return q; }
        operator const versor&() const { return q; }

        float& operator[](size_t i) { return q[i]; }
        const float& operator[](size_t i) const { return q[i]; }

        Quat operator*(const Quat& rhs) const {
            Quat out;
            glm_quat_mul(const_cast<float*>(q),
                        const_cast<float*>(rhs.q),
                        out.q);
            return out;
        }

        Quat& operator*=(const Quat& rhs) {
            versor tmp;
            glm_quat_mul(q, const_cast<float*>(rhs.q), tmp);
            glm_quat_copy(tmp, q);
            return *this;
        }

        Vec3 operator*(const Vec3& v) const {
            Vec3 out;
            glm_quat_rotatev(const_cast<float*>(q),
                            const_cast<float*>(v.v),
                            out.v);
            return out;
        }

        void normalize() {
            glm_quat_normalize(q);
        }

        Quat normalized() const {
            Quat out;
            glm_quat_normalize_to(const_cast<float*>(q), out.q);
            return out;
        }

        Mat4 toMat4() const {
            Mat4 out;
            glm_quat_mat4(const_cast<float*>(q), out.m);
            return out;
        }

        static Quat fromAxisAngle(const Vec3& axis, float angleRad) {
            Quat out;
            glm_quatv(out.q, angleRad, const_cast<float*>(axis.v));
            return out;
        }

        static Quat fromEuler(float pitch, float yaw, float roll) {
            Vec3 angles(pitch, yaw, roll);
            Quat q;
            glm_euler_xyz_quat(angles.v, q.q);
            return q;
        }


        
        static Quat fromEulerXYZ(float pitch, float yaw, float roll) {
            Vec3 angles(pitch, yaw, roll);
            Quat out;
            glm_euler_xyz_quat(const_cast<float*>(angles.v), out.q);
            return out;
        }

        Vec3 toEulerXYZ() const {
            Vec3 out;
            Mat4 mat;
            glm_quat_mat4(const_cast<float*>(q), mat.m);
            glm_euler_angles(mat.m, out.v);
            return out;
        }
    };

    struct Transform {
        Vec3 position;
        Quat rotation;
        Vec3 scale;

        Transform()
            : position(0.0f, 0.0f, 0.0f),
              rotation(0.0f, 0.0f, 0.0f, 1.0f),
              scale(1.0f, 1.0f, 1.0f) {}

        Transform(const Vec3& pos, const Quat& rot, const Vec3& scl)
            : position(pos), rotation(rot), scale(scl) {}

        Mat4 toMat4() const {
            Mat4 t = Mat4::translation(position);
            Mat4 r = rotation.toMat4();
            Mat4 s = Mat4::scale(scale);
            return t * r * s;
        }

        void set(const Vec3& pos, const Quat& rot, const Vec3& scl) {
            position = pos;
            rotation = rot;
            scale    = scl;
        }

        // translate in world space
        void translate(const Vec3& delta) {
            position += delta;
        }

        // rotate in local space
        void rotateLocal(const Quat& delta) {
            rotation = delta * rotation;
        }

        // rotate in world space
        void rotateWorld(const Quat& delta) {
            rotation = rotation * delta;
        }

        // directions in world space (right-handed; Z-forward)
        Vec3 forward() const {
            return rotation * Vec3(0.0f, 0.0f, -1.0f);
        }

        Vec3 up() const {
            return rotation * Vec3(0.0f, 1.0f, 0.0f);
        }

        Vec3 right() const {
            return rotation * Vec3(1.0f, 0.0f, 0.0f);
        }
    };

    // other things are included in cglm and thus don't need redefinitio
};