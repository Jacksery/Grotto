class Material {
public:
  Material(const char *texturePath);
  ~Material();
  void use(int unit = 0);

private:
  unsigned int textureID;
};