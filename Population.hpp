#include "Rabbit.hpp"

class Population
{
	private:
		std::list<Rabbit*> population;
        std::vector<int> nb_rabbit;
        std::vector<int> nb_birth;
        std::vector<int> nb_death;
		int mort_count;

	public:
		Population(int femelle, int male);
		void update(int time);
        void print_data();
};