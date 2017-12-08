#pragma once
#include "Simulation.h"

class MotionUnderGravitation : public Simulation
{
public:
	Vector3f gravitation;    // ��������� ���������� �������

							 // ����������� ������� ������� ������ � 1� ������ � 1 ��.
							 // Vector3D Gravitation - ��������� ���������� �������

	MotionUnderGravitation(Vector3f _gravitation)
	:Simulation(1)
	,gravitation(_gravitation)
	{

		//masses[0]->pos = Vector3f(-10.0f, 0.0f, 0.0f);
		//masses[0]->vel = Vector3f(1.0f, 5.0f, -5.0f);
	}
	// ��������� �� ��������� ����, ��� ����������� ����� "Solve".
	virtual void solve()
	{
		// ��������� ���� �� ���� ������
		for (int a = 0; a < numOfMasses; ++a)
			// ���� ���������� ��� F = m * g.
			masses[a]->applyForce(gravitation * masses[a]->m);
	}
};
