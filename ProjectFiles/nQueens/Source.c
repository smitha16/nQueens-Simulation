#include<windows.h>
#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include<GL/GL.h>
#include<string.h>

int col;
int page = 1;
const int SIDE_LENGTH = 70;
int n, y;
int board[20], count;
int sleeptime;
int sol_only = -1;
void putrect(int, int);
void mouse(int);
void nvalue(int);
void chessboard();

void init() {

	glClearColor(0.0, 0.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 700, 0, 700);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void put_queen(int x1, int y1) {
	glColor3f(0.0, 0.0, 1.0);
	int mid = SIDE_LENGTH / 2;
	glBegin(GL_POINTS);
	glVertex2i(x1 + mid + 12, y1 + SIDE_LENGTH - 16);
	glVertex2i(x1 + mid - 12, y1 + SIDE_LENGTH - 16);
	glVertex2i(x1 + mid + 24, y1 + SIDE_LENGTH - 24);
	glVertex2i(x1 + mid - 24, y1 + SIDE_LENGTH - 24);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex2i(x1 + mid - 24, y1 + SIDE_LENGTH - 24);
	glVertex2i(x1 + mid - 16, y1 + 16);
	glVertex2i(x1 + mid + 16, y1 + 16);
	glVertex2i(x1 + mid + 24, y1 + SIDE_LENGTH - 24);
	glVertex2i(x1 + mid + 12, y1 + SIDE_LENGTH - 32);
	glVertex2i(x1 + mid + 12, y1 + SIDE_LENGTH - 16);
	glVertex2i(x1 + mid, y1 + SIDE_LENGTH - 32);
	glVertex2i(x1 + mid - 12, y1 + SIDE_LENGTH - 16);
	glVertex2i(x1 + mid - 12, y1 + SIDE_LENGTH - 32);
	glEnd();
	glFlush();
}

void drawSquare(GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3, GLint x4, GLint y4)
{
	if (n % 2 == 0) {
		if (col == 0)
		{
			glColor3f(1, 1, 1);
			col = 1;
		}
		else
		{
			glColor3f(0, 0, 0);
			col = 0;
		}
	}
	else {
		if (col == 0)
		{
			glColor3f(0, 0, 0);
			col = 1;
		}
		else
		{
			glColor3f(1, 1, 1);
			col = 0;
		}
	}
	glBegin(GL_POLYGON);
		glVertex2i(x1, y1);
		glVertex2i(x2, y2);
		glVertex2i(x3, y3);
		glVertex2i(x4, y4);
	glEnd();
}

void mark(int column, int row) {
	glColor3f(255, 0, 0);
	glRectf(column * SIDE_LENGTH, row * SIDE_LENGTH, column * SIDE_LENGTH + SIDE_LENGTH, row * SIDE_LENGTH + SIDE_LENGTH);
}

int place(int row, int column)
{
	int i;
	for (i = 0; i <= row - 1; ++i)
	{
		if (board[i] == column) {
			if (sol_only != 1) {
				Sleep(sleeptime);
				mark(column, row);
				put_queen(column * SIDE_LENGTH, row * SIDE_LENGTH);
				Sleep(sleeptime);
			}
			return 0;
		}
		else {
			if (abs(board[i] - column) == abs(i - row)) {
				if (sol_only != 1) {
					Sleep(sleeptime);
					mark(column, row);
					put_queen(column * SIDE_LENGTH, row * SIDE_LENGTH);
					Sleep(sleeptime);
				}
				return 0;
			}
		}
	}
	return 1;
}

void putrect(int column, int row) {
	if (column % 2 == 0 && row % 2 == 0)
		glColor3f(1.0, 1.0, 1.0);
	if (column % 2 != 0 && row % 2 != 0)
		glColor3f(1.0, 1.0, 1.0);
	if (column % 2 == 0 && row % 2 != 0)
		glColor3f(0.0, 0.0, 0.0);
	if (column % 2 != 0 && row % 2 == 0)
		glColor3f(0.0, 0.0, 0.0);
	glRectf(column * SIDE_LENGTH, row * SIDE_LENGTH, column * SIDE_LENGTH + SIDE_LENGTH, row * SIDE_LENGTH + SIDE_LENGTH);
}

void displayheader() {
	char string[10] = { 0 };
	_itoa_s(n, string, 10, 10);
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(0, n * (SIDE_LENGTH + 2));
	int i;
	int len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
	char string2[40] = "-Queens simulation! Total Solutions: ";
	glRasterPos2f(15, n * (SIDE_LENGTH + 2));
	len = (int)strlen(string2);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string2[i]);
	}
}

void displaycount() {
	glColor3d(0.0, 0.0, 1.0);
	glRectf(400, n * SIDE_LENGTH, 500, n * SIDE_LENGTH + 50);
	char c[10] = { 0 };
	_itoa_s(count, c, 10, 10);
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(400, n * (SIDE_LENGTH + 2));
	int len = (int)strlen(c);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
	}
}

