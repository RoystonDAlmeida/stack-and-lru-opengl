#include<windows.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<stdio.h>
#include<GL/gl.h>
#include<string.h>
#include<math.h>
#include<iostream>
#include<cstring>
#include<string>
#include <cstdlib>
//LRU GLOBAL VARIABLES
#define SCENE 10
int request[9] = {  };
int counter[3] = {  }, pages[3] = { }, fault[9] = { }, colour[9] = { 1,1,1,1,1,1,1,1,1 }, pagecolour[3] = { 1,1,1 };
float assign[9] = { -5.5,-5.5,-5.5,-5.5,-5.5,-5.5,-5.5,-5.5,-5.5 };
int dest = 0, showresult = 0;
int step = -1, startani = 0, faults = 0;
char res[] = "No. of page faults =  ";
void help();
int k = 0;
int c = 0;
void display1();
float R = 1, G = 1, B = 1;
float bgcolor[][3] = { {0,1,0},{0,1,0},{0,0,1} };
int bgpointer = 0;
float tilecolor[][3] = { {1,0,0.5},{1,0.7,0.7},{0,1,1} };
int tilepointer = 0;
int n;//no of page requests
void* fonts[] =
{
GLUT_BITMAP_9_BY_15,
GLUT_BITMAP_TIMES_ROMAN_10,
GLUT_BITMAP_TIMES_ROMAN_24,
GLUT_BITMAP_HELVETICA_12,
GLUT_BITMAP_HELVETICA_10,
GLUT_BITMAP_HELVETICA_18,
};
//STACK GLOBAL VARIABLES
using namespace std;

struct elem
{
	char c[20];

};

int MAX = 4;
int tos = -1;
int width = 200;
int height = 25;
elem a[20];
int SCREEN_WIDTH = 500; //Width of the screen
int SCREEN_HEIGHT = 500; //Height of the screen

void drawText(const char* string, float x, float y, float z)
{
	const char* c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++)
	{
		if (*c == '\n')
			glRasterPos3f(x, y - 0.05, z);
		else
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
	}
}

void output(int x, int y, const char* string, int j)
{
	int len, i;
	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
		glutBitmapCharacter(fonts[j], string[i]);
}

void front_page()
{
    glClearColor(0.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glColor3f(1.0, 0.0, 0.0);
	output(300, 400, "LRU PAGE REPLACEMENT ALGORITHM",5);
	output(275, 50, "-> PRESS ENTER to START", 5);
	glFlush();
	glCallList(SCENE);
	glPopMatrix();
	glutSwapBuffers();
}

bool init()
{
	glClearColor(0, 0, 0, 1); //Set the background to black
	glViewport(0, 0, 500, 500); //Setting the viewport i.e. where the primitive should be displayed
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-250, 250, -250, 250, -100, 100); //Set the orthogonal view for the view port
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GLenum error = glGetError(); //Check for the error
	if (error != GL_NO_ERROR) //If error is there
	{
		return false; //return error has been detected
	}

	return true; //return everything is fine continue
}
void show();

void initone()
{
	int i;
	glColor3f(0, 0, 0);
	printf("\n--------LRU-----------");
	printf("\nEnter how many numbers:");
	scanf("%d",&n);
	printf("Enter a sequence of %d numbers for page request:(Except 0)\n",n);
	for (i = 0; i < n; i++)
		scanf("%d", &request[i]);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600);
	glMatrixMode(GL_MODELVIEW);

}
void drawBitmap(char *string, int x, int y)
{
	glRasterPos2f(x, y);
	for (unsigned int i = 0; i < strlen(string); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
//STACK PUSH
void push()
{
	if (tos >= MAX)
	{
		drawBitmap((char *)"STACK IS FULL", -70, 200);
		glutSwapBuffers();
		Sleep(100);

	}
	else{
		tos++;
		printf("\nEnter the Element: ");
		cin >> a[tos].c;
		cout << endl;
		show();

	}
}
//STACK DISPLAY
void show()
{

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(0, -200, 0);

	int k = 0;

	for (int i = 0; i <= tos; i++) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_POLYGON);
		glVertex2f(-100, k);
		glVertex2f(100, k);
		glVertex2f(100, k + 50);
		glVertex2f(-100, k + 50);
		glEnd();

		glRasterPos2f(-2, (k + 10));

		for (unsigned int j = 0; j < strlen(a[i].c); j++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, a[i].c[j]);
		}
		k += 50;
	}
	glutSwapBuffers();
	glPopMatrix();
}

