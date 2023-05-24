#include "vertexbuffer.h"
#include "renderer.h"

VertexBuffer::VertexBuffer(const void* data , const unsigned int size)// NOTE(Raghav Gohil): create the buffer..
{
    
    GLCall(glGenBuffers(1 , &m_renderer_id));// NOTE(Raghav Gohil): the vbo names are stored here
    GLCall(glBindBuffer(GL_ARRAY_BUFFER , m_renderer_id));// NOTE(Raghav Gohil): bound the buffer as an array type
    GLCall(glBufferData(GL_ARRAY_BUFFER, size , data , GL_STATIC_DRAW));// NOTE(Raghav Gohil): vertex attrib array position attribute
    
    
}

VertexBuffer::~VertexBuffer()// NOTE(Raghav Gohil): destroy the buffer
{
    
    GLCall(glDeleteBuffers(1 , &m_renderer_id));
    
}

void VertexBuffer::bind() const// NOTE(Raghav Gohil):  bind the buffer
{
    
    GLCall(glBindBuffer(GL_ARRAY_BUFFER , m_renderer_id));
    
}

void VertexBuffer::unbind() const// NOTE(Raghav Gohil): unbind the buffer
{
    
    GLCall(glBindBuffer(GL_ARRAY_BUFFER , 0));
    
}
