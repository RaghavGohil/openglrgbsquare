#include "renderer.h"
#include <iostream>

void GL_clear_error() 
{
    
    while (glGetError() != GL_NO_ERROR);
    
}

bool GL_log_call(const char* function , const char* file , int line) 
{
    
    while (GLenum error = glGetError()) 
    {
        
        std::cout << "Error:"<< " " << function << " " << file << " " << line << "  " << error << std::endl;
        return true;
        
    }
    
    return false;
    
}