//STACK POP
void pop()
{
	if (tos <0)
	{
		drawBitmap((char *)"STACK IS EMPTY", -70, 200);
		glutSwapBuffers();
		Sleep(1000);
	}
	else
	{
		cout << "\nElement " << a[tos].c << " is removed from stack\n";
		tos--;
		show();
	}
}

int getLRU()
{
	if (counter[0] >= counter[1] && counter[0] >= counter[2]) return 0;
	if (counter[1] >= counter[0] && counter[1] >= counter[2]) return 1;
	//if(counter[2]>=counter[1] && counter[2]>=counter[3]) return 2;
	return 2;
}

void tile(float x, float y, char n)
{

	float size = 20;

	//glColor3f(1,1,0);
	glBegin(GL_POLYGON);
	glVertex2f(x - size, y - size);
	glVertex2f(x + size, y - size);
	glVertex2f(x + size, y + size);
	glVertex2f(x - size, y + size);
	glEnd();
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x - size, y - size);
	glVertex2f(x + size, y - size);
	glVertex2f(x + size, y + size);
	glVertex2f(x - size, y + size);
	glEnd();
	glRasterPos2f(x - size / 2, y);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, n);


}

void draw_flag()
{

	glColor3fv(bgcolor[bgpointer]);
	glBegin(GL_POLYGON);
	glVertex2f(-10, -10);
	glVertex2f(10, -10);
	glVertex2f(10, 10);
	glVertex2f(-10, 10);
	glEnd();

}

void button()
{
	glColor3f(1.0, 1.0,0.0);
	glLineWidth(6.5f);
	glBegin(GL_POLYGON);
	glVertex2f(230, 530);
	glVertex2f(230, 570);
	glVertex2f(400, 570);
	glVertex2f(400, 530);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	drawText("New simulation", 250, 550, 0);

	glColor3f(1.0, 1.0, 0.0);
	glLineWidth(6.5f);
	glBegin(GL_POLYGON);
	glVertex2f(230, 430);
	glVertex2f(230, 470);
	glVertex2f(400, 470);
	glVertex2f(400, 430);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	drawText("Help", 280, 450, 0);

	glColor3f(1.0, 1.0, 0.0);
	glLineWidth(6.5f);
	glBegin(GL_POLYGON);
	glVertex2f(230, 330);
	glVertex2f(230, 370);
	glVertex2f(400, 370);
	glVertex2f(400, 330);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	drawText("Quit", 280, 350, 0);
	glutSwapBuffers();

}

void setup_request(int n)
{
	int i;
	glColor3fv(bgcolor[bgpointer]);

	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(700, 0);
	glVertex2f(700, 100);
	glVertex2f(0, 100);
	glEnd();

	glPushMatrix();
	glTranslatef(-10, 40, 0);
	for (i = 0; i < n; i++)
	{
		glColor3fv(tilecolor[tilepointer]);
		glTranslatef(70, 0, 0);
		glPushMatrix();

		if (assign[i] > -4.5)
		{
		    glTranslatef(70 * step - 70 * i, 0, 0);
		}
		glTranslatef(0, -250 - 45 * assign[i], 0);

		if ((int)assign[i] == dest && assign[i] >= 0)
			glColor3f(1, 0.3, 0.3);
		else
			//glColor3f(colour[i],1,0);
			glColor3fv(tilecolor[tilepointer]);

		tile(10, 10, request[i] + '0');
		glPopMatrix();

		if (fault[i])
		{
			glPushMatrix();
			glTranslatef(0, -385, 0);
			draw_flag();
			glPopMatrix();
		}

	}

	glPopMatrix();

}

