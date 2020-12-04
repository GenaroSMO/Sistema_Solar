#include <GL/glut.h>
#include "imageloader.h"
#include "imageloader.h"
//#include <imageloader.h>
//todos los collbacks
//planeta girando alrededor del sol 
//lunas de todos los planetas
//girar las camaras
//mover ariva y abajo
//configuracion de parametros 
//Genaro san martin ortegon
//ing. en computacion
//5° semestre 
//M.C Alfedo Juarez Blanco
//tipo de imagen vnp
//glTexImagen2D investigar
//que parametros resive glTextParameteri
// se le agrega y la clase imagenloager.cpp -lG
GLint ancho= 800;
GLint alto= 800;







int hazPerspectiva = 0;
//parametros gluLookAt
// EyeView : corresponde a la posición de la cámara
float EyeViewX=0.0;
float EyeViewY=0.0;
float EyeViewZ=35.0;
//Center : corresponde al punto hacia donde mira la cámara 
float CenterX=0.0;
float CenterY=0.0;
float CenterZ=0.0;
//UP : es un vector que define la orientación de la cámara
float UpX=0.0;
float UpY=1.0;
float UpZ=0.0;

//parametros sol
float RadioSol=2.843;

//diametro del cada planeta
float DiametroMercurio=.048;
float DiametroVenus=0.121;
float DiametroTierra=0.127;
float DiametroMarte=0.067;
float DiametroJupiter=1.42;
float DiametroSaturno=1.20;
float DiametroUrano=0.518;
float DiametroNeptuno=0.495;
double DiametroPluton=0.022;
float DiametroLunas=0.02;

//distancia de los planes lejanos al sol
float DistanciaSolMer=RadioSol+0.387;
float DistanciaSolVen=RadioSol+0.723;
float DistanciaSolTie=RadioSol+1.49;
float DistanciaSolMar=RadioSol+1.92;
float DistanciaSolJup=RadioSol+5.20;
float DistanciaSolSat=RadioSol+9.539;
float DistanciaSolUra=RadioSol+19.18;
float DistanciaSolNep=RadioSol+25.06;
float DistanciaSolPlu=RadioSol+32.01;

//velocidades de los planetas

float VelocidadMercurio=0.0f;
float VelocidadVenus=0.0f;
float VelocidadTierra=0.0f;
float VelocidadMarte=0.0f;
float VelocidadJupiter=0.0f;
float VelocidadSaturno=0.0f;
float VelocidadUrano=0.0f;
float VelocidadNeptuno=0.0f;
float VelocidadPluton=0.0f;

//rotacion ecuatorial de los planetas;
GLfloat	angulo=0.0f;
GLfloat RotacionEcuatorialMercurio=0.0f;
GLfloat RotacionEcuatorialVenus=0.0f;
GLfloat RotacionEcuatorialTierra=0.0f;
GLfloat RotacionEcuatorialMarte=0.0f;
GLfloat RotacionEcuatorialJupiter=0.0f;
GLfloat RotacionEcuatorialSaturno=0.0f;
GLfloat RotacionEcuatorialUrano=0.0f;
GLfloat RotacionEcuatorialNeptuno=0.0f;
GLfloat RotacionEcuatorialPluton=0.0f;


//iluminacoin de los planetas

GLfloat light_ambient_0 []= {0.1, 0.1, 0.1, 1.0};

//cuadratico


//poisiciones de luz solar 
GLfloat posicionLuzSol_0 []= { 0.0,  0.0, 3.0, 1.0 };
GLfloat posicionLuzSol_1 []= { 0.0,  0.0, 7.0, 1.0 };
GLfloat posicionLuzSol_2 []= { 0.0,  2.0, 5.0, 1.0 };
GLfloat posicionLuzSol_3 []= { 0.0, -2.0, 5.0, 1.0 };
GLfloat posicionLuzSol_4 []= { 2.0,  0.0, 5.0, 1.0 };
GLfloat posicionLuzSol_5 []= {-2.0,  0.0, 5.0, 1.0 };
GLfloat posicionLuzSol_6 []= { 0.0,  0.0, -7.0, 1.0 };

