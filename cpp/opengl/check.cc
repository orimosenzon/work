
#include <iostream> 
#include <GL/glut.h>
#include <math.h> 

GLfloat light_diffuse[] = {0.0, 0.0, 1.0, 0.1};  /* Red diffuse light. */

GLfloat light_position[] = {1.0, 0.0, 1.0, 0.0};  /* Infinite light location. */

GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };

GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };

GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */


GLfloat angle = 0.1; 

int lastX,lastY; 

void drawBox(void) {

  int i;
  //??
  glBegin(GL_QUADS);
	    glNormal3fv(&n[0][0]);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(1, 0.0, 0.0);
        glVertex3f(0.5, 0.5, 0.0);
        glVertex3f(0.0, 0.5, 0.0);
    glEnd();

  for (i = 0; i < 6; i++) {
    glBegin(GL_QUADS);
    glNormal3fv(&n[i][0]);
    glVertex3fv(&v[faces[i][0]][0]);
    glVertex3fv(&v[faces[i][1]][0]);
    glVertex3fv(&v[faces[i][2]][0]);
    glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
  }
}


void mouse(int button, int state, int x, int y) {
  angle = (GLfloat) fmod(angle + 0.1, 360.0);
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { 
    std::cout << "down: ("<< x<<',' << y <<")\n";
    lastX = x; 
    lastY = y; 
  }
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
    std::cout << "up: ("<< x<<',' << y <<")\n";

}

void motion(int x, int y) {
    std::cout << "motion: ("<< x<<',' << y <<")\n";

    glRotatef(x-lastX, 0, 0, 1);
    glRotatef(lastY-y, 1, 0, 0);
    lastX = x; 
    lastY = y; 
}

void display(void) {
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  drawBox();
  



  glutSwapBuffers();
}

void idle() 
{


  glutPostRedisplay();
}

void init(void) {
  /* Setup cube vertex data. */
  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;

  /* Enable a single OpenGL light. */
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);

  /* Setup the view of the cube. */
  glMatrixMode(GL_PROJECTION);
  gluPerspective( /* field of view in degree */ 40.0,
    /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 10.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
    0.0, 0.0, 0.0,      /* center is at (0,0,0) */
    0.0, 1.0, 0.);      /* up is in positive Y direction */

  /* Adjust cube position to be asthetic angle. */
  glTranslatef(0.0, 0.0, -1.0);
  glRotatef(60, 1.0, 0.0, 0.0);
  glRotatef(-20, 0.0, 0.0, 1.0);
}

int main(int argc, char **argv) {

  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("check");

  glutMouseFunc(mouse);
  glutMotionFunc(motion);

  glutDisplayFunc(display);

  init();
  glutIdleFunc(idle); 

  glutMainLoop();

}
