/* date = October 30th 2021 8:01 pm */

#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

class IndexBuffer
{
    
    private:
    unsigned int m_renderer_id;
    unsigned int m_count;
    
    public:
    IndexBuffer(const unsigned int* data , unsigned int count);
    ~IndexBuffer();
    void bind() const;
    void unbind() const;
    inline unsigned int GetCount() const {return m_count;}
};

#endif //VERTEXBUFFER_H