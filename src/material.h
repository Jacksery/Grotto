class Material {
public:
  Material(const char *texturePath);
  ~Material();
  void use();

private:
  unsigned int textureID;
};