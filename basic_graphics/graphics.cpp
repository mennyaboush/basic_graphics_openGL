#include "GLUT.H"
#include <math.h>

const int WH = 100;
const int WW = 50;
double windows[WH][WW];
double angle = 0;
double SKY_LINE = -0.5;
const int NUM_STARS = 350;
double stars[2][NUM_STARS];
double plainX, plainY;
void init()
{
	glClearColor(0, 0, 1, 0); // set background color
	glOrtho(-1, 1, -1, 1, 1, -1); // set coordinate system
	int i;

	//init stars
	for (i = 0; i < NUM_STARS; i++)
	{
		// random value in [-1,1]
		stars[0][i] = -1 + 2 * (rand() % 1000) / 1000.0;
		// random value in [0,1]
		stars[1][i] = 0.2 +(rand() % 1000) / 1000.0;
	}

	//intit windows
	for(int i = 0; i<WH;i++)
		for(int j=0;j<WW;j++)
			windows[i][j] = (rand() % 100) / 100.0;

	plainX = -0.3;
	plainY = 1;
}

void DrawBackground()
{
	// top part
	glBegin(GL_POLYGON);
	glColor3d(0, 0, 51/255);
	glVertex2d(-1, 1);
	glVertex2d(1, 1);
	glColor3d(0.4, 0.2, 0);
	glVertex2d(1, SKY_LINE);
	glVertex2d(-1, SKY_LINE);
	glEnd();

	
	// bottom part
	glBegin(GL_POLYGON);
	glColor3d(0.2, 0.2, 0.5);
	glVertex2d(-1, -1);
	glVertex2d(1, -1);
	glColor3d(0, 0, 66/255);
	glVertex2d(1, SKY_LINE);
	glVertex2d(-1, SKY_LINE);
	glEnd();

	// add stars

	for (int i = 0; i < NUM_STARS; i++)
	{
		glPointSize(rand() % 2 + 1);
		if (stars[1][i] < 0.5)
			glColor3d(0.6, 0.6, 0);//light yellow
		else
			glColor3d(1, 1, 0);//yellow
		glBegin(GL_POINTS);
		glVertex2d(stars[0][i], stars[1][i]);
		glEnd();
		//reflaction
		glBegin(GL_POINTS);
		glVertex2d(stars[0][i], -stars[1][i] + SKY_LINE);
		glEnd();

	}

}

void DrawBuilding(double w, double h, double x,double r , double g , double b)
{
	double xx, yy;
	double const DELTA = 0.1;
	glColor3d(0, 0.2, rand()%100 / 100);
	glBegin(GL_POLYGON);
	glColor3d(r, g, b);
	glVertex2d(x, SKY_LINE);
	glColor3d(r, g + DELTA, b +DELTA);
	glVertex2d(x, SKY_LINE +h);
	glVertex2d(x+w, SKY_LINE +h);
	glColor3d(r+0.3, 0, b + 2*DELTA);
	glVertex2d(x + w, SKY_LINE);
	glEnd();
	glPointSize(2);
	// windows

	int i, j;
	// pick any matrix element and change it

	i = rand() % WH;	
	j = rand() % WW;
	windows[i][j] = (rand() % 100) / 100.0;

	for(xx=x+0.01,j=0;xx<x+w-0.01;xx+=0.01,j++)
		for (yy = SKY_LINE + 0.05,i=0; yy < SKY_LINE+ h - 0.05; yy += 0.03,i++)
		{
			glColor3d(windows[i][j], windows[i][j], 0);
				glBegin(GL_POINTS);
				glVertex2d(xx, yy);
				glEnd();
		}
}
void fallingStar()
{
	glPointSize(2 + rand() % 2);
	glBegin(GL_POINTS);
	glColor3d(1, 1, 1);
	glPushMatrix();
	glScaled(0.7,0.7,0.7);
	glVertex2d(plainX + 0.01, plainY + 0.01);
	glPopMatrix();
	glEnd();

}
void DrawBuilding(double w, double h, double x)
{
	DrawBuilding(w, h, x, 0, 0.3, 0.4);
	double xx, yy;
	glColor3d(0, 0.2, rand() % 100 / 100);
	glBegin(GL_POLYGON);
	glColor3d(0, 0, 0.4);
	glVertex2d(x, SKY_LINE);
	glColor3d(0.2, 0.4, 0.6);
	glVertex2d(x, SKY_LINE + h);
	glVertex2d(x + w, SKY_LINE + h);
	glColor3d(0.3, 0, rand() % 100 / 100);
	glVertex2d(x + w, SKY_LINE);
	glEnd();
	glPointSize(2);
	// windows

	int i, j;
	// pick any matrix element and change it

	i = rand() % WH;
	j = rand() % WW;
	windows[i][j] = (rand() % 100) / 100.0;

	for (xx = x + 0.01, j = 0; xx<x + w - 0.01; xx += 0.01, j++)
		for (yy = SKY_LINE + 0.05, i = 0; yy < SKY_LINE + h - 0.05; yy += 0.03, i++)
		{
			glColor3d(windows[i][j], windows[i][j], 0);
			glBegin(GL_POINTS);
			glVertex2d(xx, yy);
			glEnd();
		}
}

