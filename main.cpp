/** Made by SAKIF RAHMAN
University : Kulna University Of Engineering and Technology, Khulna.
**/

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include "RGBpixmap.cpp"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include <time.h>

RGBpixmap pix[10];
void Init()
{
	glEnable(GL_TEXTURE_2D);

 /// GIve the right location for texturing ......
    pix[0].makeCheckImage();
	pix[0].setTexture(1);

	pix[1].readBMPFile("C:\\Users\\SAKIF\\Desktop\\Graphics GAME LAST\\wood.bmp");
	pix[1].setTexture(2);

	pix[2].readBMPFile("C:\\Users\\SAKIF\\Desktop\\Graphics GAME LAST\\jack.bmp");
	pix[2].setTexture(3);

	pix[3].readBMPFile("C:\\Users\\SAKIF\\Desktop\\Graphics GAME LAST\\road.bmp");
	pix[3].setTexture(4);

    pix[4].readBMPFile("C:\\Users\\SAKIF\\Desktop\\Graphics GAME LAST\\cone.bmp");
	pix[4].setTexture(5);
	pix[5].readBMPFile("C:\\Users\\SAKIF\\Desktop\\Graphics GAME LAST\\car.bmp");
	pix[5].setTexture(6);
}

int font=(int)GLUT_BITMAP_8_BY_13;
// zz is font position x_look is side position
static float zz = 0;
static float x_look = 0;

static float score = 0;
static float final_score = 0;

char s[30];
void renderBitmapString(float x, float y, void *font,char *string)
{
  char *c;
  // set position to start drawing fonts
  glRasterPos2f(x, y);
  // loop all the characters in the string
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}
void stop()
{
    int c, d;

                for (c = 1; c <= 32767; c++)
                for (d = 1; d <= 32767; d++)
                    {}
}

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 1000.0);
    //glOrtho (0.0, width, 0.0, height, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}
/// CUBE
float cube[8][3];
void func(double x, double y, double z)
{

    for(int i=0; i<8; i++)
    {
        for(int j=0; j<3; j++)
        {
            cube[i][j]=0.00;
        }
    }
    cube[1][2]=z,cube[2][0]=x,cube[2][2]=z,cube[3][0]=x,cube[4][1]=y,cube[5][1]=y,cube[5][2]=z;
    cube[6][0]=x,cube[6][1]=y,cube[6][2]=z,cube[7][0]=x,cube[7][1]=y;
}
static GLubyte cubes[6][4] ={
    {3,2,1,0},
    {5, 6, 7, 4},
    {2,6,5,1},
    {0, 1, 5, 4},
    {3, 0, 4,7},
    {7, 6, 2, 3}
};
static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat
y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3){
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;
    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;
    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;
    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;
    glNormal3f(Nx,Ny,Nz);
}

