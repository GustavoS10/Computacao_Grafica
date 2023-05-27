///  colisao de quadrados
//////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <string>
#include <time.h>
#include <ctime>
#include <chrono>
#include <thread>
#include <iostream>

#define janela_altura 400
#define janela_largura 600


int vida  = 5;
int point = 0;
int o2    = 100;
int count = 0;

bool isTrue  = false;
bool isFalse = true;

// movimentos
float trans = 0;
float up = 0;
// variaveis que armazenam a translacao no quadro
float tx   = 0.0;
float tx1  = 0.0;
float tx2  = 0.0;
float tx21 = 0.0;
float tx3  = 0.0;
float tx4  = 0.0;
float tx5  = 0.0;
// incremento em variaveis.
float xStep   = 20;
float xStep1  = 20;
float xStep2  = 20;
float xStep21 = 20;
float xStep3  = 20;
float xStep4  = 20;
float xStep5  = 20;

//colisao Peixe 1
float peixe_x1 = 305;
float peixe_x2 = 355;
float peixe_y1 = 0;
float peixe_y2 = -20;

//colisao Peixe 1.2
float peixe1_x1 = 305;
float peixe1_x2 = 355;
float peixe1_y1 = -35;
float peixe1_y2 = -55;

//colisao Peixe 2
float peixe_x11 = 505;
float peixe_x22 = 555;
float peixe_y11 = -80;
float peixe_y22 = -100;

//colisao Peixe 2.5
float peixe2_x11 = 405;
float peixe2_x22 = 455;
float peixe2_y11 = -120;
float peixe2_y22 = -140;

//colisao Peixe 3
float peixe_x111 = 355;
float peixe_x222 = 405;
float peixe_y111 = -170;
float peixe_y222 = -190;

//mergulhador
//cabeça
float merg_x = -50;
float merg_y = -5;
//corpo
float merg_x1 = -50;
float merg_y1 = -5;
float merg_x2 = -50;
float merg_y2 = -8;

//braços
float merg_x3 = -50;
float merg_y3 = -5.5;
float merg_x33 = -51;
float merg_y33 = -6;
float merg_x333 = -50;
float merg_y333 = -5.5;
float merg_x3333 = -49;
float merg_y3333 = -6;

//pernas
float merg_x4 = -50;
float merg_y4 = -8;
float merg_x44 = -51;
float merg_y44 = -8.5;
float merg_x444 = -50;
float merg_y444 = -8;
float merg_x4444 = -49;
float merg_y4444 = -8.5;
// Desenha as pernas

float merg1 = 0;

float mergx1 = -343;//largura
float mergy1 = -30;//altura
float mergx2 = -360; //largura
float mergy2 = -60; //altura

//mergulhador 2
float merg2_x = -50;
float merg2_y = -5;
//corpo
float merg2_x1 = -50;
float merg2_y1 = -5;
float merg2_x2 = -50;
float merg2_y2 = -8;

//braços
float merg2_x3 = -50;
float merg2_y3 = -5.5;
float merg2_x33 = -51;
float merg2_y33 = -6;
float merg2_x333 = -50;
float merg2_y333 = -5.5;
float merg2_x3333 = -49;
float merg2_y3333 = -6;

//pernas
float merg2_x4 = -50;
float merg2_y4 = -8;
float merg2_x44 = -51;
float merg2_y44 = -8.5;
float merg2_x444 = -50;
float merg2_y444 = -8;
float merg2_x4444 = -49;
float merg2_y4444 = -8.5;
// Desenha as pernas

float merg21 = 0;

float merg2x1 = -343;//largura
float merg2y1 = -117;//altura
float merg2x2 = -360; //largura
float merg2y2 = -142; //altura

float submarino_x = -5;
float submarino_x2 = 50;
float submarino_y1 = -10;
float submarino_y2 = 17;

//END VARIAVEIS GLOBAIS

void display(void);
void tela(GLsizei, GLsizei);
void keyboard(unsigned char, int, int);
void anima(int);
void anima1(int);
void anima2(int);
void anima21(int);
void anima3(int);
void anima4(int);
void anima5(int);
void pontuacao();
void O2();

