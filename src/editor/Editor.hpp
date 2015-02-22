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

    static void displayRendered(void)
    {

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

    std::cout << "imageToDraw_: " << imageToDraw_.size()<< std::endl;
    std::cout << "imageToDraw_: " << imageToDraw_[0].size()<< std::endl;


        for (y = im_size_2; y > -im_size_2; y--)    
        {
            for (x = -im_size_2; x < im_size_2; x++)    
            {
            
            x_fl = (float)x/(im_size/viewport_size);        
            y_fl = (float)y/(im_size/viewport_size);

            pixel[0][0][0] = imageToDraw_[x+im_size_2][y+im_size_2];
            pixel[0][0][1] = imageToDraw_[x+im_size_2][y+im_size_2];
            pixel[0][0][2] = imageToDraw_[x+im_size_2][y+im_size_2];

            //pixel[0][0][0] = 155;
            //pixel[0][0][1] = 155;
            //pixel[0][0][2] = 155;

            //glRasterPos3f(x_fl, y_fl, 0);
            //glDrawPixels(1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

            glPushMatrix();

            glColor3f(imageToDraw_[x+im_size_2][y+im_size_2]/255.0,
                imageToDraw_[x+im_size_2][y+im_size_2]/255.0,
                imageToDraw_[x+im_size_2][y+im_size_2]/255.0);

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

    static void display(void)
    { 
            glMatrixMode(GL_MODELVIEW);
            glClear(GL_COLOR_BUFFER_BIT); 
            glLoadIdentity(); 
            gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -10.0, 0.0, 1.0, 0.0);

            glColor3f(0.9, 0.9, 0.2);

            for(auto& object : scene_.getObjects())
            {
                core::Point p = object->getPosition();

                glTranslatef(p.getX(), p.getY(), p.getZ());
                glutSolidSphere(2,25,25);  
                glTranslatef(-p.getX(), -p.getY(), -p.getZ());
            }

            glTranslatef(0.0,0.0,-10.0);
            glColor3f(0.9, 0.3, 0.2);
            glScalef(1.0,1.0,1.0);

            //glutWireSphere(2,10,10);
            glColor3f(0.3, 0.9, 0.2);
            //glutWireCube(4);
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

    void show(int argc, char** argv, const scene::Scene& scene, const Raytracer::ImgType& img)
    {
        scene_ = scene;
        imageToDraw_ = img;
        glutInit(&argc, argv); 
        glutInitDisplayMode(GLUT_SINGLE); 
        glutInitWindowSize(500,500); 
        glutInitWindowPosition(100, 100); 
        windowIds_.push_back(glutCreateWindow ("Preview window"));
        glutDisplayFunc(display);
        glutReshapeFunc(reshape);
        windowIds_.push_back(glutCreateWindow ("Render window"));
        glutDisplayFunc (displayRendered);
        glutReshapeFunc(reshape);
        glutMainLoop();
    };

private:
    static double rotation_;
    static std::vector<int> windowIds_;
    static scene::Scene scene_;
    static Raytracer::ImgType imageToDraw_;
};

}  // namespace editor
}  // namespace rt

#endif  // RT_EDITOR_OBJECT_HPP_