#include "Rabbit.hpp"

/**
* @class Population
* @brief Classe représentant la population de lapins
*
*  La classe gère la gestion d'une population de lapin et l'export des statistiques
*/
class Population
{
	private:
		std::list<Rabbit*> population;
        std::vector<int> nb_rabbit;
        std::vector<int> nb_birth;
        std::vector<int> nb_death;
		int death_count;
		std::ofstream file;

	public:
		Population(int femelle, int male);
		void update(int time);
        void print_data();
		void write_data(int pop, int birth, int death);
		int getPopulation();
};