//funções de atraso de tempo
void incrementNumber(int);
void verificaO2(int);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);	// suporte a janelas

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// PADRAO DE CORES

	glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela
	glutInitWindowPosition(100, 100); // posicao que surge a janela
	glutCreateWindow("Seaquest da Deepweb"); // cria janela
	//glutFullScreen();
	glutKeyboardFunc(&keyboard);  // chama teclado
	glutReshapeFunc(tela);  // configura a tela
	glutDisplayFunc(display);
	glutTimerFunc(150, anima, 1);
	glutTimerFunc(150, anima1, 1);
	glutTimerFunc(150, anima2, 1);
	glutTimerFunc(150, anima21, 1);
	glutTimerFunc(150, anima3, 1);
	glutTimerFunc(150, anima4, 1);
	glutTimerFunc(150, anima5, 1);

	// Agendamento da função de callback para a decrementação com atraso
	int initialDelay = 0; // Delay inicial de 0 milissegundos
	glutTimerFunc(initialDelay, incrementNumber, 0);

	// Agendamento da função de callback para a decrementação com atraso
	glutTimerFunc(initialDelay, verificaO2, 0);


	glutMainLoop(); // redesenhar

	return(0);
}

void anima(int valor)
{
	if (tx > 60) xStep = -xStep;
	tx -= xStep;
	glutPostRedisplay();
	glutTimerFunc(150, anima, 1);
}
void anima1(int valor)
{
	if (tx1 > 60) xStep1 = -xStep1;
	tx1 -= xStep1;
	glutPostRedisplay();
	glutTimerFunc(150, anima1, 1);
}
void anima2(int valor)
{
	if (tx2 > 60) xStep2 = -xStep2;
	tx2 -= xStep2;
	glutPostRedisplay();
	glutTimerFunc(150, anima2, 1);
}
void anima21(int valor)
{
	if (tx21 > 60) xStep21 = -xStep21;
	tx21 -= xStep21;
	glutPostRedisplay();
	glutTimerFunc(150, anima21, 1);
}
void anima3(int valor)
{
	if (tx3 > 60) xStep3 = -xStep3;
	tx3 -= xStep3;
	glutPostRedisplay();
	glutTimerFunc(150, anima3, 1);
}
void anima4(int valor)
{
	if (tx4 > 60) xStep4 = +xStep4;
	tx4 += xStep4;
	glutPostRedisplay();
	glutTimerFunc(150, anima4, 1);
}
void anima5(int valor)
{
	if (tx5 > 60) xStep5 = +xStep5;
	tx5 += xStep5;
	glutPostRedisplay();
	glutTimerFunc(150, anima5, 1);
}


void keyboard(unsigned char tecla, int x, int y) {
	if (tecla == 'a' || tecla == '1')
	{
		trans -= 6;
	}
	if (tecla == 'd' || tecla == '3')
	{
		trans += 6;
	}
	if (tecla == 'w' || tecla == '5')
	{
		(up > 10) ? up : up += 6;
	}
	if (tecla == 's' || tecla == '2')
	{
		(up <= -190) ? up : up -= 6;
	}
	glutPostRedisplay();
}

//SIMBOLOS  """"""""  |||||||||||   \n\n\n\n
// quadrado de teste de hitbox
void quad() {
	glBegin(GL_QUADS);

	glColor3f(0.0, 1.0, 0.0);  // cor
	glVertex2f(merg2x1, merg2y2);
	glVertex2f(merg2x2, merg2y2);
	glVertex2f(merg2x2, merg2y1);
	glVertex2f(merg2x1, merg2y1);
	glEnd();
}

