/**
 * @file Rabbit.cpp
 * @author Antony Nifosi
 * @brief Procédures et fonctions relatives aux classes Rabbit et Female
 * @version 1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */


#include "Rabbit.hpp"

using namespace std::chrono;

/**
 * @brief Générateur Mersenne Twister
 */
std::mt19937 generator(8);
std::normal_distribution<> distribution(6, 1);
std::uniform_int_distribution<int> repartition(1, 12);
std::uniform_real_distribution<float> survivalite(0, 100);


/**
 * @brief Constructeur de la classe Rabbit qui permet d'initialiser un lapin
 */
Rabbit::Rabbit() : adult(false), 
				   age(-1),
				   survival(20), 
				   maturity(distribution(generator)),
				   proba_death((float)pow((float)survival / 100, (float)1 / maturity) * 100)
{
}

/**
 * @brief Deconstructeur de la classe Rabbit
 */
Rabbit::~Rabbit()
{
}

/**
 * @brief Fonction qui update un lapin et le fait passer au mois suivant
 * 
 * @return bool Retourne 0 car ce retour n'a pas d'importance pour les Rabbit
 */
bool Rabbit::update()
{
	age++;
	/* Update maturity */
	if (!adult && age >= maturity)
	{
		adult = true;
		survival = 50;
        proba_death = (float)pow((float)survival / 100, (float)1 / (132 - maturity)) * 100;
	}

	/* Update anniversaire (porté + survavibilité) */
	else if (age % 12 == 0)
	{
		anniversary();
		if (age >= 11 * 12)
        {
            survival -= 10;
            proba_death = (float)pow((float)survival / 100, (float)1 / (132 - maturity)) * 100;
        }
			
	}
	return false;
}

void Rabbit::anniversary()
{

}

/**
 * @brief Fonction qui permet de savoir si un lapin doit mourir ou non
 * 
 * @return bool Renvoie true si le lapin doit mourir sinon false
 */
bool Rabbit::hasToDie()
{
	bool die = false;
	float mort = survivalite(generator);

    if (mort > proba_death)
    {
        die = true;
    }       
	return die;
}

/**
 * @brief Constructeur de la classe Female qui initialise le nombre de ses premières portées
 */
Female::Female() : porte(distribution(generator))
{

}

/**
 * @brief Procédure permettant de générer le nombre de portées ainsi que le planning des portées pour l'année suivante
 */
void Female::anniversary()
{

	int i = 0;
	int mois_tmp;
	
	porte = distribution(generator);
	mois.clear();

	while (i < porte)
	{
		mois_tmp = repartition(generator);

		std::vector<int>::iterator p;
		p = std::find(mois.begin(), mois.end(), mois_tmp);

		if (p == mois.end())
		{
			mois.push_back(mois_tmp);
			i++;
		}
	}    
}

/**
 * @brief Fonction qui nous dit si la femelle doit donner naissance pour le mois courant
 * 
 * @return bool Renvoie true si la femelle doit donner naissance false sinon
 */
bool Female::update()
{
	bool naissance = false;
	naissance = Rabbit::update();
	if (adult)
	{
		for (unsigned int i = 0; i < mois.size(); i++)
		{
			if (age % 12 == mois[i])
			{
				naissance = true;
				mois.erase(mois.begin() + i);
			}
		}
	}
	return naissance;
}