GLfloat light_diffuse    []= { 1.0,  0.6, 0.0, 1.0 };
GLfloat light_specular   []= { 0.0,  0.0, 1.0, 1.0 };
GLfloat light_specular2  []= { 1.0,  1.0, 0.0, 1.0 };

//texturas de todos los planetas


GLuint textura_Sol;
GLuint textura_Mercurio;
GLuint textura_Venus;

GLuint textura_Tierra;
GLuint textura_Luna_Tierra;

GLuint textura_Marte;
GLuint textura_Luna_Uno_Marte;
GLuint textura_Luna_Dos_Marte;

GLuint textura_Jupiter;
GLuint textura_Luna_Uno_Jupiter;
GLuint textura_Luna_Dos_Jupiter;
GLuint textura_Luna_Tres_Jupiter;
GLuint textura_Luna_Cuatro_Jupiter;

GLuint textura_Saturno;
GLuint textura_Luna_Uno_Saturno;
GLuint textura_Luna_Dos_Saturno;
GLuint textura_Luna_Tres_Saturno;

GLuint textura_Urano;
GLuint textura_Luna_Uno_Urano;
GLuint textura_Luna_Dos_Urano;

GLuint textura_Neptuno;
GLuint textura_Luna_Uno_Neptuno;

GLuint textura_Pluton;

GLUquadric *quad;

//pausar
bool  bPausa = false;


void reshape(int width, int height){
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (GLfloat)width/(GLfloat)height, 0.05f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
	ancho = width;
	alto = height;
}

GLuint loadTexture(Image* image) {
	
	GLuint textureId;
	
	glGenTextures(1, &textureId);
	
	glBindTexture(GL_TEXTURE_2D, textureId);
	
	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_RGB,
				 image->width, image->height,
				 0,
				 GL_RGB,
				 GL_UNSIGNED_BYTE,
				 image->pixels);
				 
	return textureId;
}

