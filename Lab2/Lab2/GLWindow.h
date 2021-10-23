#pragma once
#ifndef GLWINDOW_H
#define GLWINDOW_H
#include "GLFW/glfw3.h"
#include <iostream>


namespace oknelaksoms 
{
    /**
     * Pattern Adapter - Wrapper
     */
    class GLWindow 
    {
    public:
        GLWindow(const std::string& title, uint32_t width, uint32_t height);
        GLWindow(const std::string& title, uint32_t width, uint32_t height,int xpos,int ypos);
        GLWindow(const std::string& title, uint32_t width, uint32_t height, GLFWwindow* share);

        ~GLWindow() 
        {
            //glfwDestroyWindow(_handle);
            glfwSetWindowShouldClose(this->_handle, 1);
        };
        uint32_t getWidth();
        uint32_t getHeight();
        GLFWwindow* getGLFWHandle() const;
        void setOpacity(float op);
    private:
        GLFWwindow* _handle;
        bool _full_screen = false;
        /*uint32_t*/int _width, _height;
        std::string _title;
        int _xpos;
        int _ypos;
        GLFWmonitor* _monitor;
        
    public:
        void makeMonitor()
        {
            _monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(_monitor);
            glfwWindowHint(GLFW_RED_BITS, mode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
            //window = glfwCreateWindow(mode->width, mode->height, "Lesson 02", monitor, NULL);
        }

        void ChangeFullScreen();

        /*
        KeyCallback _keyCallbackFunc = Mapper::keyCallbackMapNone;
        CursorPosCallback _cursorPosCallbackFunc = Mapper::cursorPosCallbackMapNone;
        MouseButtonCallback _mouseButtonCallbackFunc = Mapper::mouseButtonCallbackMapNone;
        MouseScrollCallback _mouseScrollCallbackFunk = Mapper::mouseScrollCallbackMapNone;
         */
    };

    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    GLWindow::GLWindow(const std::string& title, uint32_t width, uint32_t height)
    {
        _handle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
        glfwMakeContextCurrent(_handle);
        _width = width;
        _height = height;
        _title = title;
        glfwGetWindowPos(_handle, &_xpos, &_ypos);
        glfwSetFramebufferSizeCallback(_handle, framebuffer_size_callback);
    }
    GLWindow::GLWindow(const std::string& title, uint32_t width, uint32_t height,int xpos,int ypos)
    {
        _handle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
        glfwMakeContextCurrent(_handle);
        _width = width;
        _height = height;
        _title = title;
        _xpos = xpos;
        _ypos = ypos;
        glfwSetWindowPos(_handle, _xpos, _ypos);
        glfwSetFramebufferSizeCallback(_handle, framebuffer_size_callback);
    }
    GLWindow::GLWindow(const std::string& title, uint32_t width, uint32_t height, GLFWwindow* share) 
    {
        _handle = glfwCreateWindow(width, height, title.data(), nullptr, share);
        glfwMakeContextCurrent(_handle);
        _width = width;
        _height = height;
        _title = title;
        glfwGetWindowPos(_handle, &_xpos, &_ypos);
        glfwSetFramebufferSizeCallback(_handle, framebuffer_size_callback);
    }

    GLFWwindow* GLWindow::getGLFWHandle() const
    {
        return _handle;
    };

    uint32_t GLWindow::getWidth() 
    {
        return _width;
    };

    uint32_t GLWindow::getHeight() 
    {
        return _height;
    };
    void GLWindow::setOpacity(float op)
    {
        glfwSetWindowOpacity(_handle, op);
    }
    void GLWindow::ChangeFullScreen()
    {
        if (!_full_screen)
        {
            makeMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(_monitor);
            glfwSetWindowMonitor(_handle, _monitor, _xpos, _ypos, mode->width, mode->height, GLFW_DONT_CARE);
            glfwGetFramebufferSize(_handle, &_width, &_height);
            glViewport(0, 0, _width, _height);
            //if (_width > _height)
            //    glScalef((float)_height / (float)_width, 1.0f, 1.0f);
            //else if (_height > _width)
            //    glScalef(1.0f, (float)_width / (float)_height, 1.0f);
        }
        else
        {
            const GLFWvidmode* mode = glfwGetVideoMode(_monitor);
            glfwSetWindowMonitor(_handle, nullptr, _xpos, _ypos, _width, _height, GLFW_DONT_CARE);
            glfwGetFramebufferSize(_handle, &_width, &_height);
            glViewport(0, 0, _width, _height);
            //if (_width > _height)
            //    glScalef((float)_height / (float)_width, 1.0f, 1.0f);
            //else if (_height > _width)
            //    glScalef(1.0f, (float)_width / (float)_height, 1.0f);
        }
        _full_screen = !_full_screen;
        //glViewport(0, 0, _width, _height);
        //glfwMaximizeWindow(_handle);
    }
}
#endif /* GLWINDOW_H */