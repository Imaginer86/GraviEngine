#include "Box.h"

#include "..\gl\glaux.h"

void Box::Draw()
{
	glPushMatrix();
	Vector3 pos = GetPos();
	Vector3 size = GetSize();
	Vector3 angle = GetAngle();
	Color4f color = GetColor();

	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(angle.x, 1, 0, 0);
	glRotatef(angle.y, 0, 1, 0);
	glRotatef(angle.z, 0, 0, 1);

	glColor3f(color.r, color.g, color.b);

	glBegin(GL_QUADS);       // ������ ��������� �����������������
	// �������� �����
	//glNormal3f( 0.0f, 0.0f, 1.0f);     // ������� ��������� �� �����������
	glVertex3f(pos.x - size.x/2.0f, pos.y - size.y/2.0f,  pos.z + size.z/2.0f); // ����� 1 (�����)
	glVertex3f(pos.x + size.x/2.0f, pos.y - size.y/2.0f,  pos.z + size.z/2.0f); // ����� 2 (�����)
	glVertex3f(pos.x + size.x/2.0f, pos.y + size.y/2.0f,  pos.z + size.z/2.0f); // ����� 3 (�����)
	glVertex3f(pos.x - size.x/2.0f, pos.y + size.y/2.0f,  pos.z + size.z/2.0f); // ����� 4 (�����)
	// ������ �����
	//glNormal3f( 0.0f, 0.0f,-1.0f);     // ������� ��������� �� �����������
	glVertex3f(pos.x - size.x/2.0f, pos.y - size.y/2.0f,  pos.z - size.z/2.0f); // ����� 1 (���)
	glVertex3f(pos.x + size.x/2.0f, pos.y - size.y/2.0f,  pos.z - size.z/2.0f); // ����� 2 (���)
	glVertex3f(pos.x + size.x/2.0f, pos.y + size.y/2.0f,  pos.z - size.z/2.0f); // ����� 3 (���)
	glVertex3f(pos.x - size.x/2.0f, pos.y + size.y/2.0f,  pos.z - size.z/2.0f); // ����� 4 (���)
	// ������� �����
	// 		glNormal3f( 0.0f, 1.0f, 0.0f);     // ������� ��������� �����
	// 		glVertex3f(-1.0f,  1.0f, -1.0f); // ����� 1 (����)
	// 		glVertex3f(-1.0f,  1.0f,  1.0f); // ����� 2 (����)
	// 		glVertex3f( 1.0f,  1.0f,  1.0f); // ����� 3 (����)
	//		glVertex3f( 1.0f,  1.0f, -1.0f); // ����� 4 (����)
	glVertex3f(pos.x - size.x/2.0f, pos.y + size.y/2.0f,  pos.z - size.z/2.0f); // ����� 1 (����)
	glVertex3f(pos.x + size.x/2.0f, pos.y + size.y/2.0f,  pos.z - size.z/2.0f); // ����� 2 (����)
	glVertex3f(pos.x + size.x/2.0f, pos.y + size.y/2.0f,  pos.z + size.z/2.0f); // ����� 3 (����)
	glVertex3f(pos.x - size.x/2.0f, pos.y + size.y/2.0f,  pos.z + size.z/2.0f); // ����� 4 (����)

	// ������ �����
	glNormal3f( 0.0f,-1.0f, 0.0f);     // ������� ��������� ����
	glVertex3f(pos.x - size.x/2.0f, pos.y - size.y/2.0f,  pos.z - size.z/2.0f); // ����� 1 (����)
	glVertex3f(pos.x + size.x/2.0f, pos.y - size.y/2.0f,  pos.z - size.z/2.0f); // ����� 2 (����)
	glVertex3f(pos.x + size.x/2.0f, pos.y - size.y/2.0f,  pos.z + size.z/2.0f); // ����� 3 (����)
	glVertex3f(pos.x - size.x/2.0f, pos.y - size.y/2.0f,  pos.z + size.z/2.0f); // ����� 4 (����)
	// ������ �����
	glNormal3f( 1.0f, 0.0f, 0.0f);     // ������� ��������� ������
	glVertex3f(pos.x + size.x/2.0f, pos.y + size.y/2.0f,  pos.z - size.z/2.0f); // ����� 1 (����)
	glVertex3f(pos.x + size.x/2.0f, pos.y + size.y/2.0f,  pos.z + size.z/2.0f); // ����� 2 (����)
	glVertex3f(pos.x + size.x/2.0f, pos.y - size.y/2.0f,  pos.z + size.z/2.0f); // ����� 3 (����)
	glVertex3f(pos.x + size.x/2.0f, pos.y - size.y/2.0f,  pos.z - size.z/2.0f); // ����� 4 (����)
	// ����� �����
	glNormal3f(-1.0f, 0.0f, 0.0f);     // ������� ��������� �����
	glVertex3f(pos.x - size.x/2.0f, pos.y + size.y/2.0f,  pos.z - size.z/2.0f); // ����� 1 (����)
	glVertex3f(pos.x - size.x/2.0f, pos.y + size.y/2.0f,  pos.z + size.z/2.0f); // ����� 2 (����)
	glVertex3f(pos.x - size.x/2.0f, pos.y - size.y/2.0f,  pos.z + size.z/2.0f); // ����� 3 (����)
	glVertex3f(pos.x - size.x/2.0f, pos.y - size.y/2.0f,  pos.z - size.z/2.0f); // ����� 4 (����)
	glEnd();

	glPopMatrix();


}