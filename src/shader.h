#pragma once
#include <string>
int loadShader(std::string filename, GLchar** ShaderSource);
int unloadShader(GLchar** ShaderSource);
GLuint makeShaderProgram(GLchar *pfragshadersrc, GLchar *pvertshadersrc);
