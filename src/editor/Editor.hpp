#ifndef RT_EDITOR_OBJECT_HPP_
#define RT_EDITOR_OBJECT_HPP_

#include <GL/gl.h> 
#include <GL/glut.h> 

#include <vector>
#include <cmath>

namespace rt
{
namespace editor
{
class Editor
{
public:
    Editor()
    {
        rotation = 0.0;
    };

    static void display2(void)
    { 
            glClearColor (0.0, 1.0, 0.0, 1.0); 
            glClear(GL_COLOR_BUFFER_BIT); 
            glLoadIdentity(); 
            gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
            glFlush(); 
    };

    static void display(void)
    { 
            glMatrixMode(GL_MODELVIEW);
            glClear(GL_COLOR_BUFFER_BIT); 
            glLoadIdentity(); 
            gluLookAt (0.0, 0.0, 0.0, (5.0 - fmod(rotation/50.0, 10.0)), 0.0, -10.0, 0.0, 1.0, 0.0);

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
    };

    static void reshape(int x, int y)
    {
        if (y == 0 || x == 0) return;   
        glMatrixMode(GL_PROJECTION);  
        glLoadIdentity(); 
        gluPerspective(39.0,(GLdouble)x/(GLdouble)y,0.6,21.0);
        glMatrixMode(GL_MODELVIEW);
        glViewport(0,0,x,y);  //Use the whole window for rendering
    };

    static void processAnimationTimer(int value)
    {
        // setups the timer to be called again
        glutTimerFunc(50, Editor::processAnimationTimer, value);
        for(int i=1; i<int(windowIds.size()+1);++i)
        {
            glutSetWindow(i);
            glutPostRedisplay();   
        }
        
    };

    void show(int argc, char** argv)
    {
        glutInit(&argc, argv); 
        glutInitDisplayMode(GLUT_SINGLE); 
        glutInitWindowSize(500,500); 
        glutInitWindowPosition(100, 100); 
        windowIds.push_back(glutCreateWindow ("Preview window"));
        glutDisplayFunc(display);
        glutReshapeFunc(reshape);
        //std::cout <<  glutCreateWindow ("Render window") << std::endl;
        //glutDisplayFunc (display2);
        //glutReshapeFunc(reshape);
        processAnimationTimer(100);
        glutMainLoop();
    };

private:
    static double rotation;
    static std::vector<int> windowIds;
};

}  // namespace editor
}  // namespace rt

#endif  // RT_EDITOR_OBJECT_HPP_