void sub() {


	glBegin(GL_QUADS);

	glColor3f(1.0, 0.0, 0.0);  // cor
	glVertex2f(submarino_x + 5, submarino_y2 - 4);
	glVertex2f(submarino_x2, submarino_y2 - 4);
	glVertex2f(submarino_x2, submarino_y1);
	glVertex2f(submarino_x + 5, submarino_y1);

	glEnd();
	//binoclo ou sla como e o nome daquilo

	glBegin(GL_QUADS);

	glColor3f(1.0, 0.0, 0.0);  // cor
	glVertex2f(submarino_x2 - 30, submarino_y2);
	glVertex2f(submarino_x2 - 25, submarino_y2);
	glVertex2f(submarino_x2 - 25, submarino_y1);
	glVertex2f(submarino_x2 - 30, submarino_y1);

	glEnd();
	//bico

	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);  // cor
	glVertex2f(submarino_x + 5, submarino_y2 - 4);
	glVertex2f(submarino_x + 5, submarino_y1);
	glVertex2f(submarino_x, submarino_y2 - 13);
	glEnd();
}

void agua() {
	glBegin(GL_QUADS);

	glColor3f(0.0, 1.0, 1.0);  // cor
	glVertex2f(-300, 15);
	glVertex2f(300, 15);
	glVertex2f(300, -300);
	glVertex2f(-300, -300);
	glEnd();
}
void sol() {
	glBegin(GL_QUADS);

	glColor3f(1.0, 1.0, 0.0);  // cor
	glVertex2f(-300, 200);
	glVertex2f(-250, 200);
	glVertex2f(-250, 150);
	glVertex2f(-300, 150);
	glEnd();
}

void heart() {
	glPushMatrix();
	glScalef(7, 7, 7);
	glColor3f(1, 0, 0); // Define a cor vermelha
	glBegin(GL_QUADS);// Triângulo superior
	glVertex2f(0, 26.5);
	glVertex2f(1, 27);
	glVertex2f(2, 26);
	glVertex2f(0, 24);
	//METADE DO CORAÇÃOP
	glVertex2f(0, 24);
	glVertex2f(-2, 26);
	glVertex2f(-1, 27);
	glVertex2f(0, 26.5);

	glEnd();
	glPopMatrix();
}

void peixe() {
	////	glScalef(7, 7, 7);

		// Corpo do peixe
	glColor3f(1.0, 0.0, 0.0); // Vermelho
	glBegin(GL_TRIANGLES);
	glVertex2f(peixe_x2, peixe_y1);
	glVertex2f(peixe_x1, peixe_y1 - 10);
	glVertex2f(peixe_x2, peixe_y2);
	glEnd();

	/*	*/
}
void peixe1() {
	////	glScalef(7, 7, 7);

		// Corpo do peixe
	glColor3f(1.0, 0.0, 0.0); // Vermelho
	glBegin(GL_TRIANGLES);
	glVertex2f(peixe1_x2, peixe1_y1);
	glVertex2f(peixe1_x1, peixe1_y1 - 10);
	glVertex2f(peixe1_x2, peixe1_y2);
	glEnd();

	/*	*/
}
void peixe2() {
	// Corpo do peixe
	glColor3f(1.0, 0.0, 0.0); // Vermelho
	glBegin(GL_TRIANGLES);
	glVertex2f(peixe_x22, peixe_y11);
	glVertex2f(peixe_x11, peixe_y11 - 10);
	glVertex2f(peixe_x22, peixe_y22);
	glEnd();

	/*	*/
}
void peixe21() {
	// Corpo do peixe
	glColor3f(1.0, 0.0, 0.0); // Vermelho
	glBegin(GL_TRIANGLES);
	glVertex2f(peixe2_x22, peixe2_y11);
	glVertex2f(peixe2_x11, peixe2_y11 - 10);
	glVertex2f(peixe2_x22, peixe2_y22);
	glEnd();

	/*	*/
}
void peixe3() {
	// Corpo do peixe
	glColor3f(1.0, 0.0, 0.0); // Vermelho
	glBegin(GL_TRIANGLES);
	glVertex2f(peixe_x222, peixe_y111);
	glVertex2f(peixe_x111, peixe_y111 - 10);
	glVertex2f(peixe_x222, peixe_y222);
	glEnd();

	/*	*/
}

