#pragma once
#include "Entity.h"
#include "Render.h"

class Simulation
{
public:
	unsigned numOfMasses;    // ���������� ���� � ����������.
	Entity** masses;         // ����� �������� � 1d ������� ����������

	Simulation(int _numOfMasses)
	{
		numOfMasses = _numOfMasses;
		masses = new Entity*[numOfMasses]; // ������� ������ ����������.

										 // ������� Mass � ������� ��� � ������
		for (unsigned a = 0; a < numOfMasses; ++a)
			masses[a] = new Entity;
	}

	virtual ~Simulation()      // ������ ������ ����
	{
		for (unsigned a = 0; a < numOfMasses; ++a)
		{
			delete masses[a];
			//masses[a] = NULL;
		}

		delete[] masses;
		//masses = NULL;
	}

	Entity* getMass(unsigned index)
	{
		// ���� ������ ������� �� ����� ������� ���������� null
		if (index < 0 || index >= numOfMasses) return NULL;

		// ���������� ����� �� �������
		return masses[index];
	}

	virtual void init()      // �������� init() ��� ������ �����
	{
		for (unsigned a = 0; a < numOfMasses; ++a)
			masses[a]->init();
	}

	virtual void solve()
	{
		// ��� ���� �.�. � ������� ������ � ��� ��� ���
		// � ������ ����������� �� ������������� ���� �����
	}

	virtual void simulate(float dt)  // �������� ��� ������ �����
	{
		for (unsigned a = 0; a < numOfMasses; ++a)
			masses[a]->simulate(dt);
	}

	virtual void operate(float dt) // ������ ��������� ���������.
	{
		init();            // 1. ���� � 0
		solve();           // 2. ��������� ����
		simulate(dt);      // 3. ��������
	}

	virtual void draw(const Render& r)
	{
		for (unsigned a = 0; a < numOfMasses; ++a)
		{
			r.drawSphere(masses[a]->pos, masses[a]->r, masses[a]->color);
		}
	}
};
