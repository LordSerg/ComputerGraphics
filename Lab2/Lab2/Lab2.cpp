#include "GLWindow.h"
#include "Renderer.h"
using namespace oknelaksoms;
using namespace GraphCore;
//const float PI = 3.14159265;

int main()
{
	//if (!glfwInit())return -1;
	int w = 500, h = 500;
	//if (w > h)
	//	glScalef((float)h / (float)w, 1.0f, 1.0f);
	//else if (h > w)
	//	glScalef(1.0f, (float)w / (float)h, 1.0f);
	GraphCore::GLRenderSystem* renderer1 = new GLRendererOld2_1();
	renderer1->init();
    GLWindow *window1 = new GLWindow("first",w,h,0,30);
	glfwMakeContextCurrent(window1->getGLFWHandle());
	window1->setOpacity(0.8);
    
	//GLWindow *window2 = new GLWindow("second",w,h,window1->getGLFWHandle());
	//GraphCore::GLRenderSystem* renderer2 = new GLRendererOld2_1();
	//renderer2->init();
    GLWindow *window2 = new GLWindow("second",w,h,500,30);
	glfwMakeContextCurrent(window2->getGLFWHandle());
	window2->setOpacity(0.8);
	while (!glfwWindowShouldClose(window1->getGLFWHandle())&&
		!glfwWindowShouldClose(window2->getGLFWHandle()))
	{
		if (glfwGetKey(window1->getGLFWHandle(), GLFW_KEY_F))
			window1->ChangeFullScreen();
		if (glfwGetKey(window2->getGLFWHandle(), GLFW_KEY_F))
			window2->ChangeFullScreen();

		
		glfwMakeContextCurrent(window1->getGLFWHandle());
		glfwGetFramebufferSize(window1->getGLFWHandle(), &w, &h);
		glViewport(0, 0, w, h);
		renderer1->render(window1->getGLFWHandle(),0);
		glfwSwapBuffers(window1->getGLFWHandle());

		glfwMakeContextCurrent(window2->getGLFWHandle());
		glfwGetFramebufferSize(window2->getGLFWHandle(), &w, &h);
		glViewport(0, 0, w, h);
		renderer1->render(window2->getGLFWHandle(),1);
		glfwSwapBuffers(window2->getGLFWHandle());

		glfwPollEvents();
		
	}
}