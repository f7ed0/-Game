#define GL_GLEXT_PROTOTYPES

#include "logger/Logger.hpp"
#include <GL/gl.h>
#include <GL/glext.h>
#include <fstream>
#include <graphics/shader.hpp>
#include <iostream>
#include <sstream>

using namespace game3D::graphics;

Shader::Shader() { this->ID = 100000000; }

Shader::Shader(const char *vertexPath, const char *fragmentPath) {

  // 1. Reading file
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;
  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);

    std::stringstream vShaderStream, fShaderStream;

    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vShaderFile.close();
    fShaderFile.close();

    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();

  } catch (std::ifstream::failure *e) {
    game3D::Logger::error("ERROR::SHADER::FILE_NOT_READ_SUCESSFULLY");
  }

  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();

  // 2. Compile Shader
  unsigned int vertex, fragment;
  int success;
  char infoLog[512] = "";

  // 2.a vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);

  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

  if (success == GL_FALSE) {
    int l;
    glGetShaderInfoLog(vertex, 512, &l, infoLog);
    std::stringstream ss;
    ss << "ERROR::SHADER::VERTEX::COMPILATION_FAILED : " << l << infoLog;
    game3D::Logger::error(ss.str());
    throw -1;
  }

  // 2.b fragment shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);

  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

  if (success == GL_FALSE) {
    int l;
    glGetShaderInfoLog(vertex, 512, &l, infoLog);
    std::stringstream ss;
    ss << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED : " << l << infoLog;
    game3D::Logger::error(ss.str());
    throw -1;
  }

  this->ID = glCreateProgram();
  glAttachShader(this->ID, vertex);
  glAttachShader(this->ID, fragment);
  glLinkProgram(this->ID);
  // print linking errors if any
  glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
  if (success == GL_FALSE) {
    glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << infoLog
              << std::endl;
    throw -1;
  }

  // delete the shaders as they're linked into our program now and no longer
  // necessary
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::use() {
  // std::stringstream ss;
  // ss << "USING SHADER : " << this->ID;
  // game3D::Logger::debug(ss.str());
  if (glIsProgram(this->ID) == GL_TRUE) {
    glUseProgram(this->ID);
    GLfloat projection_matrix[16];
    glGetFloatv(GL_PROJECTION_MATRIX, projection_matrix);
    int pm_handle = glGetUniformLocation(this->ID, "projection_matrix");
    glUniformMatrix4fv(pm_handle, 1, GL_FALSE, projection_matrix);
  }
}

void Shader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
