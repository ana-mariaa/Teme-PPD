#include <iostream>
#include <omp.h>
#include <time.h>

float get_random_number(float a, float b);
float monte_carlo(int numar_total_puncte, float a, float b);
float impartire_manuala_monte_carlo(int numar_total_puncte, float a, float b);
float reductie_paralela_monte_carlo(int numar_total_puncte, float a, float b);

int main()
{
	int numar_total_puncte = 1000000;

	float a = -1.0;
	float b = 1.0;

	//------------------------------- PI Monte Carlo - Clasic ---------------------------------------------//
	clock_t startTime_monteCarlo = clock();

	float pi_monte_carlo = monte_carlo(numar_total_puncte, a, b);
	std::cout << "PI Monte Carlo = " << pi_monte_carlo << std::endl;

	clock_t stop_monteCarlo = clock();
	//------------------------------- PI Monte Carlo - Clasic ---------------------------------------------//


	//------------------------------- PI Monte Carlo - Impartire Manuala ---------------------------------------------//
	clock_t startTime_monteCarlo_impartireManuala = clock();

	float pi_monte_carlo_impartireManuala = impartire_manuala_monte_carlo(numar_total_puncte, a, b);
	std::cout << "PI Monte Carlo - Impartire Manuala = " << pi_monte_carlo << std::endl;

	clock_t stop_monteCarlo_impartireManuala = clock();// -startTime_monteCarlo_impartireManuala;
	//------------------------------- PI Monte Carlo - Impartire Manuala ---------------------------------------------//


	//------------------------------- PI Monte Carlo - Reductie Paralela ---------------------------------------------//
	clock_t startTime_monteCarlo_reductieParalela = clock();

	float pi_monte_carlo_reductieParalela = reductie_paralela_monte_carlo(numar_total_puncte, a, b);
	std::cout << "PI Monte Carlo - Reductie Paralela = " << pi_monte_carlo << std::endl;

	clock_t stop_monteCarlo_reductieParalela = clock();// -startTime_monteCarlo_reductieParalela;
	//------------------------------- PI Monte Carlo - Reductie Paralela ---------------------------------------------//

	//Afisarea timpului
	std::cout << std::endl;
	std::cout << "Timpul - monte carlo: " << double(stop_monteCarlo - startTime_monteCarlo) / CLOCKS_PER_SEC << std::endl;
	std::cout << "Timpul - Impartire Manuala: " << double(stop_monteCarlo_impartireManuala - startTime_monteCarlo_impartireManuala) / CLOCKS_PER_SEC << std::endl;
	std::cout << "Timpul - Reductie Paralela: " << double(stop_monteCarlo_reductieParalela - startTime_monteCarlo_reductieParalela) / CLOCKS_PER_SEC << std::endl;

	return 0;
}

float get_random_number(float a, float b)
{
	float c = (float)rand() / (float)RAND_MAX;
	float diff = b - a;
	float random = diff * c;

	return a + random;
}

float monte_carlo(int numar_total_puncte, float a, float b)
{
	int nr_pct_cerc = 0;

	float centru_x = 0.0;
	float centru_y = 0.0;
	float raza = 1.0;

	for (int i = 0; i < numar_total_puncte; ++i)
	{
		float pct_x = get_random_number(a, b);
		float pct_y = get_random_number(a, b);

		float distanta = sqrt((pct_x - centru_x) * (pct_x - centru_x) + (pct_y - centru_y) * (pct_y - centru_y));
		if (distanta < raza)
		{
			nr_pct_cerc += 1;
		}
	}
	
	return 4 * (nr_pct_cerc / (float)numar_total_puncte);
}

float impartire_manuala_monte_carlo(int numar_total_puncte, float a, float b)
{
	int nr_pct_cerc = 0;

	float centru_x = 0.0;
	float centru_y = 0.0;
	float raza = 1.0;

#pragma omp parallel
	{
		int de_la = omp_get_thread_num() * numar_total_puncte / omp_get_num_threads();
		int pana_la = (omp_get_thread_num() + 1) * numar_total_puncte / omp_get_num_threads();
		
		for (int i = de_la; i < pana_la; ++i)
		{
			float pct_x = get_random_number(a, b);
			float pct_y = get_random_number(a, b);

			float distanta = sqrt((pct_x - centru_x) * (pct_x - centru_x) + (pct_y - centru_y) * (pct_y - centru_y));
			if (distanta < raza)
			{
#pragma omp atomic
				nr_pct_cerc += 1;
			}
		}
	}

	return 4 * (nr_pct_cerc / (float)numar_total_puncte);
}

float reductie_paralela_monte_carlo(int numar_total_puncte, float a, float b)
{
	int nr_pct_cerc = 0;

	float centru_x = 0.0;
	float centru_y = 0.0;
	float raza = 1.0;

#pragma omp parallel reduction(+:nr_pct_cerc)
	for (int i = 0; i < numar_total_puncte; ++i)
	{
		float pct_x = get_random_number(a, b);
		float pct_y = get_random_number(a, b);

		float distanta = sqrt((pct_x - centru_x) * (pct_x - centru_x) + (pct_y - centru_y) * (pct_y - centru_y));
		if (distanta < raza)
		{
			nr_pct_cerc += 1;
		}
	}

	return 4 * (nr_pct_cerc / (float)numar_total_puncte);
}