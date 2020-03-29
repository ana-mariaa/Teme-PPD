#include <iostream>
#include <omp.h>
#include <time.h>

void calculHistograma_Clasic(int imgSize, unsigned char *img, int *hist);
void afisareHistograma(int *hist);
void calculHistograma_Paralel(int imgSize, int *hist, unsigned char *img, int *hist_thread, short nr_threads);

void main()
{
	//Alocarea de memorie pentru imagine
	int imgSize = 10000;
	unsigned char *img = new unsigned char[imgSize*imgSize];

	//Alocarea de memorie pentru histograma
	int *hist = new int[256];

	//Initializarea imaginii
	for (int i = 0; i < imgSize; ++i)
		for (int j = 0; j < imgSize; ++j)
			img[i*imgSize + j] = i % 256;

	//Initializarea histogramei
	for (int i = 0; i < 256; ++i)
		hist[i] = 0;

	//Calculul histogramei - Clasic
	clock_t start = clock();
		calculHistograma_Clasic(imgSize, img, hist);
	clock_t stop = clock();

	//Afisarea histogramei
	afisareHistograma(hist);

	//------------------------------------------------------------------------- paralel ------------------------------------------//
	// Initializarea histogramei
	for (int i = 0; i < 256; ++i)
		hist[i] = 0;

	const short nr_threads = 8;
	omp_set_num_threads(nr_threads);

	int *hist_thread = new int[256 * nr_threads];

	// Initializarea histogramei paralele
	for (int i = 0; i < 256 * nr_threads; ++i)
		hist_thread[i] = 0;

	clock_t start_paralel = clock();
		calculHistograma_Paralel(imgSize, hist, img, hist_thread, nr_threads);
	clock_t stop_paralel = clock();

	//Afisarea histogramei
	afisareHistograma(hist);

	//Afisarea timpului de executie
	std::cout << "\n\nTime - Histograma Calculata Clasic: " << double(stop - start) / CLOCKS_PER_SEC << std::endl;
	std::cout << "\nTime - Histograma Calculata Paralel: " << double(stop_paralel - start_paralel) / CLOCKS_PER_SEC << std::endl;

	//Dealocare memorie
	delete[] img;
	delete[] hist;
	delete[] hist_thread;

	system("PAUSE");
}

void calculHistograma_Clasic(int imgSize, unsigned char *img, int *hist)
{
	//Calculul histogramei - Clasic
	for (int i = 0; i < imgSize; ++i)
		for (int j = 0; j < imgSize; ++j)
			hist[img[i*imgSize + j]]++;
}

void afisareHistograma(int *hist)
{
	//Afisarea histogramei
	for (int i = 0; i < 256; ++i)
		std::cout << hist[i] << " ";
	std::cout << std::endl;
}

void calculHistograma_Paralel(int imgSize, int *hist, unsigned char *img, int *hist_thread, short nr_threads)
{
	//calcul histograma - paralel
	int thread_curent = 0;

#pragma omp parallel private(thread_curent)
	{
		thread_curent = omp_get_thread_num();
	}
#pragma omp parallel for
	{
		for (int i = 0; i < imgSize; ++i)
		{
			for (int j = 0; j < imgSize; ++j)
			{
				hist_thread[thread_curent * 256 + img[i * imgSize + j]]++;
			} 
		}
	}

	//insumarea valorilor
	for (int i = 0; i < 256; ++i)
		for (int j = 0; j < nr_threads; ++j)
			hist[i] += hist_thread[j * 256 + i];
}