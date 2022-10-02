#include <iostream>
#include <stdio.h>
#include <math.h>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

const int N =400;
const int l_watkow =2;

unsigned char tab[N][N][3];

int ulam_get_map(int x, int y, int n)
{
    x -= (n - 1) / 2;
    y -= n / 2;

    int mx = abs(x), my = abs(y);
    int l = 2 * max(mx, my);
    int d = y >= x ? l * 3 + x + y : l - x - y;

    return pow(l - 1, 2) + d;
}

int isprime(int n)
{
    for (int p = 2; p * p <= n; p++)
        if (n % p == 0) return 0;
    return n > 2;
}
void ulams(int watek)
{
    int iX, iY;
    int min = watek * (N / l_watkow);
    int max = (watek + 1) * (N / l_watkow);
    

        for (int i = min; i < max; i++)
            for (int j = 0; j <  N; j++)
                if (isprime(ulam_get_map(i, j, N)))
                    for (int k = 0; k < 3; k++) tab[i][j][k] = 0;
                else
                    for (int k = 0; k < 3; k++) tab[i][j][k] = 255;
    
}

int main()
{
   	int i, j;
   vector<thread> v;
   auto start = std::chrono::high_resolution_clock::now();

   for (int i = 0; i < l_watkow; i++)
   {
       int x = 2 * N * (i % 2) / l_watkow;
       int y = 2 * N * int(i / 2) / l_watkow;
       
       v.push_back(thread(ulams,i));
   }

    for (int i = 0; i < l_watkow; i++) v[i].join();
    auto finish = std::chrono::high_resolution_clock::now();
    duration<double> elapsed = finish - start;
    cout << "Elapsed time: " << elapsed.count() << " s\n";
    FILE* fp = fopen("ulamspi.ppm", "wb");
    fprintf(fp, "P6\n %s\n %d\n %d\n %d\n", "# ", N, N, 255);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        fwrite(tab[i][j], 1, 3, fp);
    fclose(fp);

    return 0;
}