void peixes() {
	if (tx + peixe_x2 < -300) {
		tx = 0;
	}
	//peixe_x1 = tx;  // Atualiza a coordenada x do peixe
	glPushMatrix();
	glTranslatef(tx, 0, 0);
	peixe();
	glPopMatrix();
}
void peixes1() {
	if (tx1 + peixe1_x2 < -300) {
		tx1 = 0;
	}
	//peixe_x1 = tx;  // Atualiza a coordenada x do peixe
	glPushMatrix();
	glTranslatef(tx1, 0, 0);
	peixe1();
	glPopMatrix();
}
void peixes2() {
	if (tx2 + peixe_x22 < -300) {
		tx2 = 0;
	}
	//peixe_x1 = tx;  // Atualiza a coordenada x do peixe
	glPushMatrix();
	glTranslatef(tx2, 0, 0);
	peixe2();
	glPopMatrix();
}
void peixes21() {
	if (tx21 + peixe2_x22 < -300) {
		tx21 = 0;
	}
	//peixe_x1 = tx;  // Atualiza a coordenada x do peixe
	glPushMatrix();
	glTranslatef(tx21, 0, 0);
	peixe21();
	glPopMatrix();
}
void peixes3() {
	if (tx3 + peixe_x222 < -300) {
		tx3 = 0;
	}
	//peixe_x1 = tx;  // Atualiza a coordenada x do peixe
	glPushMatrix();
	glTranslatef(tx3, 0, 0);
	peixe3();
	glPopMatrix();
}


void mergulhador() {
	glColor3f(1.0, 0.0, 0.5);

	glPushMatrix();
	glScalef(7, 7, 7);
	glPointSize(5);
	// Desenha a cabeça
	glBegin(GL_POINTS);
	glVertex2f(merg_x, merg_y);
	glEnd();

	// Desenha o corpo
	glBegin(GL_LINES);
	glVertex2f(merg_x1, merg_y1);
	glVertex2f(merg_x2, merg_y2);
	glEnd();

	// Desenha os braços
	glBegin(GL_LINES);
	glVertex2f(merg_x3, merg_y3);
	glVertex2f(merg_x33, merg_y33);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(merg_x333, merg_y33);
	glVertex2f(merg_x3333, merg_y3333);
	glEnd();

	// Desenha as pernas
	glBegin(GL_LINES);
	glVertex2f(merg_x4, merg_y4);
	glVertex2f(merg_x44, merg_y44);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(merg_x444, merg_y444);
	glVertex2f(merg_x4444, merg_y4444);
	glEnd();
	glPopMatrix();

}
void mergulhador2() {
	glColor3f(0.0, 0.0, 0.0);

	glPushMatrix();
	glScalef(7, 7, 7);
	glPointSize(5);
	// Desenha a cabeça
	glBegin(GL_POINTS);
	glVertex2f(merg2_x, merg2_y - 12);
	glEnd();

	// Desenha o corpo
	glBegin(GL_LINES);
	glVertex2f(merg2_x1, merg2_y1 - 12);
	glVertex2f(merg2_x2, merg2_y2 - 12);
	glEnd();

	// Desenha os braços
	glBegin(GL_LINES);
	glVertex2f(merg2_x3, merg2_y3 - 12);
	glVertex2f(merg2_x33, merg2_y33 - 12);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(merg2_x333, merg2_y33 - 12);
	glVertex2f(merg2_x3333, merg2_y3333 - 12);
	glEnd();

	// Desenha as pernas
	glBegin(GL_LINES);
	glVertex2f(merg2_x4, merg2_y4 - 12);
	glVertex2f(merg2_x44, merg2_y44 - 12);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(merg2_x444, merg2_y444 - 12);
	glVertex2f(merg2_x4444, merg2_y4444 - 12);
	glEnd();
	glPopMatrix();

}

void mergulhadores() {
	if (tx4 > 1100) {
		tx4 = 0;
	}
	merg1 = tx4;
	glPushMatrix();
	glTranslatef(tx4, 0, 0);
	mergulhador();
	glPopMatrix();
}
void mergulhadores2() {
	if (tx5 > 1100) {
		tx5 = 0;
	}
	merg21 = tx5;
	glPushMatrix();
	glTranslatef(tx5, 0, 0);
	mergulhador2();
	glPopMatrix();
}