void queen(int row, int n)
{
	int column;
	for (column = 0; column < n; column++)
	{
		if (place(row, column))
		{
			board[row] = column;
			Sleep(sleeptime);
			glColor3f(0, 1, 0);
			glRectf(column * SIDE_LENGTH, row * SIDE_LENGTH, column * SIDE_LENGTH + SIDE_LENGTH, row * SIDE_LENGTH + SIDE_LENGTH);
			put_queen(column * SIDE_LENGTH, row * SIDE_LENGTH);
			if (sol_only == 1)
				displaycount();
			Sleep(sleeptime);
			if (row == n - 1) {
				if (sol_only != 1)
					displaycount();
				count++;
				Sleep(2000);
				glFlush();
				putrect(column, row);
				return;
			}
			else {
				queen(row + 1, n);
				putrect(column, row);
			}
		}
		else {
			putrect(column, row);
		}
	}
}

void BitMapDisplay(char str[])
{
	y -= 40;
	glColor3f(1, 1, 1);
	glRasterPos2f(0, y);
	int len = (int)strlen(str);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	if (page == 1) {
		y = 600;
		char string1[30] = "N-Queens Simulation!";
		BitMapDisplay(string1);
		char string2[100] = "The N-Queens problem is a popular classic puzzle where";
		BitMapDisplay(string2);
		char string3[80] = "n number of queens are to be placed on an n x n";
		BitMapDisplay(string3);
		char string3a[80] = "chessboard such that no queen can attack any other queen.";
		BitMapDisplay(string3a);
		char string4[60] = "The queens can move diagonally or in a straight line. ";
		BitMapDisplay(string4);
		char string5[100] = "Therefore, to arrive at the solutions for this problem, no two";
		BitMapDisplay(string5);
		char string6[100] = "queens should be placed in the same row/column/diagonal.";
		BitMapDisplay(string6);
		char string7[80] = "A lot of algorithms used for real word problems are tested";
		BitMapDisplay(string7);
		char string7a[80] = "out on this puzzle.";
		BitMapDisplay(string7a);
		char string8[70] = "To view the simlulation, Right click and select the number";
		BitMapDisplay(string8);
		char string8a[70] = "of queens, ranging from 4 to 8.";
		BitMapDisplay(string8a);
		glutCreateMenu(nvalue);
		glutAddMenuEntry("4", 1);
		glutAddMenuEntry("5", 2);
		glutAddMenuEntry("6", 3);
		glutAddMenuEntry("7", 4);
		glutAddMenuEntry("8", 5);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
	}

	if (page == 2) {
		col = 1;
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0, 0.0, 1.0, 1.0);
		glColor3f(0, 0, 1);
		glRectf(0, n * SIDE_LENGTH, 1000, n * SIDE_LENGTH + 35);
		GLint x, y;
		for (x = 0; x < n * SIDE_LENGTH; x += SIDE_LENGTH)
		{
			if (n % 2 == 0) {
				if (col == 0)
					col = 1;
				else
					col = 0;
			}
			for (y = 0; y < n * SIDE_LENGTH; y += SIDE_LENGTH)
			{
				drawSquare(x, y, x, y + SIDE_LENGTH, x + SIDE_LENGTH, y + SIDE_LENGTH, x + SIDE_LENGTH, y);
			}
		}
		char string[40] = "Right click for more options ";
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(0, n * (SIDE_LENGTH + 2));
		int len = (int)strlen(string);
		for (int i = 0; i < len; i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
		}
		glutCreateMenu(mouse);
		glutAddMenuEntry("Full Simulation", 1);
		glutAddMenuEntry("Possible Solutions", 2);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
	}
	glFlush();
}

void reshape(int w, int h) { //display
	glViewport(100, 100, w, h);
}

void mouse(int choice) {
	glColor3f(0, 0, 1);
	glRectf(0, n * SIDE_LENGTH, 1000, n * SIDE_LENGTH + 50);
	count = 1;
	if (choice == 1) {
		sol_only = 0;
		sleeptime = 275;
		col = 1;
	}
	if (choice == 2) {
		sol_only = 1;
		sleeptime = 0;
		col = 1;
	}
	displayheader();
	queen(0, n);
	glutPostRedisplay();
}

void nvalue(int choice) {
	if (choice == 1) {
		n = 4;
	}
	if (choice == 2) {
		n = 5;
	}
	if (choice == 3) {
		n = 6;
	}
	if (choice == 4) {
		n = 7;
	}
	if (choice == 5) {
		n = 8;
	}
	page = 2;
	glutPostRedisplay();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("N-QUEENS");
	init();
	glutReshapeWindow(700,700);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}