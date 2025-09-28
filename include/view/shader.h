#pragma once
#include "config/config.h"

unsigned int makeShaderModule(const std::string &filepath,
                              unsigned int module_type);

unsigned int makeShader(const std::string &vertex_filepath,
                        const std::string &fragment_filepath);