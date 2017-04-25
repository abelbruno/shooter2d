#ifndef _SHADERS_UTIL_H_INCLUDED_
#define _SHADERS_UTIL_H_INCLUDED_

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>


//Attach shader to a program
int attachShader(GLuint prg, GLenum type, const char* name);


GLuint
loadGLSLProgram(const char* vertFileName, const char* geomFileName, const char *fragFileName);

GLuint
loadGLSLComputeProgram(const char* compFileName);

#endif // _SHADERS_UTIL_H_INCLUDED_
