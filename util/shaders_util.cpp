#include "shaders_util.h"

/***********************************************
* SHADERS
************************************************/

//Attach shader to a program
int attachShader(GLuint prg, GLenum type, const char* name)
{
    GLuint shader;
    FILE *fp;
    int size, compiled;
    char *src;

    fp = fopen(name, "rb");

    if (!fp)
    {
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    src = (char*) malloc(size);

    fseek(fp, 0, SEEK_SET);
    fread(src, sizeof(char), size, fp);
    fclose(fp);

    shader = glCreateShader(type);
    glShaderSource(shader, 1, (const char**)&src, (const GLint *) &size);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, (GLint *)&compiled);

    if(!compiled)
    {
        char log[2048];
        int len;

        glGetShaderInfoLog(shader, 2048, (GLsizei *)&len, log);
        printf("Info log: %s\n", log);
        glDeleteShader(shader);
        return 0;
    }

    free(src);

    glAttachShader(prg, shader);
    glDeleteShader(shader);

    return 1;
}

//Create shader program from vertex shader and geometry shader files
GLuint
loadGLSLProgram(const char* vertFileName, const char* geomFileName, const char *fragFileName)
{
    GLint linked;
    GLint success;
    GLuint program;

    program = glCreateProgram();

    if (vertFileName && !attachShader(program, GL_VERTEX_SHADER, vertFileName))
    {
        glDeleteProgram(program);
        fprintf(stderr, "Couldn't attach vertex shader from file %s\n", vertFileName);
        return 0;
    }
    if (geomFileName && !attachShader(program, GL_GEOMETRY_SHADER, geomFileName))
    {
        glDeleteProgram(program);
        fprintf(stderr, "Couldn't attach vertex shader from file %s\n", geomFileName);
        return 0;
    }
    if (fragFileName && !attachShader(program, GL_FRAGMENT_SHADER, fragFileName))
    {
        glDeleteProgram(program);
        fprintf(stderr, "Couldn't attach fragment shader from file %s\n", fragFileName);
        return 0;
    }

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    if (!linked)
    {
        glDeleteProgram(program);
        char temp[256];
        glGetProgramInfoLog(program, 256, 0, temp);
        fprintf(stderr, "Failed to link program: %s\n", temp);
        return 0;
    }

    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
    if (!success) {
        char temp[256];
        glGetProgramInfoLog(program, sizeof(temp), NULL, temp);
        fprintf(stderr, "Invalid shader program: '%s'\n", temp);
        exit(1);
    }

    return program;
}

//Create compute shader program from compute shader file
GLuint
loadGLSLComputeProgram(const char *compFileName)
{
    GLint linked;

    GLuint program = glCreateProgram();

    if (!attachShader(program, GL_COMPUTE_SHADER, compFileName))
    {
        glDeleteProgram(program);
        fprintf(stderr, "Couldn't attach compute shader from file %s\n", compFileName);
        return 0;
    }

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    if (!linked)
    {
        glDeleteProgram(program);
        char temp[256];
        glGetProgramInfoLog(program, 256, 0, temp);
        fprintf(stderr, "Failed to link compute program: %s\n", temp);
        glDeleteProgram(program);
        fprintf(stderr, "Couldn't compile compute shader from file %s\n", compFileName);
        return 0;
    }

    printf("compute shader linked\n");

    return program;
}
