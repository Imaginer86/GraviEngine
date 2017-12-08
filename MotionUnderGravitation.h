#pragma once
#include "Simulation.h"

class MotionUnderGravitation : public Simulation
{
public:
	Vector3f gravitation;    // ускорение свободного падени€

							 //  онструктор сначала создает предка с 1й массой в 1 кг.
							 // Vector3D Gravitation - ускорение свободного падени€

	MotionUnderGravitation(Vector3f _gravitation)
	:Simulation(1)
	,gravitation(_gravitation)
	{

		//masses[0]->pos = Vector3f(-10.0f, 0.0f, 0.0f);
		//masses[0]->vel = Vector3f(1.0f, 5.0f, -5.0f);
	}
	// ѕоскольку мы примен€ем силу, нам понадобитс€ метод "Solve".
	virtual void solve()
	{
		// ѕримен€ем силу ко всем массам
		for (int a = 0; a < numOfMasses; ++a)
			// —ила гравитации это F = m * g.
			masses[a]->applyForce(gravitation * masses[a]->m);
	}
};
