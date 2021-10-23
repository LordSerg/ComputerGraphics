#pragma once
//#ifndef GLRENDERSYSTEM_H
//#define GLRENDERSYSTEM_H
#include "GLFW/glfw3.h"
#include <iostream>
namespace oknelaksoms 
{
    namespace GraphCore 
    {
        float colorRGB,PI=3.14156535;
        struct point
        {
            float x, y, dir;
            point()
            {
                x = ((rand()%200)-100)*0.0001;
                y = ((rand()%200)-100)*0.0001;
                dir = (rand() % 3600) * PI / 1800;
            }
            point(float _x, float _y, float _dir)
            {
                x = _x;
                y = _y;
                dir = _dir;
            }
            void change()
            {
                if (x >= 1||x <= -1)dir = PI-dir;
                if (y >= 1 || y <= -1)dir = -dir;

                //if (abs(x) > 1)	dir += PI;
                //if (abs(y) > 1)	dir += PI;
                if (dir < -PI)dir += 2 * PI;
                if (dir > PI)dir -= 2 * PI;
                x += 0.001 * cos(dir);
                y += 0.001 * sin(dir);
                dir += (float)(rand() % 200-100)*0.0001;
            }
        };


        class GLRenderSystem 
        {
        public:

            virtual void init() {}

            virtual void render(GLFWwindow* window,int mode) {}

            virtual void renderTriangleArray(GLfloat vertices[], GLfloat colors[]) {}

            virtual void renderVBO() {}
        };

        class GLRender : public GLRenderSystem
        {

            void init()
            {

            }

            void render(GLFWwindow* window) {

            }

            void renderTriangleArray(GLfloat vertices[], GLfloat colors[]) {
            }
        };

        class GLRendererOld2_1 : public GLRenderSystem 
        {
            point* p1;
            int n;
            void init() 
            {
                if (!glfwInit()) 
                {
                    fprintf(stderr, "Ошибка при инициализации GLFW\n");
                    return;
                }
                glfwWindowHint(GLFW_SAMPLES, 4); // 4x Сглаживание
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2); // Мы хотим использовать OpenGL 3.3
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

                //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
                //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Мы не хотим старый OpenGL
                n = 5000;
                p1 = new point[n];
                for (int i = 0; i < n; i++)
                {
                    p1[i] = point(0.01*cos(((float)i/(float)n)*2*PI), 0.01*sin(((float)i / (float)n) * 2 * PI), ((float)i/(float)n )*2*PI);
                }
            }

            void render(GLFWwindow* window, int mode)
            {
                glClear(GL_COLOR_BUFFER_BIT);
                glColor3d(1, 1, 1);
                if (mode == 0)
                {
                    glBegin(GL_POINTS);
                    for (int i = 0; i < n; i++)
                        glVertex2f(p1[i].x, p1[i].y);
                    glEnd();
                }
                else if (mode == 1)
                {
                    glBegin(GL_LINES);
                    for (int i = 0; i < n; i++)
                    {
                        glVertex2f(p1[i].x, p1[i].y);
                        glVertex2f(p1[i].x + 0.05 * cos(p1[i].dir), p1[i].y + 0.05 * sin(p1[i].dir));
                    }
                    glEnd();
                }
                for (int i = 0; i < n; i++)
                {
                    p1[i].change();
                }
                /*glClearColor(sin(colorRGB * PI / 180), abs(cos(colorRGB * PI / 180)), abs(sin(colorRGB * PI / 180) + cos(colorRGB * PI / 180)), 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                {
                    colorRGB <= 180 ? colorRGB += 0.1 : colorRGB = 0;
                }


                glLoadIdentity();


                glRotatef((float)glfwGetTime() * 50.f, 0.f, 1.f, 1.f);
                glBegin(GL_TRIANGLES);
                glColor3f(1.f, 0.f, 0.f);
                glVertex3f(-0.6f, -0.4f, 0.f);
                glColor3f(0.f, 1.f, 0.f);
                glVertex3f(0.6f, -0.4f, 0.f);
                glColor3f(0.f, 0.f, 1.f);
                glVertex3f(0.f, 0.6f, 0.f);
                glEnd();
                */
            }

            void renderTriangleArray(GLfloat vertices[], GLfloat colors[], int n) 
            {
                glClearColor(sin(colorRGB * PI / 180), abs(cos(colorRGB * PI / 180)), abs(sin(colorRGB * PI / 180) + cos(colorRGB * PI / 180)), 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                {
                    colorRGB <= 180 ? colorRGB += 0.1 : colorRGB = 0;
                }

                glLoadIdentity();
                glRotatef((float)glfwGetTime() * 50.f, 0.f, 1.f, 1.f);
                glBegin(GL_TRIANGLES);
                if (n % 3 == 0) 
                {
                    for (int i = 0; i <= n; i += 3) {
                        glColor3f(colors[i], colors[i + 1], colors[i + 2]);
                        glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
                    }
                }
                else 
                {
                    fprintf(stderr, "Triangle error");
                    return;

                }
                glEnd();
            }

            void renderQuadArray(GLfloat vertices[], GLfloat colors[]) 
            {

                glClear(GL_COLOR_BUFFER_BIT);


                glEnableClientState(GL_VERTEX_ARRAY);
                glEnableClientState(GL_COLOR_ARRAY);

                glVertexPointer(3, GL_FLOAT, 0, vertices);
                glColorPointer(3, GL_FLOAT, 0, colors);

                glDrawArrays(GL_QUADS, 0, 8);


                glDisableClientState(GL_COLOR_ARRAY);
                glDisableClientState(GL_VERTEX_ARRAY);
            }
            void renderPOints()
            {
                glClear(GL_COLOR_BUFFER_BIT);
                glColor3d(1, 1, 1);
                glBegin(GL_POINTS);
                for (int i = 0; i < n; i++)glVertex2f(p1[i].x, p1[i].y);
                glEnd();
                for (int i = 0; i < n; i++)
                {
                    p1[i].change();
                }
            }
        };
    }
}
