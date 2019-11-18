#include "Population.hpp"

int main()
{
	int nb_male, nb_femelle, time_simu;
	auto start = std::chrono::high_resolution_clock::now();

	std::cout << "Simulateur de population de lapins :" << std::endl;
	std::cout << "Rentrer le nombre femelle, de male et la duree de la simulation (en mois) svp : ";
	std::cin >> nb_femelle >> nb_male >> time_simu;

	Population p1(nb_femelle, nb_male);

	p1.update(time_simu);
	p1.print_data();
	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Temps ecoule : " << elapsed.count() << "s" << std::endl;

	return 0;
}