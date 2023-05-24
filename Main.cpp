#define GLEW_STATIC
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "GLEW\include\GL\glew.h"
#include "GLFW\glfw3.h"
#include "renderer.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"

struct ShaderProgramSource 
{
    
    std::string VertexSource;
    std::string FragmentSource;
    
};

static ShaderProgramSource parse_shader(const std::string &filePath)
{
    
    std::ifstream stream(filePath);
    
    enum class ShaderType
    {
        
        NONE = -1, VERTEX = 0, FRAGMENT = 1
            
    };
    
    std::string line = "";
    
    std::stringstream ss[2];// NOTE(Raghav Gohil): one for vertex and one for fragment 
    
    ShaderType type = ShaderType::NONE;// NOTE(Raghav Gohil): set the default shader type
    
    if (stream.is_open()) 
    {
        
        while (getline(stream, line))
        {
            
            if (line.find("#shader") != std::string::npos)
            {
                
                if (line.find("vertex") != std::string::npos)
                {
                    
                    // NOTE(Raghav Gohil): this is the vertex shader mode
                    type = ShaderType::VERTEX;
                    
                }
                
                else if (line.find("fragment") != std::string::npos)
                {
                    
                    // NOTE(Raghav Gohil): this is the fragment shader mode
                    type = ShaderType::FRAGMENT;
                    
                }
                
            }
            
            else
            {
                
                ss[(int)type] << line << '\n';
                
            }
            
        }
        
    }
    
    return { ss[0].str() , ss[1].str() };
    
}

static void process_input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static unsigned int compile_shader(unsigned int type , const std::string &source) 
{
    
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str(); // NOTE (Raghav Gohil): creates a sequence of characters with null-terminated character at the end. \0 (to mark the end of the string variable)
    glShaderSource(id , 1 , &src , nullptr);// NOTE(Raghav Gohil): src is a double pointer
    glCompileShader(id);
    
    // NOTE(Raghav Gohil): error handing done here
    int result;
    glGetShaderiv(id , GL_COMPILE_STATUS , &result);
    
    if (result == GL_FALSE) 
    {
        
        int length;
        glGetShaderiv(id , GL_INFO_LOG_LENGTH , &length);
        char* message = (char*)_malloca(length * sizeof(char));
        glGetShaderInfoLog(id , length , &length , message);
        
        std::cout << "Error" << " " << "Failed to compile shader" << message << std::endl;
        
        glDeleteShader(id);
        
        return 0;
        
    }
    
    return id;
    
}

static unsigned int create_shader(const std::string &vertexShader , const std::string &fragmentShader)// NOTE(Raghav Gohil): compile the shaders
{
    
    unsigned int program = glCreateProgram();
    unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragmentShader);
    
    glAttachShader(program , vs);
    glAttachShader(program, fs);
    
    glLinkProgram(program);
    glValidateProgram(program);
    
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return program;
    
}

