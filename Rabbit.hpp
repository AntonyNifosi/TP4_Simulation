#include <iostream>
#include <random>
#include <vector>
#include <list>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <cstdio>
#include <thread>
#include <math.h>

class Rabbit
{
	protected:
		int adult;
		int age;
		float survival;
		int maturity;
		int death_month;
		float proba_death;

	public:
		Rabbit();
		virtual bool update();
		virtual void anniversary();
		bool hasToDie();
};

class Female : public Rabbit
{
	private:
		int porte;
		std::vector<int> mois;

	public:
		Female();
		void anniversary();
		bool update();
};