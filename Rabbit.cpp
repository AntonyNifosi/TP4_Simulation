#include "Rabbit.hpp"

using namespace std::chrono;

/* Declaration des generateurs de nombres aleatoires */
std::mt19937 generator(888888);
std::normal_distribution<> distribution(6, 1);
std::uniform_int_distribution<int> repartition(1, 12);
std::uniform_real_distribution<float> survivalite(0, 100);


Rabbit::Rabbit() : adult(0), age(-1), survival(20), maturity(distribution(generator))
{
	proba_death = (float)pow((float)survival / 100, (float)1 / maturity) * 100;
}

bool Rabbit::update()
{
	age++;
	/* Update maturity */
	if (!adult && age >= maturity)
	{
		adult = 1;
		survival = 50;
        proba_death = (float)pow((float)survival / 100, (float)1 / 12) * 100;
	}

	/* Update anniversaire (porté + survavibilité) */
	else if (age % 12 == 0)
	{
		anniversary();
		if (age >= 11 * 12)
        {
            survival -= 10;
            proba_death = (float)pow((float)survival / 100, (float)1 / 12) * 100;
        }
			
	}
	return 0;
}

void Rabbit::anniversary()
{

}

bool Rabbit::hasToDie()
{
	bool die = false;
	float mort = survivalite(generator);

    if (mort >= proba_death)
    {
        die = true;
    }       
    /* Update de l'age */
    if (age >= 15 * 12)
    {
        die = true;
    }
	return die;
}

Female::Female() : porte(distribution(generator))
{

}

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

		if (p != mois.end())
		{

		}
		else
		{
			mois.push_back(mois_tmp);
			i++;
		}
	}
}

bool Female::update()
{
	bool naissance = false;
	naissance = Rabbit::update();
	if (adult)
	{
		/* A ameliorer avec un while */
		for (int i = 0; i < mois.size(); i++)
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