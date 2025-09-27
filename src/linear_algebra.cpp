#include "linear_algebra.h"
#include <cmath>

#define PI 3.14159265358979323846

mat4 create_matrix_transform(vec3 translation) {
  mat4 matrix = {};

  // column-major order
  // column 1
  matrix.elements[0] = 1.0f;
  matrix.elements[1] = 0.0f;
  matrix.elements[2] = 0.0f;
  matrix.elements[3] = 0.0f;
  // column 2
  matrix.elements[4] = 0.0f;
  matrix.elements[5] = 1.0f;
  matrix.elements[6] = 0.0f;
  matrix.elements[7] = 0.0f;
  // column 3
  matrix.elements[8] = 0.0f;
  matrix.elements[9] = 0.0f;
  matrix.elements[10] = 1.0f;
  matrix.elements[11] = 0.0f;
  // column 4
  matrix.elements[12] = translation.elements[0];
  matrix.elements[13] = translation.elements[1];
  matrix.elements[14] = translation.elements[2];
  matrix.elements[15] = 1.0f;

  return matrix;
}

mat4 create_z_rotation(float angle) {
  mat4 matrix = {};

  angle = angle * (PI / 180.0f); // convert to radians

  float c = cosf(angle);
  float s = sinf(angle);

  // column-major order
  // column 1
  matrix.elements[0] = c;
  matrix.elements[1] = s;
  matrix.elements[2] = 0.0f;
  matrix.elements[3] = 0.0f;
  // column 2
  matrix.elements[4] = -s;
  matrix.elements[5] = c;
  matrix.elements[6] = 0.0f;
  matrix.elements[7] = 0.0f;
  // column 3
  matrix.elements[8] = 0.0f;
  matrix.elements[9] = 0.0f;
  matrix.elements[10] = 1.0f;
  matrix.elements[11] = 0.0f;
  // column 4
  matrix.elements[12] = 0.0f;
  matrix.elements[13] = 0.0f;
  matrix.elements[14] = 0.0f;
  matrix.elements[15] = 1.0f;

  return matrix;
}

mat4 create_model_transform(vec3 translation, float rotation_angle) {
  mat4 matrix;

  float c = cosf(rotation_angle * (PI / 180.0f));
  float s = sinf(rotation_angle * (PI / 180.0f));

  // column-major order
  // column 1
  matrix.elements[0] = c;
  matrix.elements[1] = s;
  matrix.elements[2] = 0.0f;
  matrix.elements[3] = 0.0f;
  // column 2
  matrix.elements[4] = -s;
  matrix.elements[5] = c;
  matrix.elements[6] = 0.0f;
  matrix.elements[7] = 0.0f;
  // column 3
  matrix.elements[8] = 0.0f;
  matrix.elements[9] = 0.0f;
  matrix.elements[10] = 1.0f;
  matrix.elements[11] = 0.0f;
  // column 4
  matrix.elements[12] = translation.elements[0];
  matrix.elements[13] = translation.elements[1];
  matrix.elements[14] = translation.elements[2];
  matrix.elements[15] = 1.0f;

  return matrix;
}

mat4 create_lookat_matrix(vec3 from, vec3 to) {
  vec3 globalUp = {.elements = {0.0f, 0.0f, 1.0f}};
  vec3 forward =
      normalize((vec3){.elements = {to.elements[0] - from.elements[0],
                                    to.elements[1] - from.elements[1],
                                    to.elements[2] - from.elements[2]}});
  vec3 right = normalize(cross(forward, globalUp));
  vec3 up = cross(right, forward);

  mat4 matrix = {};
  // column-major order
  // column 1
  matrix.elements[0] = right.elements[0];
  matrix.elements[1] = up.elements[0];
  matrix.elements[2] = -forward.elements[0];
  matrix.elements[3] = 0.0f;
  // column 2
  matrix.elements[4] = right.elements[1];
  matrix.elements[5] = up.elements[1];
  matrix.elements[6] = -forward.elements[1];
  matrix.elements[7] = 0.0f;
  // column 3
  matrix.elements[8] = right.elements[2];
  matrix.elements[9] = up.elements[2];
  matrix.elements[10] = -forward.elements[2];
  matrix.elements[11] = 0.0f;
  // column 4
  matrix.elements[12] = -dot(right, from);
  matrix.elements[13] = -dot(up, from);
  matrix.elements[14] = dot(forward, from);
  matrix.elements[15] = 1.0f;

  return matrix;
};

mat4 create_perspective_matrix(float fov, float aspect, float near, float far) {
  mat4 matrix = {};

  fov = fov * (PI / 360.0f); // convert to radians
  float t = tanf(fov);
  float n = -near;
  float f = -far;

  for (int i = 0; i < 16; ++i) {
    matrix.elements[i] = 0.0f;
  }

  matrix.elements[0] = 1.0f / (aspect * t);
  matrix.elements[5] = 1.0f / t;
  matrix.elements[10] = -(f + n) / (n - f);
  matrix.elements[11] = -1.0f;
  matrix.elements[14] = (2 * f * n) / (n - f);

  return matrix;
}

float dot(vec3 a, vec3 b) {
  return a.elements[0] * b.elements[0] + a.elements[1] * b.elements[1] +
         a.elements[2] * b.elements[2];
}

vec3 cross(vec3 a, vec3 b) {
  vec3 result;
  result.elements[0] =
      a.elements[1] * b.elements[2] - a.elements[2] * b.elements[1];
  result.elements[1] =
      a.elements[2] * b.elements[0] - a.elements[0] * b.elements[2];
  result.elements[2] =
      a.elements[0] * b.elements[1] - a.elements[1] * b.elements[0];
  return result;
}

vec3 normalize(vec3 v) {
  float length = sqrtf(dot(v, v));
  vec3 result;
  if (length > 0.0f) {
    result.elements[0] = v.elements[0] / length;
    result.elements[1] = v.elements[1] / length;
    result.elements[2] = v.elements[2] / length;
  } else {
    result.elements[0] = 0.0f;
    result.elements[1] = 0.0f;
    result.elements[2] = 0.0f;
  }
  return result;
}