#include "Box.h"

#include "..\gl\glaux.h"

void Box::Draw()
{
	glPushMatrix();
	Vector3 posr = GetPos();
	Vector3 pos;
	Vector3 size = GetSize();
	Vector3 angle = GetAngle();
	Color4f color = GetColor();

	glTranslatef(posr.x, posr.y, posr.z);
	//glRotatef(angle.x, 1, 0, 0);
	//glRotatef(angle.y, 0, 1, 0);
	//glRotatef(angle.z, 0, 0, 1);

	float anglef = 360.0f*acosf(q.w)/Math::PI;
	glRotatef(anglef, q.x, q.y, q.z);

	glColor3f(color.r, color.g, color.b);

	glBegin(GL_QUADS);       // Начало рисования четырехугольников
	// Передняя грань
	//glNormal3f( 0.0f, 0.0f, 1.0f);     // Нормаль указывает на наблюдателя
	glVertex3f(pos.x - size.x/2.0f, pos.y - size.y/2.0f,  pos.z + size.z/2.0f); // Точка 1 (Перед)
	glVertex3f(pos.x + size.x/2.0f, pos.y - size.y/2.0f,  pos.z + size.z/2.0f); // Точка 2 (Перед)
	glVertex3f(pos.x + size.x/2.0f, pos.y + size.y/2.0f,  pos.z + size.z/2.0f); // Точка 3 (Перед)
	glVertex3f(pos.x - size.x/2.0f, pos.y + size.y/2.0f,  pos.z + size.z/2.0f); // Точка 4 (Перед)
	// Задняя грань
	//glNormal3f( 0.0f, 0.0f,-1.0f);     // Нормаль указывает от наблюдателя
	glVertex3f(pos.x - size.x/2.0f, pos.y - size.y/2.0f,  pos.z - size.z/2.0f); // Точка 1 (Зад)
	glVertex3f(pos.x + size.x/2.0f, pos.y - size.y/2.0f,  pos.z - size.z/2.0f); // Точка 2 (Зад)
	glVertex3f(pos.x + size.x/2.0f, pos.y + size.y/2.0f,  pos.z - size.z/2.0f); // Точка 3 (Зад)
	glVertex3f(pos.x - size.x/2.0f, pos.y + size.y/2.0f,  pos.z - size.z/2.0f); // Точка 4 (Зад)
	// Верхняя грань
	// 		glNormal3f( 0.0f, 1.0f, 0.0f);     // Нормаль указывает вверх
	// 		glVertex3f(-1.0f,  1.0f, -1.0f); // Точка 1 (Верх)
	// 		glVertex3f(-1.0f,  1.0f,  1.0f); // Точка 2 (Верх)
	// 		glVertex3f( 1.0f,  1.0f,  1.0f); // Точка 3 (Верх)
	//		glVertex3f( 1.0f,  1.0f, -1.0f); // Точка 4 (Верх)
	glVertex3f(pos.x - size.x/2.0f, pos.y + size.y/2.0f,  pos.z - size.z/2.0f); // Точка 1 (Верх)
	glVertex3f(pos.x + size.x/2.0f, pos.y + size.y/2.0f,  pos.z - size.z/2.0f); // Точка 2 (Верх)
	glVertex3f(pos.x + size.x/2.0f, pos.y + size.y/2.0f,  pos.z + size.z/2.0f); // Точка 3 (Верх)
	glVertex3f(pos.x - size.x/2.0f, pos.y + size.y/2.0f,  pos.z + size.z/2.0f); // Точка 4 (Верх)

	// Нижняя грань
	glNormal3f( 0.0f,-1.0f, 0.0f);     // Нормаль указывает вниз
	glVertex3f(pos.x - size.x/2.0f, pos.y - size.y/2.0f,  pos.z - size.z/2.0f); // Точка 1 (Верх)
	glVertex3f(pos.x + size.x/2.0f, pos.y - size.y/2.0f,  pos.z - size.z/2.0f); // Точка 2 (Верх)
	glVertex3f(pos.x + size.x/2.0f, pos.y - size.y/2.0f,  pos.z + size.z/2.0f); // Точка 3 (Верх)
	glVertex3f(pos.x - size.x/2.0f, pos.y - size.y/2.0f,  pos.z + size.z/2.0f); // Точка 4 (Верх)
	// Правая грань
	glNormal3f( 1.0f, 0.0f, 0.0f);     // Нормаль указывает вправо
	glVertex3f(pos.x + size.x/2.0f, pos.y + size.y/2.0f,  pos.z - size.z/2.0f); // Точка 1 (Верх)
	glVertex3f(pos.x + size.x/2.0f, pos.y + size.y/2.0f,  pos.z + size.z/2.0f); // Точка 2 (Верх)
	glVertex3f(pos.x + size.x/2.0f, pos.y - size.y/2.0f,  pos.z + size.z/2.0f); // Точка 3 (Верх)
	glVertex3f(pos.x + size.x/2.0f, pos.y - size.y/2.0f,  pos.z - size.z/2.0f); // Точка 4 (Верх)
	// Левая грань
	glNormal3f(-1.0f, 0.0f, 0.0f);     // Нормаль указывает влево
	glVertex3f(pos.x - size.x/2.0f, pos.y + size.y/2.0f,  pos.z - size.z/2.0f); // Точка 1 (Верх)
	glVertex3f(pos.x - size.x/2.0f, pos.y + size.y/2.0f,  pos.z + size.z/2.0f); // Точка 2 (Верх)
	glVertex3f(pos.x - size.x/2.0f, pos.y - size.y/2.0f,  pos.z + size.z/2.0f); // Точка 3 (Верх)
	glVertex3f(pos.x - size.x/2.0f, pos.y - size.y/2.0f,  pos.z - size.z/2.0f); // Точка 4 (Верх)
	glEnd();

	glPopMatrix();


}