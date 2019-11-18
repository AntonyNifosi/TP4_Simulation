#include "Population.hpp"

std::mt19937 generator2(888888);
std::uniform_int_distribution<int> naissance(3, 6);
std::uniform_int_distribution<int> sexe(0, 1);


Population::Population(int femelle, int male) : mort_count(0)
{
	/* Initialisation de la population avec des males et des femmelles */
	for (int j = 0; j < femelle; j++)
	{
		population.push_back(new Female());
	}
	for (int j = 0; j < male; j++)
	{
		population.push_back(new Rabbit());
	}
}

void Population::update(int time)
{
    int death_tmp = 0;
    int birth_tmp = 0;

	std::cout << "Update de la population :" << std::endl;
    
	for (int j = 0; j < time; j++)
	{
		for (auto i = population.begin(); i != population.end(); i++)
		{
            /* Si le lapin doit mourrir */
            if ((*i)->hasToDie())
            {	
                delete *i;
                *i = nullptr;
                death_tmp++;
                mort_count++;
            }
            /* Sinon on fait son update */
            else
            {
                if ((*i)->update())
                {
                    int nb_baby = naissance(generator2);
                    for (int k = 0; k < nb_baby; k++)
                    {
                        birth_tmp++;
                        if (sexe(generator2))
                        {
                            population.push_back(new Female());
                        }
                        else
                        {
                            population.push_back(new Rabbit());
                        }
                    }
                }
            }
		}
        population.remove(nullptr);

        if (j % 12 == 0)
        {
            nb_rabbit.push_back(population.size());
            nb_birth.push_back(birth_tmp);
            nb_death.push_back(death_tmp);
            birth_tmp = 0;
            death_tmp = 0;
        }
	}
	std::cout << "Taille de la population finales a lanne " << time / 12 << " : " << population.size() << " / Nombre de lapins mort : "<< mort_count << std::endl;
}

void Population::print_data()
{
    for (int i = 0; i < nb_rabbit.size(); i++)
    {
        std::cout << "Nombre de lapins a l'annee " << i << " : " << nb_rabbit[i] << " --> Naissances : " << nb_birth[i] << " --> Mort : " << nb_death[i] << std::endl;
    }
}