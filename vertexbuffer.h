/* date = October 30th 2021 8:01 pm */

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

class VertexBuffer
{
    
    private:
    unsigned int m_renderer_id;
    
    public:
    VertexBuffer(const void* data , unsigned int size);
    ~VertexBuffer();
    void bind() const;
    void unbind() const;
    
};

#endif //VERTEXBUFFER_H