void SOL(){
	glPushMatrix();	
		glEnable(GL_TEXTURE_2D);  //se activa para que se pueda usar texturas en nustros planetas
			glBindTexture(GL_TEXTURE_2D, textura_Sol);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	
			glRotatef(angulo, 0.0f,1, 0.0f);
			
			gluQuadricTexture(quad,1);
			gluSphere(quad,RadioSol,60,60);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void MERCURIO(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_Mercurio);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			
			glRotatef(VelocidadMercurio,0,1,0);
			glTranslatef(0,0,DistanciaSolMer);
			glRotatef(RotacionEcuatorialMercurio,0,1,0);
			glRotatef(90,1,0,0);
			
			gluQuadricTexture(quad,1);
			gluSphere(quad,DiametroMercurio,70,70);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void VENUS(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_Venus);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		
			glRotatef(VelocidadVenus,0,1,0);
			glTranslatef(0,0,DistanciaSolVen);
			glRotatef(RotacionEcuatorialVenus,0,1,0);
			glRotatef(90,1,0,0);			
			
			gluQuadricTexture(quad,1);
			gluSphere(quad,DiametroVenus,60,60);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void TIERRA(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_Tierra);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			
			glRotatef(VelocidadTierra,0,1,0);
			glTranslatef(0,0,DistanciaSolTie);
			glRotatef(RotacionEcuatorialTierra,0,1,0);
			glRotatef(270,1,0,0);
			
			gluQuadricTexture(quad,1);
			gluSphere(quad,DiametroTierra,60,60);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void LUNA_DE_LA_TIERRA(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_Luna_Tierra);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			
			glRotatef(VelocidadTierra,0,1,0);
			glTranslatef(0,0,DistanciaSolTie+0.2);
			glRotatef(RotacionEcuatorialTierra,0,1,0);
			glRotatef(90,1,0,0);
			
			gluQuadricTexture(quad,1);
			gluSphere(quad,DiametroLunas,60,60);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void LUNA_UNO_DE_MARTE(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_Luna_Uno_Marte);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	
			glRotatef(VelocidadMarte,0,1,0);
			glTranslatef(0,0,DistanciaSolMar+0.15);
			glRotatef(RotacionEcuatorialMarte,0,1,0);
			glRotatef(90,1,0,0);
			
			gluQuadricTexture(quad,1);
			gluSphere(quad,DiametroLunas,60,60);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void LUNA_DOS_DE_MARTE(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_Luna_Dos_Marte);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			
			glRotatef(VelocidadMarte,0,1,0);
			glTranslatef(0.1,0.0,DistanciaSolMar);
			glRotatef(RotacionEcuatorialMarte,0,1,0);
			glRotatef(90,1,0,0);
			
			gluQuadricTexture(quad,1);
			gluSphere(quad,DiametroLunas,60,60);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void MARTE(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_Marte);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			
			glRotatef(VelocidadMarte,0,1,0);
			glTranslatef(0,0,DistanciaSolMar);
			glRotatef(RotacionEcuatorialMarte,0,1,0);
			glRotatef(90,1,0,0);
			
			gluQuadricTexture(quad,1);
			gluSphere(quad,DiametroMarte,60,60);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void JUPITER(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_Jupiter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			
			glRotatef(VelocidadJupiter,0,1,0);
			glTranslatef(0,0,DistanciaSolJup);
			glRotatef(RotacionEcuatorialJupiter,0,1,0);
			glRotatef(90,1,0,0);
			
			gluQuadricTexture(quad,1);
			gluSphere(quad,DiametroJupiter,60,60);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void LUNA_UNO_JUPITER(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_Luna_Uno_Jupiter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			
			glRotatef(VelocidadJupiter,0,1,0);
			glTranslatef(0,0,DiametroJupiter+DistanciaSolJup+0.25);
			glRotatef(RotacionEcuatorialJupiter,0,1,0);
			glRotatef(90,1,0,0);
			
			gluQuadricTexture(quad,1);
			gluSphere(quad,DiametroLunas+.10,60,60);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void LUNA_DOS_JUPITER(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_Luna_Dos_Jupiter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			
			glRotatef(VelocidadJupiter,0,1,0);
			glTranslatef(DiametroJupiter+0.1,0,DistanciaSolJup);
			glRotatef(RotacionEcuatorialJupiter,0,1,0);
			
			gluQuadricTexture(quad,1);
			gluSphere(quad,DiametroLunas+.10,60,60);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void LUNA_TRES_JUPITER(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_Luna_Tres_Jupiter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			
			glRotatef(VelocidadJupiter,0,1,0);
			glTranslatef(-DiametroJupiter-0.1,0,DiametroJupiter+DistanciaSolJup);
			glRotatef(RotacionEcuatorialJupiter,0,1,0);
			
			gluQuadricTexture(quad,1);
			gluSphere(quad,DiametroLunas+.10,60,60);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void LUNA_CUATRO_JUPITER(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_Luna_Cuatro_Jupiter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			
			glRotatef(VelocidadJupiter,0,1,0);
			glTranslatef(0,0,DistanciaSolJup-(0.3+DiametroJupiter));
			glRotatef(RotacionEcuatorialJupiter,0,1,0);
			
			gluQuadricTexture(quad,1);
			gluSphere(quad,DiametroLunas+.10,60,60);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void SATURNO(){
	//gluDisk(2,4,4,6);
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_Saturno);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			
			glRotatef(VelocidadSaturno,0,1,0);			
			glTranslatef(0,0,DistanciaSolSat);			
			glRotatef(RotacionEcuatorialSaturno,0,1,0);
			glRotatef(90,1,0,0);
			
			
			gluQuadricTexture(quad,1);
			gluSphere(quad,DiametroSaturno,60,60);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void LUNA_UNO_SATURNO(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_Luna_Uno_Saturno);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			
			glRotatef(VelocidadSaturno,0,1,0);
			glTranslatef(0.0f,0.5f,(DistanciaSolSat+0.25+DiametroSaturno));
			glRotatef(RotacionEcuatorialSaturno,0,1,0);
			
			gluQuadricTexture(quad,1);
			gluSphere(quad,DiametroLunas+.10,60,60);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void LUNA_DOS_SATURNO(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_Luna_Dos_Saturno);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
			
			glRotatef(VelocidadSaturno,0,1,0);
			glTranslatef((0.2+DiametroSaturno),0,(DistanciaSolSat+0.35+DiametroSaturno));
			glRotatef(RotacionEcuatorialSaturno,0,1,0);			
			
			gluQuadricTexture(quad,1);
			gluSphere(quad,DiametroLunas+.10,60,60);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void LUNA_TRES_SATURNO(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_Luna_Tres_Saturno);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
			
			glRotatef(VelocidadSaturno,0,1,0);
			glTranslatef(0,(0.15+DiametroSaturno),DistanciaSolSat);
			glRotatef(RotacionEcuatorialSaturno,0,1,0);
			
			
			gluQuadricTexture(quad,1);
			gluSphere(quad,DiametroLunas+.10,60,60);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void ANILLO_SATURNO(){
	glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_Luna_Tres_Saturno);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			
			glRotatef(VelocidadSaturno,0,1,0);
			glTranslatef(0,0,DistanciaSolSat);
			glRotatef(90,2,0,0);
			//gluDisk(2,4,4,6);
			
			gluQuadricTexture(quad,1);
			gluDisk(quad,0,(DiametroSaturno+0.50), 60, 2 );
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void URANO(){
	glPushMatrix();	
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_Urano);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			
			glRotatef(VelocidadUrano,0,1,0);
			glTranslatef(0.0f,00.0f,DistanciaSolUra);
			glRotatef(RotacionEcuatorialUrano,0,1,0);
			glRotatef(90,1,0,0);
		
			gluQuadricTexture(quad,1);
			gluSphere(quad,DiametroUrano,60,60);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void LUNA_UNO_URANO(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_Luna_Uno_Urano);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				
			glRotatef(VelocidadUrano,0,1,0);
			glTranslatef(0,1,(DistanciaSolUra+(0.25+DiametroUrano)));
			glRotatef(RotacionEcuatorialUrano,0,1,0);
			
			gluQuadricTexture(quad,1);
			gluSphere(quad,DiametroLunas+.05,60,60);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void LUNA_DOS_URANO(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_Luna_Dos_Urano);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			
			glRotatef(VelocidadUrano,0,1,0);
			glTranslatef(1.5,0,(DistanciaSolUra+(0.25+DiametroUrano)));
			glRotatef(RotacionEcuatorialUrano,0,1,0);
			
			gluQuadricTexture(quad,1);
			gluSphere(quad,DiametroLunas+.05,60,60);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void NEPTUNO(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_Neptuno);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			
			glRotatef(VelocidadNeptuno,0,1,0);
			glTranslatef(0.0f,0.0f,DistanciaSolNep);
			glRotatef(RotacionEcuatorialNeptuno,0,1,0);
			glRotatef(90,1,0,0);
			
			gluQuadricTexture(quad,1);
			gluSphere(quad,DiametroNeptuno,60,60);			
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void LUNA_UNO_NEPTUNO(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_Luna_Uno_Neptuno);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glRotatef(VelocidadNeptuno,0,1,0);
			glTranslatef(0,1,(DistanciaSolNep+(0.25+DiametroNeptuno)));
			glRotatef(RotacionEcuatorialNeptuno,0,1,0);
			
			gluQuadricTexture(quad,1);
			gluSphere(quad,DiametroLunas+.05,60,60);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void PLUTON(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_Pluton);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			
			glRotatef(VelocidadPluton,0,1,0);
			glTranslatef(0.0f,0.0f,DistanciaSolPlu);
			glRotatef(RotacionEcuatorialPluton,0,1,0);
			glRotatef(90,1,0,0);
			
			gluQuadricTexture(quad,1);
			gluSphere(quad,DiametroPluton,60,60);			
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
}


void display(){	
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt (EyeViewX,EyeViewY,EyeViewZ,CenterX,CenterY,CenterZ,UpX,UpY,UpZ);
	
	glLightModelfv (GL_LIGHT_MODEL_AMBIENT, light_ambient_0);
	float linear_atenuation=0.0099,quadratic_atenuation=0.0099;
	//luz 0	
	glLightfv (GL_LIGHT0, GL_POSITION, posicionLuzSol_0);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular2);	
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,1);
	glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION,linear_atenuation);
	glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,quadratic_atenuation);			
	glEnable (GL_LIGHT0);
	
	//luz 1
	glLightfv (GL_LIGHT1, GL_POSITION, posicionLuzSol_1);	
	glLightfv (GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv (GL_LIGHT1, GL_SPECULAR, light_specular);	
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION,1);
	glLightf(GL_LIGHT1,GL_LINEAR_ATTENUATION,linear_atenuation);
	glLightf(GL_LIGHT1,GL_QUADRATIC_ATTENUATION,quadratic_atenuation);			
	glEnable (GL_LIGHT1);
	
	//luz 2
	glLightfv (GL_LIGHT2, GL_POSITION, posicionLuzSol_2);
	glLightfv (GL_LIGHT2, GL_DIFFUSE, light_diffuse);
	glLightfv (GL_LIGHT2, GL_SPECULAR, light_specular);	
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION,1);
	glLightf(GL_LIGHT2,GL_LINEAR_ATTENUATION,linear_atenuation);
	glLightf(GL_LIGHT2,GL_QUADRATIC_ATTENUATION,quadratic_atenuation);	
	glEnable (GL_LIGHT2);
	
	//luz 3
	glLightfv (GL_LIGHT3, GL_POSITION, posicionLuzSol_3);
	glLightfv (GL_LIGHT3, GL_DIFFUSE, light_diffuse);
	glLightfv (GL_LIGHT3, GL_SPECULAR, light_specular);		
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION,1);
	glLightf(GL_LIGHT3,GL_LINEAR_ATTENUATION,linear_atenuation);
	glLightf(GL_LIGHT3,GL_QUADRATIC_ATTENUATION,quadratic_atenuation);		
	glEnable (GL_LIGHT3);
		
	//luz 4
	glLightfv (GL_LIGHT4, GL_POSITION, posicionLuzSol_4);
	glLightfv (GL_LIGHT4, GL_DIFFUSE, light_diffuse);
	glLightfv (GL_LIGHT4, GL_SPECULAR, light_specular);	
	glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION,1);
	glLightf(GL_LIGHT4,GL_LINEAR_ATTENUATION,linear_atenuation);	
	glLightf(GL_LIGHT4,GL_QUADRATIC_ATTENUATION,quadratic_atenuation);
	glEnable (GL_LIGHT4);
	
	//luz 5
	glLightfv (GL_LIGHT5, GL_POSITION, posicionLuzSol_5);
	glLightfv (GL_LIGHT5, GL_DIFFUSE, light_diffuse);
	glLightfv (GL_LIGHT5, GL_SPECULAR, light_specular);	
	glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION,1);
	glLightf(GL_LIGHT5,GL_LINEAR_ATTENUATION,linear_atenuation);
	glLightf(GL_LIGHT5,GL_QUADRATIC_ATTENUATION,quadratic_atenuation);
	glEnable (GL_LIGHT5);
	
	//luz 6
	glLightfv (GL_LIGHT6, GL_POSITION, posicionLuzSol_6);
	glLightfv (GL_LIGHT6, GL_DIFFUSE, light_diffuse);
	glLightfv (GL_LIGHT6, GL_SPECULAR, light_specular);	
	glLightf(GL_LIGHT6, GL_CONSTANT_ATTENUATION,1);
	glLightf(GL_LIGHT6,GL_LINEAR_ATTENUATION,linear_atenuation);	
	glLightf(GL_LIGHT6,GL_QUADRATIC_ATTENUATION,quadratic_atenuation);
	glEnable (GL_LIGHT6);
	
	
	SOL();
	
	MERCURIO();
	
	VENUS();
	
	TIERRA();
	LUNA_DE_LA_TIERRA();
	
	MARTE();
	LUNA_UNO_DE_MARTE();
	LUNA_DOS_DE_MARTE();
	
	JUPITER();
	LUNA_UNO_JUPITER();
	LUNA_DOS_JUPITER();
	LUNA_TRES_JUPITER();
	LUNA_CUATRO_JUPITER();
	
	SATURNO();
	LUNA_UNO_SATURNO();
	LUNA_DOS_SATURNO();
	LUNA_TRES_SATURNO();
	ANILLO_SATURNO();
	
	URANO();
	LUNA_UNO_URANO();
	LUNA_DOS_URANO();
	
	NEPTUNO();
	LUNA_UNO_NEPTUNO();
	
	PLUTON();
	
	glFlush();
	glutSwapBuffers();
}

