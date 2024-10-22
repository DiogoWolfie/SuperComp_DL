#include <omp.h>
#include <iostream>
#include <iomanip>
static long num_steps = 1024l;

#define MIN_BLK  1024*1024*256




double pi_r(long Nstart, long Nfinish, double step) {
    double x =0;
    double y =0;
    double sum =0;
    long i,iblk;
    if (Nfinish-Nstart < MIN_BLK){
        for (i = Nstart; i < Nfinish; i++){
            double x = (i+0.5)*step;
            sum += 4.0/(1.0+x*x); 
        }
        return sum;
        
        
    } else {
        iblk = Nfinish-Nstart;
        #pragma omp task shared(x)
        x = pi_r(Nstart,Nfinish-iblk/2,step);
        #pragma omp task shared(y)
        y = pi_r(Nfinish-iblk/2, Nfinish, step);
        #pragma omp taskwait
        return x+y;
    }
    
    
}

int main () {
    long i;
    double step, pi,a;
    double init_time, final_time;
    step = 1.0/(double) num_steps;
    init_time = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        a = pi_r(0, num_steps, step);

    }
    
    pi = step * a;
    final_time = omp_get_wtime() - init_time;

    std::cout << "for " << num_steps << " steps pi = " << std::setprecision(15) << pi << " in " << final_time << " secs\n";
}