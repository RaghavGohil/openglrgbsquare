/* date = October 30th 2021 7:53 pm */

#ifndef RENDERER_H
#define RENDERER_H

#endif //RENDERER_H

#include "GLEW\include\GL\glew.h"

// TODO(Raghav Gohil): remove this defines and create a new method to deal with errors.

#define ASSERT(x) if((x)) __debugbreak(); // NOTE(Raghav Gohil): this is compiler intrinsic
#define GLCall(x) GL_clear_error();\
x;\
ASSERT(GL_log_call(#x,__FILE__,__LINE__));

void GL_clear_error();

bool GL_log_call(const char* function , const char* file , int line);
