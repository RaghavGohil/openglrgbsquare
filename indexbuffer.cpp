#include "indexbuffer.h"
#include "renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data , unsigned int count):m_count(count)// NOTE(Raghav Gohil): create the buffer..
{

    GLCall(glGenBuffers(1 , &m_renderer_id));// NOTE(Raghav Gohil): the vbo names are stored here
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , m_renderer_id));// NOTE(Raghav Gohil): bound the buffer as an array type
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int) , data , GL_STATIC_DRAW));// NOTE(Raghav Gohil): vertex attrib array position attribute

}

IndexBuffer::~IndexBuffer()// NOTE(Raghav Gohil): destroy the buffer
{

    GLCall(glDeleteBuffers(1 , &m_renderer_id));

}

void IndexBuffer::bind() const// NOTE(Raghav Gohil):  bind the buffer
{

    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , m_renderer_id));

}

void IndexBuffer::unbind() const// NOTE(Raghav Gohil): unbind the buffer
{

    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , 0));

}
