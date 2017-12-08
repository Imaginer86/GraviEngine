#pragma once
#include "Simulation.h"

class MassConnectedWithSpring : public Simulation
{
public:
	float springConstant;    // ������ springConstant, ������� ����
							 // ����������.
	Vector3f connectionPos;  // �����

							 // ����������� ������� ������� ������ � 1� ������ � 1 ��.
	MassConnectedWithSpring(float _springConstant)
	:Simulation(1)
	,springConstant(_springConstant)// ���������� springConstant
	,connectionPos(0.0f, 0.0f, 0.0f)// � connectionPos.
	{
		// ��������� ����� ������������ connectionPos.
		//masses[0]->pos = connectionPos + Vector3f(5.0f, 0.0f, 0.0f);
		// �������� 0
		//masses[0]->vel = Vector3f(0.0f, 1.0f, 0.0f);
	}
	virtual void solve() // ����� ����������� ���� �������
	{
		for (int a = 0; a < numOfMasses; ++a)
		{
			// ������� ������ �� ����� �� ����� ����������
			Vector3f springVector = masses[a]->pos - connectionPos;
			// ��������� ���� �������� �� �������
			masses[a]->applyForce(-springVector * springConstant);
		}
	}

};