int main()// NOTE(Raghav Gohil): the main entry point
{
    
    glfwInit();
    // NOTE(Raghav Gohil): window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // NOTE(Raghav Gohil): glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "Engine", NULL, NULL);// NOTE(Raghav Gohil): create a window
    
    glfwSetWindowShouldClose(window, false);
    
    if (window == NULL)
    {
        std::cout << "Error:" << " " << "Failed to create GLFW window" << std::endl;
        glfwTerminate();// NOTE(Raghav Gohil): terminate application
        return -1;
    }
    
    glfwMakeContextCurrent(window);// NOTE(Raghav Gohil): made a context
    
    // NOTE(Raghav Gohil): sets refresh rate = to the the monitor's refresh rate
    //glfwSwapInterval(1);
    
    // NOTE(Raghav Gohil): check if glew is ok
    
    if (glewInit() != GLEW_OK)std::cout << "Glew is not ok" << std::endl;
    
    glViewport(0, 0, 800, 600);// NOTE(Raghav Gohil): set the viewport
    
    // NOTE(Raghav Gohil): resizing screen
    void framebuffer_size_callback(GLFWwindow * window, int width, int height);// NOTE(Raghav Gohil): declare function
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    std::cout << glGetString(GL_VERSION) << std::endl;
    
    // NOTE(Raghav Gohil): vertices
    {
        float vertices[] =
        {
            // NOTE(Raghav Gohil): positions , colors removed
            -0.5f , -0.5f , 0.0f, //1.0f , 0.0f , 0.0f,// NOTE(Raghav Gohil): this is the stride
            0.5f , -0.5f , 0.0f, //0.0f , 1.0f , 0.0f,
            0.5f ,  0.5f , 0.0f, //0.0f , 0.0f , 1.0f,
            -0.5f , 0.5f , 0.0f, //1.0f , 1.0f , 1.0f,
        };
        
        unsigned int indices[] =
        {
            
            0,1,2,
            2,3,0,
            
        };
        
        // NOTE(Raghav Gohil): vertex array object stores the VBOs
        
        unsigned int VAO;// NOTE(Raghav Gohil): in this VAO the names of the arrays is stored
        glGenVertexArrays(1, &VAO);// NOTE(Raghav Gohil): generated an array
        glBindVertexArray(VAO);// NOTE(Raghav Gohil): bound the array names
        
        // NOTE(Raghav Gohil): vertex buffer
        
        VertexBuffer vb(vertices , sizeof(vertices));
        
        //unsigned int VBO;
        //glGenBuffers(1 , &VBO);// NOTE(Raghav Gohil): the vbo names are stored here
        //glBindBuffer(GL_ARRAY_BUFFER , VBO);// NOTE(Raghav Gohil): bound the buffer as an array type
        //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) , vertices , GL_STATIC_DRAW);//
        
        // NOTE(Raghav Gohil): vertex attrib array position attribute
        
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 3*sizeof(float) , (void*)0);
        
        // NOTE(Raghav Gohil): vertex attrib arrray color attribute
        
        //glEnableVertexAttribArray(1);
        //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float) , (void*)(3 * sizeof(float)));
        
        // NOTE(Raghav Gohil): index buffer object
        
        IndexBuffer ib(indices , 6);
        
        //unsigned int IBO;
        //glGenBuffers(1, &IBO);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , IBO);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices , GL_STATIC_DRAW);
        
        // NOTE(Raghav Gohil): some gpu drivers provide you with a default shader
        
        ShaderProgramSource source = parse_shader("../Basic.shader");
        
        unsigned int shader = create_shader(source.VertexSource, source.FragmentSource);
        glUseProgram(shader);
        
        while (!glfwWindowShouldClose(window))// NOTE(Raghav Gohil): render loop
        {
            
            process_input(window);
            
            // NOTE(Raghav Gohil): GL_clear_error();
            
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            
            glClear(GL_COLOR_BUFFER_BIT);
            
            // NOTE(Raghav Gohil): uniforms:
            
            /** change shader value with time..
            float timeValue = glfwGetTime();
            float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
            int vertexColorLocation = glGetUniformLocation(shader, "ourColor");
            glUseProgram(shader);
            glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f); //rgba values (the   green value is dynamically changing)
            */
            
            // NOTE(Raghav Gohil): this is drawing without index buffer:
            
            //glDrawArrays(GL_TRIANGLES , 0 , 3);
            GLCall(glDrawElements(GL_TRIANGLES, 6 , GL_UNSIGNED_INT , nullptr)); // NOTE(Raghav Gohil): VERY IMPORTANT PUT UNSIGNED CUZ YES
            
            // NOTE(Raghav Gohil): drawing with legacy opengl
            /**
            glBegin(GL_TRIANGLES);
    
            glVertex2f(-0.5f, -0.5f);
            glVertex2f(0.0f, 0.5f);
            glVertex2f(0.5f, -0.5f);
    
            glEnd();
            */
            
            glfwSwapBuffers(window);// NOTE(Raghav Gohil): swaps buffers to overcome flickering issues
            glfwPollEvents();// NOTE(Raghav Gohil): waits for events
            
        }
        
        glDeleteProgram(shader);
    }
    glfwTerminate();// NOTE(Raghav Gohil): terminate glfw
    
    return 0;// NOTE(Raghav Gohil): return code zero to exit safely
    
}

