#ifndef vtchristiansen_shaders_H_
#define vtchristiansen_shaders_H_

#include <SDL2/SDL.h>
#include <GL/glew.h>
//#include "GL/freeglut.h"
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;

GLuint fragShader(const GLchar* filename);
GLuint vertShader(const GLchar* filename);
const GLchar* readFile(const char* filename);
GLuint createProgram(GLuint fragshader,GLuint vertshader);


GLuint fragShader(const GLchar* filename){
  GLuint fragshader=glCreateShader(GL_FRAGMENT_SHADER);
  
  const GLchar* source=readFile(filename);
  glShaderSource(fragshader, 1, &source, NULL);
  
  glCompileShader(fragshader);
  
  GLint compileStatus;
  glGetShaderiv(fragshader, GL_COMPILE_STATUS, &compileStatus);
  
  if(!compileStatus){
    GLint logSize;
    glGetShaderiv(fragshader, GL_INFO_LOG_LENGTH, &logSize);
    
    GLchar* infoLog = new GLchar[logSize+1];
    glGetShaderInfoLog(fragshader,logSize,&logSize,infoLog);
    fprintf(stderr,"\nCompile failure in %u shader: %s\n Error message:\n%s\n",infoLog);
    delete[] infoLog;
  }
  return fragshader;
}


GLuint vertShader(const char* filename){
  GLuint vertshader=glCreateShader(GL_VERTEX_SHADER);
  
  const GLchar* source=readFile(filename);
  glShaderSource(vertshader, 1, &source, NULL);
  
  glCompileShader(vertshader);
  
  GLint compileStatus;
  glGetShaderiv(vertshader, GL_COMPILE_STATUS, &compileStatus);
  
  if(!compileStatus){
    GLint logSize;
    glGetShaderiv(vertshader, GL_INFO_LOG_LENGTH, &logSize);
    
    GLchar* infoLog = new GLchar[logSize+1];
    glGetShaderInfoLog(vertshader,logSize,&logSize,infoLog);
    fprintf(stderr,"\nCompile failure in %u shader: %s\n Error message:\n%s\n",infoLog);
    delete[] infoLog;
  }
  return vertshader;
}

GLuint createProgram(GLuint fragshader,GLuint vertshader){

  GLuint program=glCreateProgram();
  glAttachShader(program,fragshader);
  glAttachShader(program,vertshader);
  
  glBindAttribLocation(program, 0, "in_position");
  glBindAttribLocation(program, 1, "in_color");
  glLinkProgram(program);
  
  GLint linkStatus;
  glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
  
  if(!linkStatus){
    GLint logSize;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
    
    GLchar *infoLog = new GLchar[logSize+1];
    glGetProgramInfoLog(program,logSize,&logSize,infoLog);
    
    fprintf(stderr,"\nShader linking failed: %s\n",infoLog);
    delete[] infoLog;
  }
  
  return program;
}
  
const GLchar* readFile(const char* filename){
  
  FILE* shade = fopen(filename, "rb");
  
  if(!shade){
    fprintf(stderr,"unable to open file '%s'\n",filename);
    return NULL;
  }
  
  fseek(shade, 0, SEEK_END);
  long filesize=ftell(shade);
  fseek(shade, 0, SEEK_SET);
  
  
  GLchar* shadingSource= new GLchar[filesize+1];//
  fread(shadingSource, 1, filesize, shade);
  
  
  if(ftell(shade) == 0){
    fprintf(stderr, "File '%s' is empty.\n",filename);
    return NULL;
  }
  
  fclose(shade);
  
  shadingSource[filesize] = 0;
  
  return const_cast<const GLchar*>(shadingSource);
  
}

#endif