void drawcube(double x,double y, double z)
{
    //glColor3d(0,0,1);
    func(x,y,z);
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++) {
        getNormal3p(cube[cubes[i][0]][0],
        cube[cubes[i][0]][1], cube[cubes[i][0]][2],
        cube[cubes[i][1]][0], cube[cubes[i][1]][1],
        cube[cubes[i][1]][2], cube[cubes[i][2]][0],
        cube[cubes[i][2]][1], cube[cubes[i][2]][2]);
        glVertex3fv(&cube[cubes[i][0]][0]);
        glVertex3fv(&cube[cubes[i][1]][0]);
        glVertex3fv(&cube[cubes[i][2]][0]);
        glVertex3fv(&cube[cubes[i][3]][0]);
    }
    glEnd();

}
///cube

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;
    glClearColor(.2, 0.593, .85540, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
/// GLUE LOOK AT
    glLoadIdentity();
    if (zz>-748)
        zz = zz - 0.2;
    if (zz>-748)
        score = score + .1;
    final_score = score* 200 / 745;

    gluLookAt(0.0+ x_look, 1.0, 7.5 + zz,
              x_look , 0.0, -10.0 + zz,
              0.0, 1.0, 0.0);
    ///floor
    glColor3d(.322,.745,.5);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,2);
        glEnable(GL_TEXTURE_2D);
        glTranslated(-100,-3,-800);
        drawcube(200,1,1600);
         glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    ///track
    glColor3d(15.1/255,15.1/255,15.1/255);
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,2);
        glEnable(GL_TEXTURE_2D);
        glTranslated(-7.5,-2.9,-800);
        drawcube(15,1,1600);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glColor3d(229.1/255,231.1/255,233.1/255);
     glPushMatrix();
        glTranslated(-7.5,-2.88,-800);
        drawcube(.5,1,1600);
    glPopMatrix();
    glPushMatrix();
        glTranslated(7.5,-2.88,-800);
        drawcube(.5,1,1600);
    glPopMatrix();
    int i = 0;
    for(i = 0; i< 80 ; i++){
        glPushMatrix();
            glTranslated(0,-2.88,-10- i*10);
            drawcube(.5,1,3);
        glPopMatrix();
    }

    /// building
    for(i = 0; i< 26 ; i++){
        glBindTexture(GL_TEXTURE_2D,3);
        glEnable(GL_TEXTURE_2D);
        glColor3d(254.1/255,15.1/255,15.1/255);
        glPushMatrix();
            glTranslated(15,-4,-10-i*30);
            drawcube(10,10,10);
        glPopMatrix();
        glPushMatrix();
            glTranslated(-25,-4,-10-i*30);
            drawcube(10,10,10);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }

    ///CAR
    glColor3d(26.1/255,82.1/255,118.1/255);
     glPushMatrix();
       // glBindTexture(GL_TEXTURE_2D,6);
        //glEnable(GL_TEXTURE_2D);
        glTranslated(-1+x_look,-2,-2+zz);
        drawcube(2,1,4);
        //glDisable(GL_TEXTURE_2D);
     glPopMatrix();
     ///Red light
    glColor3d(255.1/255,67.1/255,53.1/255);
     glPushMatrix();
        glTranslated(-1+x_look,-1.25,-1.9+zz);
        drawcube(.4,.2,4);
     glPopMatrix();
     glPushMatrix();
        glTranslated(0.6+x_look,-1.25,-1.9+zz);
        drawcube(.4,.2,4);
     glPopMatrix();
     ///numberplate
     glColor3d(255.1/255,255.1/255,255.1/255);
     glPushMatrix();
        glTranslated(-.3+x_look,-1.6,-1.9+zz);
        drawcube(.6,.4,4);
             glPopMatrix();
     glColor3d(255.1/255,255.1/255,255.1/255);
     glPushMatrix();
        glTranslated(-1+x_look,-1.8,-1.9+zz);
        drawcube(2,.1,4);
     glPopMatrix();

    glPushMatrix();

        glColor3d(21.1/255,67.1/255,96.1/255);
        glTranslated(-1+.05+x_look,-1,-1.1+zz);
        drawcube(1.9,.7,2);
    glPopMatrix();

    ///back glass
     glPushMatrix();

        glColor3d(3.1/255,10.1/255,0.1/255);
        glTranslated(-1+.15+.05+x_look,-1+.07,-1.1+zz);
        drawcube(1.6,.6,2.1);
    glPopMatrix();

    glPushMatrix();
 glLoadIdentity();

 ///write the string
    glTranslated(-.3+x_look,1.6+5,-8+zz);
    glColor3d(255.1/255,255.1/255,53.1/255);

   renderBitmapString(30,35,(void *)font,s);
   char res[20];
    gcvt(final_score,6,res);
    renderBitmapString(30,55+40,(void *)font,"SCORE =>");
    renderBitmapString(30,55+20,(void *)font,res);
    renderBitmapString(40,55,(void *)font,"SAKIF");
 glPopMatrix();


