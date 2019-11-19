/**
 * @file Population.cpp
 * @author Antony Nifosi
 * @brief Procédures et fonctions relatives à la classe Population
 * @version 1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */


#include "Population.hpp"

/**
 * @brief Générateur Mersenne Twister
 */
std::mt19937 generator2(8);
std::uniform_int_distribution<int> naissance(3, 6);
std::uniform_int_distribution<int> sexe(0, 1);


/**
 * @brief Constructeur de la classe Population qui permet d'initialiser une population avec les valeurs passées en paramètres
 * 
 * @param[in] femelle nombre de femelles à générer dans la population
 * @param[in] male nombre de mâles à générer dans la population
 */
Population::Population(int femelle, int male) : death_count(0)
{
    /* Creation du fichier de donnees pour l'histogramme */
    file.open("result.txt");

	/* Initialisation de la population avec des males et des femmelles */
	for (int j = 0; j < femelle; j++)
	{
		population.push_back(new Female());
	}
	for (int j = 0; j < male; j++)
	{
		population.push_back(new Rabbit());
	}
    write_data(femelle + male, 0 , 0);
}

/**
 * @brief Procédure permettant l'update d'une population, update de chaque lapins, génération de potées etc ...
 * 
 * @param[in] time temps en mois que la simulation va durer
 */
void Population::update(int time)
{
    int death_tmp = 0;
    int birth_tmp = 0;

    if (file)
    {
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
                    death_count++;
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

            /* On recupere les donnees */
            nb_rabbit.push_back(population.size());
            nb_birth.push_back(birth_tmp);
            nb_death.push_back(death_tmp);
            write_data(population.size(), birth_tmp, death_tmp);
            birth_tmp = 0;
            death_tmp = 0;
           
        }
        file.close();
    }
    else
    {
        std::cout << "Impossible d'ouvrir / creer le fichier de donnees !" << std::endl;
    }
	
}

/**
 * @brief Procédure permettant d'afficher les statistiques de la population mois par mois
 */
void Population::print_data()
{
    for (unsigned int i = 0; i < nb_rabbit.size(); i++)
    {
        std::cout << "Nombre de lapins au mois " << i << " : " << nb_rabbit[i] << " --> Naissances : " << nb_birth[i] << " --> Morts : " << nb_death[i] << std::endl;
    }
    std::cout << "Taille finale de la population : " << population.size() << " / Nombre de morts totales : " << death_count << std::endl;
}

/**
 * @brief Procédure qui écrit toutes les statistiques de la population dans un fichier .txt
 * 
 * @param[in] pop nombre de lapins de la population au mois courant
 * @param[in] birth nombre de naissances de la population au mois courant
 * @param[in] death nombre de morts de la population au mois courant
 */
void Population::write_data(int pop, int birth, int death)
{
    file << pop << ";" << birth << ";" << death << "\n";
}

/**
 * @brief Constructeur de la classe Population qui permet d'initialiser une population avec les valeurs passées en paramètres
 * 
 * @return int Retourne la taille de la population actuelle
 */
int Population::getPopulation()
{
    return population.size();
}