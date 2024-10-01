
#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    unsigned int program_ID;

    Shader(const char* vertex_shader_path, const char* fragment_shader_path);  // Constructor declaration
    ~Shader();  // Destructor declaration

    void use_shader();  // Function declaration

    void set_float(const std::string& name, float value);  // Function declaration
    void set_vec4(const std::string& name, glm::vec4 value);  // Function declaration

private:
    std::string read_shader_file(const char* file_path);  // Private function declaration
    void add_shader(unsigned int program, const char* shader_code, GLenum shader_type);  // Private function declaration
};

#endif