//printf("zz === %f\n",zz);
//printf("X_look === %f\n\n\n",x_look);


    ///collusion detection
   ///Texture cube
   int slide =0 ;
   int look =0;
   slide =-600 ;
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,2);
        glEnable(GL_TEXTURE_2D);
            glTranslated(-5.4,-2.3,-5+ slide);
            drawcube(4,1,2);
        glPopMatrix();
    glPushMatrix();
            glTranslated(1.4,-2.3,-5+ slide);
            drawcube(4,1,2);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    if (zz>-6.7+slide && zz<-2.3+slide)
    {
        if(x_look>.4 || x_look < -.4)
        {
            zz = zz + 40;
            score = score - 100;
        }
    }
    slide = 100;
    look = 3;
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,2);
        glEnable(GL_TEXTURE_2D);
            glTranslated(-5.4-2 + look,-2.3,-5-slide);
            drawcube(6,1,2);
        glPopMatrix();
    glPushMatrix();
            glTranslated(1.4 + look,-2.3,-5- slide);
            drawcube(4,1,2);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    if (zz>-6.7 - slide&& zz<-2.3- slide)
    {
        if(x_look <2.6 || x_look > 3.3)
        {
            zz = zz + 40;
            score = score - 100;
        }
    }
    slide = 200;
    look = -3;
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,2);
        glEnable(GL_TEXTURE_2D);
            glTranslated(-5.4+2 + look,-2.3,-5-slide);
            drawcube(4,1,2);
        glPopMatrix();
    glPushMatrix();
            glTranslated(1.4 +2 + look,-2.3,-5- slide);
            drawcube(8,1,2);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    if (zz>-6.7 - slide&& zz<-2.3- slide)
    {
        if(x_look <-1.4 || x_look > -.6)
        {
            zz = zz + 40;
            score = score - 100;
        }
    }
    slide = 300;
    look = 3;
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,2);
        glEnable(GL_TEXTURE_2D);
            glTranslated(-5.4-2 + look,-2.3,-5-slide);
            drawcube(6,1,2);
        glPopMatrix();
    glPushMatrix();
            glTranslated(1.4 + look,-2.3,-5- slide);
            drawcube(4,1,2);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    if (zz>-6.7 - slide&& zz<-2.3- slide)
    {
        if(x_look <2.6 || x_look > 3.3)
        {
            zz = zz + 40;
            score = score - 100;
        }
    }
    slide = 400;
    look = -3;
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,2);
        glEnable(GL_TEXTURE_2D);
            glTranslated(-5.4+2 + look,-2.3,-5-slide);
            drawcube(4,1,2);
        glPopMatrix();
    glPushMatrix();
            glTranslated(1.4 +2 + look,-2.3,-5- slide);
            drawcube(8,1,2);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    if (zz>-6.7 - slide&& zz<-2.3- slide)
    {
        if(x_look <-1.4 || x_look > -.6)
        {
            zz = zz + 40;
            score = score - 100;
        }
    }
    slide = -500;
    look = 0;
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,2);
        glEnable(GL_TEXTURE_2D);
            glTranslated(-5.4,-2.3,-5+ slide);
            drawcube(4,1,2);
        glPopMatrix();
    glPushMatrix();
            glTranslated(1.4,-2.3,-5+ slide);
            drawcube(4,1,2);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    if (zz>-507 && zz<-502)
    {
        if(x_look>.4 || x_look < -.4)
        {
            zz = zz + 40;
            score = score - 100;
        }
    }
    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
/*
        case 'w':
            zz = zz - 1.1;
            break;
        case 's':
            zz = zz + 0.1;
        break;
*/
        case 'd':
            if ( x_look < 5)
                x_look = x_look + 0.1;
            else
                x_look = x_look;
            break;
        case 'a':
            if ( x_look > -5)
                x_look = x_look - 0.1;
            else
                x_look = x_look;
            break;
        break;
        case 'r':
               int c, d;

                for (c = 1; c <= 32767; c++)
                for (d = 1; d <= 32767; d++)
                    {}
            zz = 0;
            x_look = 0;
            score = 0;
            final_score = 0;
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/** For lighting */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition (100, 100);


    printf("Press ###### A #### for LEFT\n");
    printf("Press ###### D #### for RIGHT\n");
    printf("Press ###### R #### for RESTART\n");
    printf("Try to avoid the OBSTACLE\nHIGH SCORE CAN BE 100% \nTRY FOR YOUR BEST\n\n\n\n\n");

    glutCreateWindow("GLUT Shapes");

   glutReshapeFunc(resize);
    //glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    Init();

    glutMainLoop();

    return EXIT_SUCCESS;
}