void init(){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glClearColor(0,0,0,0);
	ancho = 800;
	alto = 800;
	quad = gluNewQuadric();
	
	
	Image* sol 		= loadBMP("sol.bmp");
	Image* mercurio= loadBMP("Mercurio.bmp");
	Image* venus= loadBMP("Venus.bmp");
	Image* tierra= loadBMP("Tierra.bmp");
	Image* luna_tierra= loadBMP("Luna_Tierra.bmp");
	
	Image* marte= loadBMP("Marte.bmp");
	Image* luna_uno_marte= loadBMP("LunaUnoMarte.bmp");
	Image* luna_dos_marte= loadBMP("LunaDosMarte.bmp");
	
	Image* jupiter= loadBMP("Jupiter.bmp");
	Image* luna_uno_jupiter= loadBMP("LunaUnoJupiter.bmp");
	Image* luna_dos_jupiter= loadBMP("LunaDosJupiter.bmp");
	Image* luna_tres_jupiter= loadBMP("LunaTresJupiter.bmp");
	Image* luna_cuatro_jupiter= loadBMP("LunaCuatroJupiter.bmp");
	
	Image* saturno= loadBMP("Saturno.bmp");
	Image* luna_uno_saturno= loadBMP("LunaUnoSaturno.bmp");
	Image* luna_dos_saturno= loadBMP("LunaDosSaturno.bmp");
	Image* luna_tres_saturno= loadBMP("LunaTresSaturno.bmp");
	
	Image* urano= loadBMP("Urano.bmp");
	Image* luna_uno_urano= loadBMP("LunaUnoUrano.bmp");
	Image* luna_dos_urano= loadBMP("LunaDosUrano.bmp");
	
	
	Image* neptuno= loadBMP("Neptuno.bmp");
	Image* luna_uno_neptuno= loadBMP("LunaNeptuno.bmp");
	
	Image* pluton= loadBMP("Pluton.bmp");
	
	textura_Sol= loadTexture(sol);
	textura_Mercurio= loadTexture(mercurio);
	textura_Venus= loadTexture(venus);
	
	textura_Tierra= loadTexture(tierra);
	textura_Luna_Tierra= loadTexture(luna_tierra);
	
	textura_Marte= loadTexture(marte);
	textura_Luna_Uno_Marte=loadTexture(luna_uno_marte);
	textura_Luna_Dos_Marte=loadTexture(luna_dos_marte);
	
	textura_Jupiter= loadTexture(jupiter);
	textura_Luna_Uno_Jupiter=loadTexture(luna_uno_jupiter);
	textura_Luna_Dos_Jupiter=loadTexture(luna_dos_jupiter);
	textura_Luna_Tres_Jupiter=loadTexture(luna_tres_jupiter);
	textura_Luna_Cuatro_Jupiter=loadTexture(luna_cuatro_jupiter);//ys
	
	
	textura_Saturno= loadTexture(saturno);
	textura_Luna_Uno_Saturno= loadTexture(luna_uno_saturno);
	textura_Luna_Dos_Saturno= loadTexture(luna_dos_saturno);
	textura_Luna_Tres_Saturno= loadTexture(luna_tres_saturno);
	
	textura_Urano= loadTexture(urano);
	textura_Luna_Uno_Urano= loadTexture(luna_uno_urano);
	textura_Luna_Dos_Urano= loadTexture(luna_dos_urano);
	
	textura_Neptuno= loadTexture(neptuno);
	textura_Luna_Uno_Neptuno= loadTexture(luna_uno_neptuno);
	
	textura_Pluton=loadTexture(pluton);
	
	
	delete sol;
	delete mercurio;
	delete venus;
	delete tierra;
	delete luna_tierra;
		
	delete marte;
	delete luna_uno_marte;
	delete luna_dos_marte;
	
	
	delete jupiter;
	delete luna_uno_jupiter;
	delete luna_dos_jupiter;
	delete luna_tres_jupiter;
	delete luna_cuatro_jupiter;
	
	delete saturno;
	delete luna_uno_saturno;
	delete luna_dos_saturno;
	delete luna_tres_saturno;
	
	
	delete urano;
	delete luna_uno_urano;
	delete luna_dos_urano;
	
	delete neptuno;
	delete luna_uno_neptuno;	
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

void idle(){
	if( false == bPausa ) {
		VelocidadMercurio+=1.72;
		VelocidadVenus+=1.26;
		VelocidadTierra+=1.07;
		VelocidadMarte+=0.86;
		VelocidadJupiter+=0.47;
		VelocidadSaturno+=0.34;
		VelocidadUrano+=0.24;
		VelocidadNeptuno+=0.19;
		VelocidadPluton+=0.10;
	}
	angulo+=1.5f;
	RotacionEcuatorialMercurio+=0.10;
	RotacionEcuatorialVenus+=0.6;
	RotacionEcuatorialTierra+=1.6;
	RotacionEcuatorialMarte+=0.8;
	RotacionEcuatorialJupiter+=4.5;
	RotacionEcuatorialSaturno+=3.6;
	RotacionEcuatorialUrano+=1.9;
	RotacionEcuatorialNeptuno+=0.9;
	RotacionEcuatorialPluton+=0.8;
	display();
}

void specialKeys( int key, int x, int y ) {
	//tecla derecha
	if (key == GLUT_KEY_RIGHT)
		CenterX-=0.5;
	//tecla izquierda
	else if (key == GLUT_KEY_LEFT)
		CenterX+=0.5;
	//tecla ariva
	else if (key == GLUT_KEY_UP)
		EyeViewZ-=0.5;
	//tecla abajo
	else if (key == GLUT_KEY_DOWN)
		EyeViewZ+=0.5;
		// lo que quiero despues EyeViewX  EyeViewY
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 'd':
			EyeViewX+=0.5;
			break;
		case 'a':
			EyeViewX-=0.5;
			break;
		//con w y s se puede ver asia adelante y acia a tras la camara	
		case 'w':
			EyeViewY+=0.5;
			break;
		case 's':
			EyeViewY-=0.5;
			break;
		case 'p':
            bPausa = true;
            break;
        case 'c':
            bPausa = false;
            break;
		case 27:
			exit(0);
			break;
	}
}

	
int main(int argc, char **argv){
	// Inicializa la librería auxiliar GLUT 
	glutInit(&argc, argv);
	// Inicializa el modo de visualización 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	// Indica la posición inicial (xmin,ymin) 
	glutInitWindowPosition(800, 800);
	// Indica el tamaño de la ventana (ancho,alto) 
	glutInitWindowSize(ancho, alto);
	// Abre la ventana con el título indicado 
	glutCreateWindow("sistema solar");
	// Inicializar valores 
	init();	
	// Indica cual es la función de dibujo  
	glutDisplayFunc(display);
	// Indica cual es la función para el cambio de tamaño de la ventana 
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);
	
	glutMainLoop();
	
	return 0;
	
}
/*

void menuStatusFunc(int status, int x, int y){
    
        -Descripción:
           Estado del menú global para un programa GLUT puede determinar cuando un menú está en uso o no.

        -Parametros:
            El X y Y. parámetros indican la ubicación en la ventana que causó el menú para entrar en uso, o el lugar donde fue puesto en libertad
           el menú (puede ser fuera de la ventana).
}


void menuStateFunc(int status){    
        -Descripción:
           Estado del menú global para un programa GLUT puede determinar cuando un menú está en uso o no. Solo recibe el status mas
           no la posición de la ventana que lo mandó a llamar.
  
}

void glutTabletButtonFunc(int button, int state, int x, int y){    
        -Descripción:
            Se llama cuando la ventana tiene el foco de entrada de la tableta (normalmente, cuando el ratón está en la ventana) y el usuario
            genera pulsaciones de los botones de la tableta. El botón de parámetro será el número de botón (a partir de uno).

        -Parametros:
            Los X y Y. parámetros de devolución de llamada indican las coordenadas relativas de la ventana cuando el estado de los botones
            de la tableta cambió.


}
void glutTabletMotionFunc(int x, int y){
       
        -Descripción:
             Se llama cuando la ventana tiene el foco de entrada de la tableta (normalmente, cuando el ratón está en la ventana)
             y el usuario genera un movimiento de la tableta.

        -Parametros:
                Los X y Y indican la posición absoluta de la tableta. Los parámetros de devolución de llamada se normalizan a
                estar dentro del rango de 0 a 2000.
}


void glutDialsFunc(int dial, int value){
        -Descripción:
            Se llama cuando la ventana tiene el foco de entrada de marcado y caja de botones (normalmente, cuando el ratón está en la ventana)
            y el usuario genera y marcar los cambios de marcación caja de botones. El parámetro será el número de marcado (a partir de uno).
            El valor mide la rotación absoluta en grados.

        -Parametros:
            GLUT_NUM_DIALS: úmero de marcaciones disponibles de dial y caja de botones se puede determinar

    

}

void glutTimerFunc(int value){    
        -Descripción:
            glutTimerFunc registra el temporizador de devolución de llamada func a ser activado en al menos milisegundos milisegundos.
            El valor de parámetro para la devolución de llamada del temporizador será el valor del valor de parámetro para glutTimerFunc.
            Las rutinas de temporización en múltiples iguales o diferentes tiempos pueden ser registrados simultáneamente.

            El número de milisegundos es un límite inferior en el tiempo para que se genere la devolución de llamada.
            GLUT intenta entregar el temporizador de devolución de llamada tan pronto como sea posible después de la expiración del
            intervalo de tiempo de la devolución de llamada.
    
}

void buttonBoxFunc(int button, int state){
    
        -Descripción:
            Se llama cuando la ventana tiene el foco de entrada de marcado y caja de botones (normalmente, cuando el ratón está en la ventana)
            y el usuario genera pulsadores de botón de cuadro y botón. El botón de parámetro será el número de botón (a partir de uno).
        
}

void glutSpaceballButtonFunc (int button, int state){    
        -Descripción:
            Se llama cuando la ventana tiene el foco de entrada Spaceball (normalmente, cuando el ratón está en la ventana) y el usuario
            genera pulsaciones de botón Spaceball.
    
}
void spaceballRotateFunc(int x, int y, int z){    
        -Descripción:
           Se llama cuando la ventana tiene el foco de entrada Spaceball (normalmente, cuando el ratón está en la ventana)
           y el usuario genera rotaciones Spaceball.
        -Parametros:
           Los x , Y , y Z parámetros de devolución de llamada indican la rotación a lo largo de los ejes X, Y, y Z.
           Los parámetros de devolución de llamada se normalizan a estar dentro de la gama de -1.800-1.800   
}

void spaceballMotionFunc (int x, int y, int z){    
        -Descripción:
            Se manda a llamar cuando ocurre el movimieto del Spaceball dentro de la ventana.

        -Parametros:
            Los X , Y , y Z parámetros de devolución de llamada indican las traducciones a
            lo largo de los ejes X, Y, y Z.. Los parámetros de devolución de llamada se normalizan
            para estar dentro de la gama de -1000 a 1000  

}
void entryFunc(int state){    
        -Descripción:
            Lee cuando el mouse entra o sale de la pantalla    
}

void visibilityFunc(){    
    -Descripción:
      Se manda a llamar cuando la visibilidad de una ventana cambia.
}

void passiveMotionFunc(int x,int y){    
    -Descripcion:
        Funcion que lee cuando el putero del mouse entra sin que este presionado algun boton  

}


void motionFunc(int x,int y){
    -Descripcion:
        Funcion que lee cuando el putero del mouse entra mientras el mouse va presionado.
}

void mouseFuncion(int button, int state, int x,int y){
     
     -Descripcion:
        Leee los eventos del mouse
   
}
*/



















