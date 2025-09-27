
struct mat4 {
  float elements[4 * 4];
} typedef mat4;

struct vec3 {
  float elements[3];
} typedef vec3;

// Matrix operations
mat4 create_matrix_transform(vec3 translation);
mat4 create_z_rotation(float angle);
mat4 create_model_transform(vec3 translation, float rotation_angle);
mat4 create_lookat_matrix(vec3 from, vec3 to);
mat4 create_perspective_matrix(float fov, float aspect, float near, float far);

// Vector operations
float dot(vec3 a, vec3 b);
vec3 cross(vec3 a, vec3 b);
vec3 normalize(vec3 v);