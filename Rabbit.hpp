#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include <list>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <cstdio>
#include <thread>
#include <math.h>

/**
* @class Rabbit
* @brief Classe représentant les lapins en génral (mâle + femelle)
*
*  La classe gère la gestion d'un lapin, son update, anniversaire et mort
*/
class Rabbit
{
	protected:
		bool adult;
		int age;
		float survival;
		int maturity;
		float proba_death;

	public:
		Rabbit();
		virtual ~Rabbit();
		virtual bool update();
		virtual void anniversary();
		bool hasToDie();
};

/**
* @class Female
* @brief Classe représentant les lapines
*
*  La classe gère les actions spécifiques aux femelles lors de l'update et de l'anniversaire
*/
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