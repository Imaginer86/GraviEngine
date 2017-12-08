#pragma once
#include "Simulation.h"

class MassConnectedWithSpring : public Simulation
{
public:
	float springConstant;    // больше springConstant, сильнее сила
							 // притяжения.
	Vector3f connectionPos;  // Точка

							 // Конструктор сначала создает предка с 1й массой в 1 кг.
	MassConnectedWithSpring(float _springConstant)
	:Simulation(1)
	,springConstant(_springConstant)// установили springConstant
	,connectionPos(0.0f, 0.0f, 0.0f)// и connectionPos.
	{
		// положение массы относительно connectionPos.
		//masses[0]->pos = connectionPos + Vector3f(5.0f, 0.0f, 0.0f);
		// Скорость 0
		//masses[0]->vel = Vector3f(0.0f, 1.0f, 0.0f);
	}
	virtual void solve() // Будет применяться сила пружины
	{
		for (int a = 0; a < numOfMasses; ++a)
		{
			// Находим вектор от массы до точки притяжения
			Vector3f springVector = masses[a]->pos - connectionPos;
			// Применяем силу опираясь на формулу
			masses[a]->applyForce(-springVector * springConstant);
		}
	}

};
