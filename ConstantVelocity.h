#pragma once
#include "Simulation.h"
#include "Constans.h"

class ConstantVelocity : public Simulation
{
	Vector3f gravitation;
public:

	// Конструктор сначала создает предка с 1й массой в 1 кг.
	ConstantVelocity(int numOfMasses, const Vector3f& gravitation_ = Vector3f(0.0f, 0.0f, 0.0f)) : Simulation(numOfMasses), gravitation(gravitation_)
	{
	}

	virtual void simulate(float dt);  // Итерация для каждой массы
	virtual void solve();

};

inline void ConstantVelocity::solve()
{
	// Применяем силу ко всем массам
	//for (unsigned a = 0; a < numOfMasses; ++a)
		// Сила гравитации это F = m * g.
		//masses[a]->applyForce(gravitation * masses[a]->m);

	for (unsigned a = 0; a < numOfMasses; ++a)
		for (unsigned b = a + 1; b < numOfMasses; ++b)
		{
			Entity *massa = getMass(a);
			Entity *massb = getMass(b);
			Vector3f rvector = massa->pos - massb->pos;
			float dist = rvector.unitize();
			float gforce = G * massa->m * massb->m / dist;

			massa->applyForce(rvector*gforce);
			massb->applyForce(rvector*gforce);
		}

}

inline void ConstantVelocity::simulate(float dt)
{
	Simulation::simulate(dt);
	return;

	/*
	for (unsigned a = 0; a < numOfMasses; ++a)
		for (unsigned b = a + 1; b < numOfMasses; ++b)
		{
			Entity *massa = getMass(a);
			Entity *massb = getMass(b);
			float dist = (massa->pos - massb->pos).length();
			float rdist = 2.0f;
			if (dist < rdist)
			{
				float v = (massa->vel - massb->vel).length();
				float dc = (rdist - dist) / v;

				massa->simulate(-dc);
				massb->simulate(-dc);

				Vector3f pa = massa->pos;
				Vector3f va = massa->vel;
				Vector3f pb = massb->pos;
				Vector3f vb = massb->vel;

				float ma = massa->m;
				float mb = massb->m;

				Vector3f po = (pb + pa) / 2.0f;

				Vector3f p = pb - pa;
				p.unitize();
				Vector3f ta = p * va.dotProduct(p);
				Vector3f tb = -p * vb.dotProduct(-p);

				float d = -p.x*po.x - p.y*po.y - p.z*po.z;

				Vector3f pva = pa + va;
				float ka = -p.dotProduct(pva) - d;
				Vector3f pna = pva + p*ka;
				Vector3f na = pna - po;

				Vector3f pvb = pb + vb;
				float kb = -p.dotProduct(pvb) - d;
				Vector3f pnb = pvb + p*kb;
				Vector3f nb = pnb - po;

				float vtla = ta.length();
				float vtlb = -tb.length();
				float tfa = (-vtla + (vtla*ma + vtlb*mb) * 2.0f / (ma + mb));
				float tfb = (-vtlb + (vtla*ma + vtlb*mb) * 2.0f / (ma + mb));

				Vector3f vaa = p * tfa + na;
				Vector3f vbb = p * tfb + nb;

				massa->vel = vaa;
				massb->vel = vbb;

				massa->simulate(dc);
				massb->simulate(dc);
			}
		}
		*/
	//Simulation::simulate(dt);
}