void setup_pages()
{
	glPushMatrix();

	tile(0, 0, pages[0] == 0 ? ' ' : pages[0] + '0');
	glTranslatef(0, -45, 0);

	tile(0, 0, pages[1] == 0 ? ' ' : pages[1] + '0');
	glTranslatef(0, -45, 0);

	tile(0, 0, pages[2] == 0 ? ' ' : pages[2] + '0');
	glPopMatrix();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glPushMatrix();
	glTranslatef(120 + 70 * step, 200, 0);
	setup_pages();
	glPopMatrix();

	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslatef(50, 400, 0);
	setup_request(n);
	glPopMatrix();
	glEnd();

	if (showresult && step == n-1)
	{
		glColor3f(0, 0, 0);
		res[21] = faults + '0';
		drawText(res, 50, 20, 0);
	}
	drawText("LRU Page Replacement Algorithm", 250, 550, 0);

	glFlush();
	glutSwapBuffers();
}

void idle()
{
	if (!startani)
		return;

	if (dest > assign[step])
		assign[step] += 0.01;

	if (dest <= assign[step])
	{
		if (fault[step])
			pages[dest] = request[step];
		startani = 0;
		dest = -10;
		showresult = 1;
	}

	display();
}

//LRU-mouse control
void mouse(int btn, int state, int x, int y)
{
	int n, i, j;
	if ((btn == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) && (x <= 500) && (x >= 300) && (y <= 90) && (y >= 30)&& k==1 ) {
		k = 3;
		display();
	}
	if ((btn == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) && (x <= 500) && (x >= 300) && (y <= 230) && (y >= 170) && k==1)
	{

		k = 2;
		display1();

	}
	if ((btn == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) && (x <= 500) && (x >= 300) && (y <= 370) && (y >= 310)&& k==1 )
	{
		exit(0);
	}
	if (startani == 1)
		return;

	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && step < 8 && k==3)
	{
		if (step < 9)
			step++;

		for (i = 0; i < 3; i++)
		{
			if (request[step] == pages[i])
			{
				fault[step] = 0;
				counter[i] = 0;

				for (j = 0; j < 3; j++)
					if (j != i) counter[j]++;
				//dest=i;
				dest = -5;
				startani = 1;
				colour[step] = 0;
				glutPostRedisplay();
				return;
			}
		}

		n = getLRU();
		counter[n] = 0;
		for (i = 0; i < 3; i++)
			if (i != n)
				counter[i]++;
		//pagecolour[n]=0;
		//assign[step]=n;
		dest = n;
		startani = 1;

		fault[step] = 1;
		faults++;
	}

	glutPostRedisplay();
	glutSwapBuffers();

}
//declaration for render
void render();

void handle_bg_colour(int action)
{
	bgpointer = action;
	glutPostRedisplay();
}

void handle_tile_colour(int action)
{
	tilepointer = action;
	glutPostRedisplay();
}

