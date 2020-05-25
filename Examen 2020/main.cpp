#include <iostream>
#include <omp.h>

/* --------------------------------------------------------------------
Implementați un program ce calculează produsul scalar a 2 vectori
cu N elemente iar apoi paralelizați programul utilizand OpenMP
Urmati, pe rand, pasii de mai jos.
Indicatie: produsul scalar a 2 vectori este formulat astfel:
c = a_1*b_1 + a_2*b_2 + ... + a_n*b_n,
Unde a_i, b_i reprezinta componenta i a vectorului a respectiv b.
--------------------------------------------------------------------*/

int main()
{
	// Numarul N de elemente
	int N = 1000;
	// Primul vector
	float *a;
	// Al 2-lea vector
	float *b;
	// rezultatul
	float c;
	/* --------------------------------------------------------------------
	1. Alocati memorie pe host pentru cei doi vectori:
	--------------------------------------------------------------------*/
	/* ------------------------ REZOLVARE PCT 1 -----------------------------*/
	/* ------------------------ CODUL TAU DE AICI ---------------------------*/
	a = new float[N];
	b = new float[N];
	/* ------------------------ CODUL TAU PANA AICI ---------------------------*/
	/* --------------------------------------------------------------------
	2. Initializați vectorii a si b dupa cum urmeaza:
	* primul vector are elementele de la pozitie para 0 iar cele de la pozitie impara 1
	* al 2-lea vector are elementele de la pozitie para 1 iar cele de la pozitie impara 0
	--------------------------------------------------------------------*/
	/* ------------------------ REZOLVARE PCT 2 -----------------------------*/
	/* ------------------------ CODUL TAU DE AICI ---------------------------*/
	c = 0;

	for (int i = 0; i < N; ++i)
	{
		if (i % 2 == 0)
		{
			a[i] = 0;
			b[i] = 1;
		}
		else
		{
			a[i] = 1;
			b[i] = 0;
		}
	}

	/* ------------------------ CODUL TAU PANA AICI ---------------------------*/
	/* --------------------------------------------------------------------
	3. Implementați operatia de produs scalar si scrieti rezultatul in variabila c
	--------------------------------------------------------------------*/
	/* ------------------------ REZOLVARE PCT 3 -----------------------------*/
	/* ------------------------ CODUL TAU DE AICI ---------------------------*/
	for (int i = 0; i < N; ++i)
	{
		c += a[i] * b[i];
	}

	/* ------------------------ CODUL TAU PANA AICI ---------------------------*/
	/* --------------------------------------------------------------------
	4. Implementați varianta paralela a calculului de la cerinta precedenta
	--------------------------------------------------------------------* /
	/* ------------------------ REZOLVARE PCT 4 -----------------------------*/
	/* ------------------------ CODUL TAU DE AICI ---------------------------*/
	c = 0;
#pragma omp parallel for
	for (int i = 0; i < N; ++i)
	{
		c += a[i] * b[i];
	}
	/* ------------------------ CODUL TAU PANA AICI ---------------------------*/
}