void DrawBuildingAndReflection(double w, double h, double x)
{
	DrawBuilding(w, h, x);
	glPushMatrix();
	glTranslated(0, SKY_LINE, 0); //3
	glScaled(1, -0.5, 1);// 2.
	glTranslated(0, -SKY_LINE, 0); // 1.
	DrawBuilding(w, h, x);
	glPopMatrix();

}

void DrawBuildingAndReflection(double w, double h, double x, double r, double g, double b)
{
	DrawBuilding(w, h, x , r , g , b);
	glPushMatrix();
	glTranslated(0, SKY_LINE, 0); //3
	glScaled(1, -0.5, 1);// 2.
	glTranslated(0, -SKY_LINE, 0); // 1.
	DrawBuilding(w, h, x , r , g , b);
	glPopMatrix();

}
void bridge()
{
	double i,y;
	//Frame for bridge
	glBegin(GL_LINE_STRIP);
	
		glScaled(1, -3, 1);
		glTranslated(0.5, 0, 0);
		glColor3d(1,1,1);
		glLineWidth(7);
		for (i = -1; i < 0; i += 0.01)
		{
			y = fabs (cos(i)*sin(i));
			glVertex2d(i , y + SKY_LINE);
		
		}
		glEnd();

		//Strings for a bridge
		glColor3d(1, 1, 1);
		double const bridgeDelta = 0.05;
		double const bridgeStringsDelta = 0.01;
		for (i = -1; i < 0; i += bridgeDelta)
		{
			glBegin(GL_POLYGON);
			y = fabs(cos(i)*sin(i));
			glVertex2d(i, y + SKY_LINE); // left top
			i += bridgeStringsDelta;
			y= fabs(cos(i)*sin(i));
			glVertex2d(i, y + SKY_LINE); // right top
			glVertex2d(i, SKY_LINE); // right down
			glVertex2d(i- bridgeStringsDelta, SKY_LINE); // left down
			glEnd();
		}
		
	//Floor to bridge
		glBegin(GL_POLYGON);
		glVertex2d(-1, SKY_LINE);
		glVertex2d(0, SKY_LINE);
		glVertex2d(0, SKY_LINE -0.01);
		glVertex2d(-1, SKY_LINE - 0.01);
		glEnd();

		glPushMatrix();
		glScaled(-0.5, 0, 0);
		glTranslated(0, -SKY_LINE, 0);

		//=========================== reflaction
		//Frame for bridge
		//glBegin(GL_LINE_STRIP);
		//glLineWidth(7);
		//for (i = -1; i < 0; i += 0.01)
		//{
		//	y = fabs(cos(i)*sin(i));
		//	glVertex2d(i, -0.5*y + SKY_LINE);

		//}
		//glEnd();

		////Strings for a bridge
		//glColor3d(1, 1, 1);
		//for (i = -1; i < 0; i += bridgeDelta)
		//{
		//	glBegin(GL_POLYGON);
		//	y = fabs(cos(i)*sin(i));
		//	glVertex2d(i, -0.5*y + SKY_LINE); // left top
		//	i += bridgeStringsDelta;
		//	y = fabs(cos(i)*sin(i));
		//	glVertex2d(i, -0.5*y + SKY_LINE); // right top
		//	glVertex2d(i, SKY_LINE); // right down
		//	glVertex2d(i - bridgeStringsDelta, SKY_LINE); // left down
		//	glEnd();
		//}
		//
}
void display()
{
	double x, y;
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer
	glLoadIdentity();

DrawBackground();

DrawBuildingAndReflection(0.4, 0.7, -0.7, 0.01, 0.01, 0.4);
DrawBuildingAndReflection(0.3, 1, 0, 0.01, 0.01, 0.4);
DrawBuildingAndReflection(0.4, 0.9, 0.5, 0.01, 0.01, 0.4);

double const DELTA = 0.1;
double temp;
	for (x = -1; x <= 1; x = x + 3/2*DELTA )
	{
		y = 7*DELTA + fabs(cos(2*x)*sin(20*x))+ SKY_LINE;
		DrawBuildingAndReflection(DELTA, y, x);
	}
	DrawBuilding(0.4, 1, 0);
	glPushMatrix();
	glTranslated(0, -0.5, 0); //3
	glScaled(1, -0.5, 1);// 2.
	glTranslated(0, 0.5, 0); // 1.
	DrawBuilding(0.4, 1, 0);
	glPopMatrix();

	// add plains 
	fallingStar();
	bridge();
	glutSwapBuffers();
}

void idle()
{
	angle+=0.001;
	plainX += 0.01;
	plainY -= 0.001;
	if (plainX > 4) 
	{
		plainX = -0.3;
		plainY = 1 - rand() % 100 / 200;
	}
	
	glutPostRedisplay(); // indirect call to display
}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Basic graphics app");

	glutDisplayFunc(display);
	glutIdleFunc(idle);

	init();

	glutMainLoop();
}