int verificarColisao() {
	//PEIXE 1
	if (((peixe_y1 > submarino_y1 + up) && (peixe_y1 < submarino_y2 + up)) || ((peixe_y2 > submarino_y1 + up) && (peixe_y2 < submarino_y1 + up))) {
		if (((peixe_x1 + tx > submarino_x + trans) && (peixe_x1 + tx < submarino_x2 + trans)) ||
			((peixe_x2 + tx < submarino_x2 + trans) && (peixe_x2 + tx > submarino_x + trans))) {

			tx = 0;
			trans = 0;
			up = 12;
			return 1;
		}
	}
	//PEIXE 1.2
	if (((peixe1_y1 > submarino_y1 + up) && (peixe1_y1 < submarino_y2 + up)) || ((peixe1_y2 > submarino_y1 + up) && (peixe1_y2 < submarino_y1 + up))) {
		if (((peixe1_x1 + tx1 > submarino_x + trans) && (peixe1_x1 + tx1 < submarino_x2 + trans)) ||
			((peixe1_x2 + tx1 < submarino_x2 + trans) && (peixe1_x2 + tx1 > submarino_x + trans))) {

			tx1 = 0;
			trans = 0;
			up = 12;
			return 1;
		}
	}
	//PEIXE 2
	if (((peixe_y11 > submarino_y1 + up) && (peixe_y11 < submarino_y2 + up)) || ((peixe_y22 > submarino_y1 + up) && (peixe_y22 < submarino_y1 + up))) {
		if (((peixe_x11 + tx2 > submarino_x + trans) && (peixe_x11 + tx2 < submarino_x2 + trans)) ||
			((peixe_x22 + tx2 < submarino_x2 + trans) && (peixe_x22 + tx2 > submarino_x + trans))) {

			tx2 = 0;
			trans = 0;
			up = 12;

			return 2;
		}
	}
	//PEIXE 2.1
	if (((peixe2_y11 > submarino_y1 + up) && (peixe2_y11 < submarino_y2 + up)) || ((peixe2_y22 > submarino_y1 + up) && (peixe2_y22 < submarino_y1 + up))) {
		if (((peixe2_x11 + tx21 > submarino_x + trans) && (peixe2_x11 + tx21 < submarino_x2 + trans)) ||
			((peixe2_x22 + tx21 < submarino_x2 + trans) && (peixe2_x22 + tx21 > submarino_x + trans))) {

			tx21 = 0;
			trans = 0;
			up = 12;

			return 2;
		}
	}
	//PEIXE 3
	if (((peixe_y111 > submarino_y1 + up) && (peixe_y111 < submarino_y2 + up)) || ((peixe_y222 > submarino_y1 + up) && (peixe_y222 < submarino_y1 + up))) {
		if (((peixe_x111 + tx3 > submarino_x + trans) && (peixe_x111 + tx3 < submarino_x2 + trans)) ||
			((peixe_x222 + tx3 < submarino_x2 + trans) && (peixe_x222 + tx3 > submarino_x + trans))) {

			tx3 = 0;
			trans = 0;
			up = 12;

			return 1;
		}
	}
	return 0; // Sem colisão
}
int mergulhadorColisao() {
	if (((mergy1 > submarino_y1 + up) && (mergy1 < submarino_y2 + up)) || ((mergy2 > submarino_y1 + up) &&
		(mergy2 < submarino_y1 + up))) {
		if (((mergx1 + tx4 > submarino_x + trans) && (mergx1 + tx4 < submarino_x2 + trans)) ||
			((mergx2 + tx4 < submarino_x2 + trans) && (mergx2 + tx4 > submarino_x + trans))) {

			tx4 = 0;
			//trans = 0;
			//up = 0;

			return 1;
		}
	}
	//MERGULHADOR 3
	if (((merg2y1 > submarino_y1 + up) && (merg2y1 < submarino_y2 + up)) || ((merg2y2 > submarino_y1 + up) &&
		(merg2y2 < submarino_y1 + up))) {
		if (((merg2x1 + tx5 > submarino_x + trans) && (merg2x1 + tx5 < submarino_x2 + trans)) ||
			((merg2x2 + tx5 < submarino_x2 + trans) && (merg2x2 + tx5 > submarino_x + trans))) {

			tx5 = 0;
			//trans = 0;
			//up = 0;

			return 1;
		}
	}
	return 0;
}