void menu(int action)
{

	if (action == 0)
		exit(0);

}
void help()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glColor3f(1.0, 0.0, 0.0);
	drawText("HELP FOR USER", 320, 550, 0);
	drawText("LRU algorithm is a Greedy algorithm where the page to be replaced is least recently used.", 50, 520, 0);
	drawText("The idea is based on locality of reference, the least recently used page is not likely,", 50, 500, 0);
	drawText("Let say the page reference string 7 0 1 2 0 3 0 4 2 3 0 3 2 .", 50, 480, 0);
	drawText("Initially we have 3 page slots empty.", 50, 460, 0);
	drawText("Initially all slots are empty, so when 7 0 1 2 are allocated to the empty slots", 50, 440, 0);
	drawText("-> 4 Page faults 0 is already their so ? > 0 Page fault.", 50, 420, 0);
	drawText("when 3 came it will take the place of 7 because it is least recently used ,", 50, 400, 0);
	drawText("?>1 Page fault  0 is already in memory so ?> 0 Page fault..", 50, 380, 0);
	drawText("4 will takes place of 1 ?> 1 Page Fault", 50, 360, 0);
	drawText("Now for the further page reference string ? > 0 Page fault because they are already available in the memory", 50, 340, 0);
	glFlush();
	glCallList(SCENE);
	glPopMatrix();
	glutSwapBuffers();
}
void addMenu()
{
	int submenu1, submenu2;

	submenu1 = glutCreateMenu(handle_bg_colour);
	glutAddMenuEntry("Red", 0);
	glutAddMenuEntry("Green", 1);
	glutAddMenuEntry("Blue", 2);

	submenu2 = glutCreateMenu(handle_tile_colour);
	glutAddMenuEntry("Light brown", 0);
	glutAddMenuEntry("Light Red", 1);
	glutAddMenuEntry("Light Blue", 2);

	glutCreateMenu(menu);
	glutAddSubMenu("Background Colour", submenu1);
	glutAddSubMenu("Tile Colour", submenu2);
	glutAddMenuEntry("Quit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
//LRU
void display1()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(R,B,G, 1.0);
	if (k == 0)
	{
		front_page();
	}
	else if (k == 1)
	{
		button();
	}
	else if (k == 2)
	{
		help();
	}
	else if (k == 3)
	{

		display();
	}
	glFlush();
}

void render() //display function
{
	glClear(GL_COLOR_BUFFER_BIT); //resetting the screen
	if (tos == -1)
	{
		char *c = (char *)"3. Enter q or Q to Exit";
		glRasterPos2i(-70, 120);
		for (unsigned int i = 0; i < strlen(c); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		}
		c = (char *)"2. Enter r or R to Pop";
		glRasterPos2i(-70,140);
		for (unsigned int i = 0; i < strlen(c); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		}
		c = (char *)"1. Enter i or I to Push";
		glRasterPos2i(-70, 160);
		for (unsigned int i = 0; i < strlen(c); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		}
		glFlush();
		glutSwapBuffers();
	}
	else{
		glFlush();
		show();
		}
}
//LRU KEYBOARD
void key(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		k = 1;
		display1();
	}
	switch (key)
	{
	case 13:k = 1;
		display1();

		break;

	case 'Q':
	case 'q':exit(0);
	}

}
void reshape(int w, int h) //function to call when the screen is reshaped
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h); //setting the viewport i.e. where the primitive should be displayed
	glOrtho(-250, 250, -250, 250, -100, 100); //set the orthogonal view for the view port
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
//STACK KEYBOARD
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'i' | 'I': push();
		break;

	case 'r' | 'R': pop();
		render();
		break;
	case 'q' | 'Q': exit(0);
	}
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    int ch;
    printf("\n------------");
	printf("\n1.STACK(PUSH AND POP)");
	printf("\n2.LRU PAGE REPLACEMENT ALGORITHM");
	printf("\n3.EXIT");
	printf("\n------------");
	printf("\nEnter your choice:");
	scanf("%d",&ch);
	switch(ch)
	{
	    //Stack
	    case 1:glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT); //Setting the window size for STACK
	           glutCreateWindow("STACK");//Setting the name of the window
	           //glutMouseFunc(mouse1);
	           if (!init()) //check for the error
	           {
		          cout << "Error" << endl;
		         return -1;
	           }
	           glutKeyboardFunc(keyboard);
	           glutDisplayFunc(render);
	           glutReshapeFunc(reshape);
	    break;
	    //LRU
	    case 2:	//glutInitWindowSize(640,480);
	           glutInitWindowSize(1100, 1100);
	           glutCreateWindow("COH");
	           //glutDisplayFunc(display);
	           glutMouseFunc(mouse);
	           glutIdleFunc(idle);
	           initone();
	           glutKeyboardFunc(key);
	           glutDisplayFunc(display1);
	    break;
	    case 3:exit(0);
	}
	addMenu();
	glutMainLoop();
	return 0;
}