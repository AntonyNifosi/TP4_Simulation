/**
 * @file tp4.cpp
 * @author Antony Nifosi
 * @brief Simulateur de génération de population de lapins
 * @version 1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */


#include "Population.hpp"
#include <fstream>
#include <iostream>
#include <string>


/**
 * @brief Tableau des quantiles
 */
const double t_values[] =
{
    12.706, 4.303, 3.182, 2.776, 2.571, 2.447, 2.365, 2.308, 2.262, 2.228,
    2.201, 2.179, 2.160, 2.145, 2.131, 2.120, 2.110, 2.101, 2.093, 2.086,
    2.080, 2.074, 2.069, 2.064, 2.060, 2.056, 2.052, 2.048, 2.045, 2.042,
    2.021, 2.000, 1.980, 1.960
};


double quantil(int ind);
double variance (std::vector<Population>& value, int nb, double average);
void conf_interval(int n, double mean, double v, double * borne_inf, double * borne_sup);

int main()
{
	std::string answer;
	std::vector<Population> simulations;
	int nb_simu, nb_male, nb_femelle, time_simu;
	double average = 0;
	auto start = std::chrono::high_resolution_clock::now();

	std::cout << "Simulateur de population de lapins :" << std::endl;
	std::cout << "Souhaitez vous faire plusieurs simulations et obtenir une moyenne (YES) ou simplement une seule detaillee (NO) ? Y / N" << std::endl;
	std::cin >> answer;

	/* On choisit de faire plusieurs simulations */
	if (answer == "Y")
	{
		std::cout << "Rentrer le nombre de simulations a faire, le nombre de femelle, de male et la duree de la simulation (en mois) svp : ";
		std::cin >> nb_simu >> nb_femelle >> nb_male >> time_simu;

		for (int i = 0; i < nb_simu; i++)
		{
			simulations.push_back(Population(nb_femelle, nb_male));
			simulations[i].update(time_simu);
			average += simulations[i].getPopulation();
			std::cout << "Population de la simulation " << i + 1 << " : " << simulations[i].getPopulation() << std::endl;
		}


		average = average / nb_simu;
		double borne_inf, borne_sup;
		double v = variance(simulations, nb_simu, average);
		conf_interval(nb_simu, average, v, &borne_inf, &borne_sup);

		std::cout << "Moyenne des simulation --> Population moyenne : " << average << " / Ecart type : " << sqrt(v) << std::endl;
		std::cout << "Interval de confiance à 95% : [" << borne_inf << " ; " << borne_sup << "]" << std::endl;
 	}
	/* Une seule simulation detaillee */  
	else
	{
		std::cout << "Rentrer le nombre femelle, de male et la duree de la simulation (en mois) svp : ";
		std::cin >> nb_femelle >> nb_male >> time_simu;
		Population p1(nb_femelle, nb_male);
		p1.update(time_simu);
		p1.print_data();
	}
		
	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Temps ecoule : " << elapsed.count() << "s" << std::endl;

	return 0;
}

/**
 * @brief Fonction qui permet d'obtenir les quantils à partir du tableau t_values
 * 
 * @param[in] ind indice du quantil voulu ([1, 30], 40, 80, 120, inf)
 * @return double quantil correspondant
 */
double quantil(int ind)
{
    int result = 0;

    if (ind <= 30)
        result = ind - 1;

    else if (ind == 40)
        result = 30;

    else if (ind == 80)
        result = 31;

    else if (ind == 120)
        result = 32;
    else
        result = 33;
    
    return t_values[result];
}


/**
 * @brief Fonction calculant une estimation sans biais de la variance d'un tableau (en l'occurence de PI)
 * 
 * @param[in] value vecteur des populations
 * @param[in] nb nombre de simulations
 * @param[in] average moyenne des approximations
 * @return double variance des approximations
 */
double variance (std::vector<Population>& value, int nb, double average)
{
    int i;
    double var = 0;
	
	/* Calcul de la variance */
    for (i = 0; i < nb; i++)
    {
        var += (value[i].getPopulation() - average) * (value[i].getPopulation() - average);
    }

    return (var / (double)(nb - 1));
}


/**
 * @brief Fonction qui calcule les intervalles de confiances à 95%
 * 
 * @param[in] n nombre d'occurences
 * @param[in] mean moyenne
 * @param[in] v variance
 * @param[out] borne_inf borne inferieure de l'intervalle de confiance
 * @param[out] borne_sup borne supérieur de l'intervalle de confiance
 */
void conf_interval(int n, double mean, double v, double * borne_inf, double * borne_sup)
{
    *borne_inf = mean - quantil(n) * sqrt(v / n);
    *borne_sup = mean + quantil(n) * sqrt(v / n);
}