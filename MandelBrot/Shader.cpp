
#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertex_shader_path, const char* fragment_shader_path) {
    std::string vertex_code = read_shader_file(vertex_shader_path);
    std::string fragment_code = read_shader_file(fragment_shader_path);

    unsigned int vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    const char* vShaderCode = vertex_code.c_str();
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fShaderCode = fragment_code.c_str();
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    program_ID = glCreateProgram();
    glAttachShader(program_ID, vertex);
    glAttachShader(program_ID, fragment);
    glLinkProgram(program_ID);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(program_ID);
}

void Shader::use_shader() {
    glUseProgram(program_ID);
}

void Shader::set_float(const std::string& name, float value) {
    glUniform1f(glGetUniformLocation(program_ID, name.c_str()), value);
}

void Shader::set_vec4(const std::string& name, glm::vec4 value) {
    glUniform4fv(glGetUniformLocation(program_ID, name.c_str()), 1, &value[0]);
}

std::string Shader::read_shader_file(const char* file_path) {
    std::ifstream shader_file;
    shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::stringstream shader_stream;
    
    try {
        shader_file.open(file_path);
        shader_stream << shader_file.rdbuf();
        shader_file.close();
    } catch (std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

    return shader_stream.str();
}

void Shader::add_shader(unsigned int program, const char* shader_code, GLenum shader_type) {
    unsigned int shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_code, NULL);
    glCompileShader(shader);
    glAttachShader(program, shader);
    glDeleteShader(shader);
}
