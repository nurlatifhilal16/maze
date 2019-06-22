#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include "math.h"
using namespace std;

int sudut=0, x=1, y=1, z=1, transX=0, transY=0, row=0, col=7;
bool start=false, winPlayer=false;
float pos[] = {1.3,45.5,0};
float viewDir[] = {-0.1,-50.5,0};
float alpha = 5;
//float pos[3];
//GLdouble viewDir[] = {
//    pos[0] = 10;
//    pos[1] = 0.0;
//    pos[2] = 0.0;
//}
//float alpha = 5;

int matrix [15][15] = {
    {1,1,1,1,1,1,1,0,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,0,1,0,1,1,1,0,1},
    {1,0,0,0,1,0,0,0,1,0,1,0,1,0,1},
    {1,0,1,0,1,0,1,1,1,0,1,0,1,0,1},
    {1,0,1,0,1,0,1,0,0,0,1,0,0,0,1},
    {1,0,1,0,1,1,1,0,1,0,1,0,1,1,1},
    {1,0,1,0,0,0,1,0,1,0,1,0,0,0,1},
    {1,1,1,0,1,0,1,0,1,0,1,1,1,0,1},
    {1,0,0,0,1,0,0,0,1,0,1,0,0,0,1},
    {1,0,1,1,1,1,1,1,1,0,1,1,1,1,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,0,1,0,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,1,0,1,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,0,1,1,1,1,1,1,1}
};
//
//void setView(){
//    glPushMatrix();
//    gluLookAt(pos[0],pos[1],pos[2]+0.5,pos[0]+viewDir[0],pos[1]+viewDir[1],pos[2]+viewDir[2],0,0,1);
//    glPopMatrix();
//}

void material(float r, float g, float b){
     GLfloat mat_specular[] = { r, g, b, 1.0 };
     GLfloat mat_shininess[] = { 10.0 };
     GLfloat mat_diffuse[] = { r, g, b, 1.0 };

     glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
     glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
}

void lighting(float r, float g, float b){
     glPushMatrix();
     GLfloat light_position_diff[] = { 0.0, 0.0, -0.05, 0.0 };
     GLfloat diffuse_light[] = { r, g, b, 1.0 };
     GLfloat light_position_spec[] = { 0.0, 0.0, -1.0, 0.0 };
     GLfloat specular_light[] = { r, g, b, 1.0 };
     GLfloat light_position_diff1[] = { 0.0, 1.0, 0.0, 0.0 };
     GLfloat diffuse_light1[] = { r, g, b, 1.0 };
     GLfloat ambient_light[] = { 0.0, 0.9, 0.9, 1.0 };

     glLightfv(GL_LIGHT0, GL_POSITION, light_position_diff);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
     glLightfv(GL_LIGHT1, GL_POSITION, light_position_spec);
     glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light);
     glLightfv(GL_LIGHT2, GL_POSITION, light_position_diff1);
     glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse_light1);
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient_light);
     glPopMatrix();
}

void wallItem(){
     glTranslated(-32.5,37.5,0);
     glutSolidCube(5);
}

void player(){
    glPushMatrix();
    material(1,1,0);
    glTranslated(2.5+transX,37.5+transY,0);
    glutSolidCube(4);
    glPopMatrix();
}

void floor(){
    glPushMatrix();
    material(1,0,1);
    glTranslated(2.5,2.5,4);
    glScaled(2.15,2.15,0.1);
    glutSolidCube(35);
    glPopMatrix();
}

void wall(){
    int temp=0, posX=5,tempY=0,posY=5;
    for (int j=0; j<15; j++){
        for (int i=0; i<15; i++){
            if (matrix[j][i] == 1){
                glPushMatrix();
                glTranslated(temp,tempY,0);
                material(0,1,0);
                wallItem();
                temp+=posX;
                glPopMatrix();
            }
            else{
                temp+=posX;
            }
        }
        temp=0;
        tempY-=posY;
    }
}

void drawText(float x, float y, float z, void *font, char *huruf){
    char *c;
    glRasterPos3f(x,y,z);
    for (c=huruf; *c != '\0'; c++){
        glutBitmapCharacter(font, *c);
    }
}

void introGame(){
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glRectf(30.0,15.0,35.0,15.5);
    glRectf(35.0,15.5,35.5,10.0);
    glRectf(-32.0,15.0,-27.0,15.5);
    glRectf(-31.5,15.0,-32.0,10.5);
    glRectf(-10.0,1.0,13.0,1.5);

    drawText(-26,10,0,GLUT_BITMAP_TIMES_ROMAN_24,"WELCOME TO 3D MAZE GAME");
    drawText(-20,5,0,GLUT_BITMAP_HELVETICA_18,"Press SPACE  To Start Your Game");
    glFlush();
}

