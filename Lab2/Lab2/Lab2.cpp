#include "Renderer.h"
#include "GLWindow.h"
using namespace oknelaksoms;
using namespace GraphCore;
//const float PI = 3.14159265;

int main()
{
	//if (!glfwInit())return -1;
	int w = 500, h = 500;
	std::cout << "Завдання 2\nАвтор: Москаленко Сергій\n";
	//if (w > h)
	//	glScalef((float)h / (float)w, 1.0f, 1.0f);
	//else if (h > w)
	//	glScalef(1.0f, (float)w / (float)h, 1.0f);
	bool is33 = true;
	GraphCore::GLRenderSystem* renderer1,*renderer2;
	if (is33)
	{
		renderer1 = new GLRender();
		renderer2 = new GLRender();
	}
	else
	{
		renderer1 = new GLRendererOld2_1();
		renderer2 = new GLRendererOld2_1();
	}
	renderer1->init();
	glewExperimental = true; // Флаг необходим в Core-режиме OpenGL
    GLWindow *window1 = new GLWindow("first",w,h,0,30);
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Невозможно инициализировать GLEW\n");
		return -1;
	}
	glfwMakeContextCurrent(window1->getGLFWHandle());
	window1->setOpacity(0.8);
    
	GLWindow *window2 = new GLWindow("second",w,h,w,30);
	glfwMakeContextCurrent(window2->getGLFWHandle());
	window2->setOpacity(0.8);

	GLWindow* window3 = new GLWindow("third", w, h,0, h+30);
	glfwMakeContextCurrent(window3->getGLFWHandle());
	window3->setOpacity(0.8);
	
	renderer2->init();
    //GLWindow *window2 = new GLWindow("second",w,h,500,30);
	while (!glfwWindowShouldClose(window1->getGLFWHandle())||!glfwWindowShouldClose(window2->getGLFWHandle()))
	{
		//if (glfwGetKey(window1->getGLFWHandle(), GLFW_KEY_F))
		//	window1->ChangeFullScreen();
		//if (glfwGetKey(window2->getGLFWHandle(), GLFW_KEY_F))
		//	window2->ChangeFullScreen();

		
		glfwMakeContextCurrent(window1->getGLFWHandle());
		glfwGetFramebufferSize(window1->getGLFWHandle(), &w, &h);
		glViewport(0, 0, w, h);
		renderer1->render(window1->getGLFWHandle(),0);
		glfwSwapBuffers(window1->getGLFWHandle());

		glfwMakeContextCurrent(window2->getGLFWHandle());
		glfwGetFramebufferSize(window2->getGLFWHandle(), &w, &h);
		glViewport(0, 0, w, h);
		renderer2->render(window2->getGLFWHandle(),1);
		glfwSwapBuffers(window2->getGLFWHandle());

		glfwMakeContextCurrent(window3->getGLFWHandle());
		glfwGetFramebufferSize(window3->getGLFWHandle(), &w, &h);
		glViewport(0, 0, w, h);
		renderer2->renderTriangleArray(window3->getGLFWHandle());
		glfwSwapBuffers(window3->getGLFWHandle());

		glfwPollEvents();
		
	}
}