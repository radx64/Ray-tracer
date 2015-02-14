#include <iostream>

#include "core/Point.hpp"
#include "core/Vector.hpp"

#include <GL/gl.h> 
#include <GL/glut.h> 

#include <vector>

void guiInterface(int argc, char** argv);
void textInterface();

void display2 (void)
{ 
        glClearColor (0.0, 1.0, 0.0, 1.0); 
        glClear (GL_COLOR_BUFFER_BIT); 
        glLoadIdentity(); 
        gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
        glFlush(); 
}

float rotation = 0.0;
std::vector<int> windowIds;


void display (void)
{ 
        glMatrixMode(GL_MODELVIEW);
        glClear (GL_COLOR_BUFFER_BIT); 
        glLoadIdentity(); 
        gluLookAt (0.0, 0.0, 0.0, 0.0, 0.0, -10.0, 0.0, 1.0, 0.0);

        glTranslatef(0.0,0.0,-10.0);
        glColor3f(0.9, 0.3, 0.2);
        glScalef(1.0,1.0,1.0);

        glRotatef(rotation+=1.0,1.0,0.0,0.0);
        // rotation about Y axis
        glRotatef(rotation+=1.0,0.0,1.0,0.0);
        // rotation about Z axis
        glRotatef(rotation+=1.0,0.0,0.0,1.0);
        glutWireSphere(2,10,10);
        glColor3f(0.3, 0.9, 0.2);
        glutWireCube(4);

        glFlush(); 
} 

void reshape(int x, int y)
{
    if (y == 0 || x == 0) return;   
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity(); 
    gluPerspective(39.0,(GLdouble)x/(GLdouble)y,0.6,21.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}

void processAnimationTimer(int value)
{
    // setups the timer to be called again
    glutTimerFunc(50, processAnimationTimer, value);
    for(int i=1; i<int(windowIds.size()+1);++i)
    {
        glutSetWindow(i);
        glutPostRedisplay();   
    }
    
}

int main(int argc, char** argv)
{
	std::cout << "Params given: " << argc << std::endl <<"To executable: "<< argv[0] << std::endl;

    if (argc > 1)
    {
        std::cout << "Starting GUI interface using OpenGL..." << std::endl;
        guiInterface(argc, argv);
    }
    else
    {
        std::cout << "Starting text interface..." << std::endl;
        textInterface();
    }
    return 0;
}




void guiInterface(int argc, char** argv)
{
        glutInit(&argc, argv); 
        glutInitDisplayMode (GLUT_SINGLE); 
        glutInitWindowSize (500,500); 
        glutInitWindowPosition (100, 100); 
        windowIds.push_back(glutCreateWindow ("Preview window"));
        glutDisplayFunc (display);
        glutReshapeFunc(reshape);
        //std::cout <<  glutCreateWindow ("Render window") << std::endl;
        //glutDisplayFunc (display2);
        //glutReshapeFunc(reshape);
        processAnimationTimer(100);
        glutMainLoop();
}

void textInterface()
{
    rt::core::Point p(1.0, 2.0, 3.0);
    std::cout << p << std::endl;
    rt::core::Vector v(1.0, 2.0, 3.0);
    std::cout << v << std::endl;
    rt::core::Vector z = v + p;
    std::cout << z << std::endl;
}