void win(){
    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    drawText(-20,20,0,GLUT_BITMAP_TIMES_ROMAN_24,"CONGRATULATIONS !!");
    drawText(-34,15,0,GLUT_BITMAP_HELVETICA_18,"You have successfully completed all levels of this game");
    drawText(-13,10,0,GLUT_BITMAP_HELVETICA_18,"you are a great player");
    drawText(-13,5,0,GLUT_BITMAP_HELVETICA_12,"Press 'B' Button To End Game");
    glFlush();
    glPopMatrix();
}
void display(){
//     glLoadIdentity();
//     glMatrixMode (GL_PROJECTION);
     glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
     glLoadIdentity();
     gluPerspective(45.0, 1, 1, 20 );
     gluLookAt(pos[0],pos[1],pos[2]+0.5,pos[0]+viewDir[0],pos[1]+viewDir[1],pos[2]+viewDir[2],0,0,-1);
//     glLoadIdentity();

//     gluLookAt(1.3,45.5,0, 1.2,0,0, 0,0,-1);
//     glMatrixMode(GL_MODELVIEW);



     GLfloat mat_specular[] = { 0.7, 0.7, 0.7, 1.0 };
     GLfloat mat_shininess[] = { 10.0 };
     GLfloat mat_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
     glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
     glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
     glRotated(sudut, x,y,z);

     floor();
     wall();
     player();

     glFlush();
}

void input(unsigned char key, int x, int y){
    if (key == 'x'){
        x=1;
        y=0;
        z=0;
        sudut+=10;
        display();
    }
    else if (key == 'y'){
        y=1;
        x=0;
        z=0;
        sudut+=-10;
        display();
    }
    else if (key == 'z'){
        y=0;
        x=0;
        z=1;
        sudut+=-10;
        display();
    }
    else if (key == ' '){
        if (start == false)
        {
            start=true;
            display();
        }
    }
    else if (key == 'b' || key == 'B'){
        exit(0);
    }
    else if (key == 'i' || key == 'I'){
        cout << "i" <<endl;
        alpha-=0.1;
        viewDir[1] = cos(alpha);
        viewDir[0] = sin(alpha);
        display();
    }
    else if (key == 'm' || key == 'M'){
        alpha+=0.1;
        viewDir[1] = cos(alpha);
        viewDir[0] = sin(alpha);
        display();
    }
    else if (key == 'j' || key == 'J'){
        pos[0]+=0.01*viewDir[0];
        pos[1]+=0.01*viewDir[1];
        pos[2]+=0.01*viewDir[2];
        display();
    }
    else if (key == 'l' || key == 'L'){
        pos[0]-=0.01*viewDir[0];
        pos[1]-=0.01*viewDir[1];
        pos[2]-=0.01*viewDir[2];
        display();
    }
}

void movePlayer(int key, int a, int b){
    switch (key){
        case GLUT_KEY_LEFT:
            if (matrix[row][col-1]==0){
                col-=1;
                transX-=5;
                cout << transX <<endl;
                display();
            }
        break;

        case GLUT_KEY_RIGHT:
            if (matrix[row][col+1]==0){
                col+=1;
                transX+=5;
                cout << transX <<endl;
                display();
            }
        break;

        case GLUT_KEY_UP:
            if (matrix[row-1][col]==0 && winPlayer==false){
                row-=1;
                transY+=5;
                cout << transY <<endl;
                display();
            }
        break;

        case GLUT_KEY_DOWN:
            if (matrix[row+1][col]==0 && start){
                row+=1;
                transY-=5;
                cout << transY <<endl;
                cout << row <<endl;
                cout << col <<endl;
                display();
            }
            if (row==14 && col==7){
                win();
                winPlayer=true;
                cout << "menaaannnggg" <<endl;
            }
        break;
    }
}

void reshape (int w, int h){
     glViewport (0, 0, (GLsizei) w, (GLsizei) h);
     glMatrixMode (GL_PROJECTION);
     glLoadIdentity();
     if (w <= h)
        glOrtho (-45, 50, -45*(GLfloat)h/(GLfloat)w,50*(GLfloat)h/(GLfloat)w, 100.0, -100.0);
//        glOrtho (-15, 50, -15*(GLfloat)h/(GLfloat)w,50*(GLfloat)h/(GLfloat)w, 100.0, -100.0);
     else
        glOrtho (-35*(GLfloat)w/(GLfloat)h, 40*(GLfloat)w/(GLfloat)h, -35, 40, 100.0, -100.0);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
 }

void myinit(){
     glClearColor (1.0, 1.0, 1.0, 1.0);
     lighting(1,1,1);
     glEnable(GL_LIGHTING);
     glEnable(GL_DEPTH_TEST);
     glShadeModel (GL_SMOOTH);
     glEnable(GL_LIGHT0);
     glEnable(GL_LIGHT1);
     glEnable(GL_LIGHT2);

     //3Ddependeci
    glShadeModel(GL_FLAT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char* argv[]){
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
     glutInitWindowSize(600,600);
     glutInitWindowPosition(100,100);
     glutCreateWindow("Crazy Fish");
     glutDisplayFunc(introGame);
     glutKeyboardFunc(input);
     glutSpecialFunc(movePlayer);
     glutReshapeFunc(reshape);
     myinit();
     glutMainLoop();
     return 0;
}