void vidas() {

	int x = 20;  // Coordenada x
	int y = 170;  // Coordenada y
	glRasterPos2f(x, y);
	char texto[24] = "Vida: ";
	snprintf(texto, 10, "%d", vida);
	for (int i = 0; texto[i] != '\0'; i++) {
		glColor3f(1.0, 1.0, 1.0);  // cor
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, texto[i]);
	}
}
void pontuacao() {

	int x = 20;  // Coordenada x
	int y = 140;  // Coordenada y
	glRasterPos2f(x, y);
	char texto[24] = "Vida: ";
	snprintf(texto, 10, "%d", point);
	for (int i = 0; texto[i] != '\0'; i++) {
		glColor3f(1.0, 1.0, 1.0);  // cor
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, texto[i]);
	}
}
void verificaPonto() {
	if (point == 5) {
		++vida;
		point = 0;
	}
}
void verificaO2(int num) {
	if (up < -1) {
		--o2;
	}
	else if(o2 <=99 && up >= 11){
		++o2;
	}
	if (o2 <= 1) {
		printf("AQUIII");
		vida = vida - 1;
		up   = 12;
	}
	int delay = 300;// Atraso de 500milissegundos
	glutTimerFunc(delay, verificaO2, 0);
}
void O2() {
	int x = 10;  // Coordenada x
	int y = 120;  // Coordenada y
	glRasterPos2f(x, y);
	char texto[24] = "";
	snprintf(texto, 10, "%i", o2);
	for (int i = 0; texto[i] != '\0'; i++) {
		glColor3f(1.0, 1.0, 1.0);  // cor
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, texto[i]);
	}
}

void incrementNumber(int value)
{
	static int cont = 0;

	if (count <= 29) ++count;
	if (count == 29) vida = vida - 1; 
	if (count >= 30) {
		count = 0;
		cont++;
	}
	if (cont == 1) isTrue  = true;
	if (cont == 2) isFalse = false;

	glutPostRedisplay(); // Redesenha a cena para atualizar a exibição

	// Define o próximo intervalo de tempo para chamar a função de callback
	int delay = 640;// Atraso de 640milissegundos
	glutTimerFunc(delay, incrementNumber, 0);
}

void desenhar()
{
	agua();
	sol();
	peixes();
	peixes2();
	peixes3();
	if (isTrue) peixes1();
	if (!isFalse) peixes21();
	mergulhadores();
	mergulhadores2();

	vidas();
	pontuacao();
	verificaPonto();
	O2();
	heart();
	//glViewport(200, 300, 400, 600);
	//glOrtho(-200.0, 200.0, -200.0, 200.0, -1.0, 1.0);
	//verificação esquerda
	glTranslatef(trans, up, 0);
	sub();
}

void display()
{
	glMatrixMode(GL_MODELVIEW);  //coordenadas de desenho
	glLoadIdentity();
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // cor do fundo

	// Defina a cor do texto

	glClear(GL_COLOR_BUFFER_BIT);

	// Converte a variável inteira para uma string
	//std::string variableString = std::to_string(VIDA);



	glutSwapBuffers();

	if (mergulhadorColisao()) {
		if (mergulhadorColisao() == 0 && point != 5) {
			++point;
		}
		else if (mergulhadorColisao() == 0 && point == 5) {
			++vida;
			point = 0;
		}
	}

	if (verificarColisao()) {
		//printf("%i\n", verificarColisao());
		if (verificarColisao() == 0 && vida >= 1) {
			--vida;
		}
	}


	glClear(GL_COLOR_BUFFER_BIT); // EXECUTA LIMPESA

	// Especificar o local aonde o desenho acontece: bem no centro da janela
	glTranslatef(janela_largura / 2, janela_altura / 2, 0.0f);

	glViewport(0, 0, janela_largura, janela_altura);
	desenhar();


	glFlush();  // execute o desenho

}

void tela(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// cria a janela (esq, direita, embaixo, em cima)
	gluOrtho2D(0, janela_largura, 0, janela_altura);


	glMatrixMode(GL_MODELVIEW);

}
