#ifndef RT_EDITOR_OBJECT_HPP_
#define RT_EDITOR_OBJECT_HPP_

#include <iostream>

#include <vector>
#include <cmath>

#include <GL/gl.h> 
#include <GL/glut.h> 

#include "scene/Scene.hpp"
#include "Raytracer.hpp"

namespace rt
{
namespace editor
{
class Editor
{
public:
Editor()
{ };

static void display(void)
{
    std::cout << " Display called!" << std::endl; 
int  x, y;           // pozycja rysowanego piksela "całkowitoliczbowa"
float x_fl, y_fl;    // pozycja rysowanego piksela "zmiennoprzecinkowa"
GLubyte pixel[1][1][3]; // składowe koloru rysowanego piksela
int im_size = IMG_SIDE;
double viewport_size = 3.0;
int im_size_2;       // połowa rozmiaru obrazu w pikselach
im_size_2 = im_size/2;    // obliczenie połowy rozmiaru obrazu w pikselach
    
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(-viewport_size/2, viewport_size/2, -viewport_size/2, viewport_size/2, -viewport_size/2, viewport_size/2);
glMatrixMode(GL_MODELVIEW);


glClear(GL_COLOR_BUFFER_BIT);
glFlush();

    for (y = im_size_2; y > -im_size_2; y--)    
    {
        for (x = -im_size_2; x < im_size_2; x++)    
        {
        
        x_fl = (float)x/(im_size/viewport_size);        
        y_fl = (float)y/(im_size/viewport_size);

        pixel[0][0][0] = imageToDraw_[x+im_size_2][y+im_size_2];
        pixel[0][0][1] = imageToDraw_[x+im_size_2][y+im_size_2];
        pixel[0][0][2] = imageToDraw_[x+im_size_2][y+im_size_2];

        glPushMatrix();

        glColor3f(
            1.0-imageToDraw_[x+im_size_2][y+im_size_2]/255.0,
            1.0-imageToDraw_[x+im_size_2][y+im_size_2]/255.0,
            1.0-imageToDraw_[x+im_size_2][y+im_size_2]/255.0);

        glTranslatef(x_fl,y_fl,0.0f);   
        glBegin(GL_QUADS);                      // Draw A Quad
            glVertex3f(0.0f, 0.0f, 0.0f);              // Top Left
            glVertex3f(1.0f, 0.0f, 0.0f);              // Top Right
            glVertex3f(1.0f, 1.0f, 0.0f);              // Bottom Right
            glVertex3f(0.0f, 1.0f, 0.0f);              // Bottom Left
        glEnd();                            // Done Drawing The Quad

        glPopMatrix();
        }
    }
    glFlush();
}

static void reshape(int x, int y)
{
    if (y == 0 || x == 0) return;   
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity(); 
    gluPerspective(39.0,(GLdouble)x/(GLdouble)y,0.6,21.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);
};

void show(int argc, char** argv, const scene::Scene& scene, const Raytracer::ImgType& img)
{
    scene_ = scene;
    imageToDraw_ = img;
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE); 
    glutInitWindowSize(500,500); 
    glutInitWindowPosition(100, 100);
    windowIds_.push_back(glutCreateWindow ("Render window"));
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
};

private:
static std::vector<int> windowIds_;
static scene::Scene scene_;
static Raytracer::ImgType imageToDraw_;
};

}  // namespace editor
}  // namespace rt

#endif  // RT_EDITOR_OBJECT_HPP_