#pragma once
#include "Entity.h"
#include "Render.h"

class Simulation
{
public:
	unsigned numOfMasses;    // Количество масс в контейнере.
	Entity** masses;         // Массы хранятся в 1d массиве указателей

	Simulation(int _numOfMasses)
	{
		numOfMasses = _numOfMasses;
		masses = new Entity*[numOfMasses]; // Создаем массив указателей.

										 // Создаем Mass и заносим его в массив
		for (unsigned a = 0; a < numOfMasses; ++a)
			masses[a] = new Entity;
	}

	virtual ~Simulation()      // Чистим массив масс
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
		// Если индекс выходит за рамки массива возвращаем null
		if (index < 0 || index >= numOfMasses) return NULL;

		// Возвращаем массу по индексу
		return masses[index];
	}

	virtual void init()      // вызываем init() для каждой массы
	{
		for (unsigned a = 0; a < numOfMasses; ++a)
			masses[a]->init();
	}

	virtual void solve()
	{
		// Нет кода т.к. в базовом классе у нас нет сил
		// В других контейнерах мы переопределим этот метод
	}

	virtual void simulate(float dt)  // Итерация для каждой массы
	{
		for (unsigned a = 0; a < numOfMasses; ++a)
			masses[a]->simulate(dt);
	}

	virtual void operate(float dt) // Полная процедура симуляции.
	{
		init();            // 1. Силу в 0
		solve();           // 2. Применяем силы
		simulate(dt);      // 3. Итерация
	}

	virtual void draw(const Render& r)
	{
		for (unsigned a = 0; a < numOfMasses; ++a)
		{
			r.drawSphere(masses[a]->pos, masses[a]->r, masses[a]->color);
		}
	}
};
