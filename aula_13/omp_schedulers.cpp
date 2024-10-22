#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <omp.h>
void print_iterations(const std::string& description,
const std::vector< std::vector<int> >& vectors,
const int n)
{
    std::vector< std::string > strings(4, std::string());
for (int i = 0; i != n; i++)
    {
for (int j = 0; j != 4; j++)
        {
const auto& vector = vectors[j];
auto it = std::find(vector.begin(), vector.end(), i);
if (it != vector.end())
            {
                strings[j] += "*";
            }
else 
            { 
                strings[j] += " ";
            }
        }
    }
    std::cout << description << std::endl;
for (auto& s : strings)
    {
        std::cout << s << "\n";
    }
    std::cout << std::endl;
}
template <typename T>
void schedule(T function, 
const std::string& description, 
const int n)
{
    std::vector< std::vector<int> > vectors(4, std::vector<int>());
function(vectors, n);
print_iterations(description, vectors, n);
}
void scheduleDefault(std::vector< std::vector<int> >& vectors,
int n)
{
#pragma omp parallel num_threads(4), shared(vectors, n)
    {    
#pragma omp for 
for (int i = 0; i < n; i++)
        {
            vectors[omp_get_thread_num()].push_back(i);
        }
    }
}
void scheduleStatic(std::vector< std::vector<int> >& vectors,
int n)
{
#pragma omp parallel num_threads(4), shared(vectors, n)
    {    
        #pragma omp for schedule(static)
for (int i = 0; i < n; i++)
        {
            vectors[omp_get_thread_num()].push_back(i);
        }
    }
}
void scheduleStatic4(std::vector< std::vector<int> >& vectors,
int n)
{
#pragma omp parallel num_threads(4), shared(vectors, n)
    {    
#pragma omp for schedule(static, 4)
for (int i = 0; i < n; i++)
        {
            vectors[omp_get_thread_num()].push_back(i);
        }
    }
}
void scheduleStatic8(std::vector< std::vector<int> >& vectors,
int n)
{
#pragma omp parallel num_threads(4), shared(vectors, n)
    {    
#pragma omp for schedule(static, 8)
for (int i = 0; i < n; i++)
        {
            vectors[omp_get_thread_num()].push_back(i);
        }
    }
}
void scheduleDynamic(std::vector< std::vector<int> >& vectors,
int n)
{
#pragma omp parallel num_threads(4), shared(vectors, n)
    {    
#pragma omp for schedule(dynamic)
for (int i = 0; i < n; i++)
        {
            vectors[omp_get_thread_num()].push_back(i);
        }
    }
}
void scheduleDynamic1(std::vector< std::vector<int> >& vectors,
int n)
{
#pragma omp parallel num_threads(4), shared(vectors, n)
    {    
#pragma omp for schedule(dynamic, 1)
for (int i = 0; i < n; i++)
        {
            vectors[omp_get_thread_num()].push_back(i);
        }
    }
}
void scheduleDynamic4(std::vector< std::vector<int> >& vectors,
int n)
{
#pragma omp parallel num_threads(4), shared(vectors, n)
    {    
#pragma omp for schedule(dynamic, 4)
for (int i = 0; i < n; i++)
        {
            vectors[omp_get_thread_num()].push_back(i);
        }
    }
}
void scheduleDynamic8(std::vector< std::vector<int> >& vectors,
int n)
{
#pragma omp parallel num_threads(4), shared(vectors, n)
    {    
#pragma omp for schedule(dynamic, 8)
for (int i = 0; i < n; i++)
        {
            vectors[omp_get_thread_num()].push_back(i);
        }
    }
}
void scheduleGuided(std::vector< std::vector<int> >& vectors,
int n)
{
#pragma omp parallel num_threads(4), shared(vectors, n)
    {    
#pragma omp for schedule(guided)
for (int i = 0; i < n; i++)
        {
            vectors[omp_get_thread_num()].push_back(i);
        }
    }
}
void scheduleGuided2(std::vector< std::vector<int> >& vectors,
int n)
{
#pragma omp parallel num_threads(4), shared(vectors, n)
    {    
#pragma omp for schedule(guided, 2)
for (int i = 0; i < n; i++)
        {
            vectors[omp_get_thread_num()].push_back(i);
        }
    }
}
void scheduleGuided4(std::vector< std::vector<int> >& vectors,
int n)
{
#pragma omp parallel num_threads(4), shared(vectors, n)
    {    
#pragma omp for schedule(guided, 4)
for (int i = 0; i < n; i++)
        {
            vectors[omp_get_thread_num()].push_back(i);
        }
    }
}
void scheduleGuided8(std::vector< std::vector<int> >& vectors,
int n)
{
#pragma omp parallel num_threads(4), shared(vectors, n)
    {    
#pragma omp for schedule(guided, 8)
for (int i = 0; i < n; i++)
        {
            vectors[omp_get_thread_num()].push_back(i);
        }
    }
}
void scheduleAuto(std::vector< std::vector<int> >& vectors,
int n)
{
#pragma omp parallel num_threads(4), shared(vectors, n)
    {    
#pragma omp for schedule(auto)
for (int i = 0; i < n; i++)
        {
            vectors[omp_get_thread_num()].push_back(i);
        }
    }
}
void scheduleRuntime(std::vector< std::vector<int> >& vectors,
int n)
{
#pragma omp parallel num_threads(4), shared(vectors, n)
    {    
#pragma omp for schedule(auto)
for (int i = 0; i < n; i++)
        {
            vectors[omp_get_thread_num()].push_back(i);
        }
    }
}
int main()
{
const int n = 64;
double init_time, final_time;

init_time = omp_get_wtime();
schedule(scheduleDefault,  "default:               ", n);
final_time = omp_get_wtime() - init_time;
std::cout << "time: " << final_time << std::endl;

init_time = omp_get_wtime();
schedule(scheduleStatic,   "schedule(static):      ", n);
final_time = omp_get_wtime() - init_time;
std::cout << "time: " << final_time << std::endl;

init_time = omp_get_wtime();
schedule(scheduleStatic4,  "schedule(static, 4):   ", n);
final_time = omp_get_wtime() - init_time;
std::cout << "time: " << final_time << std::endl;

init_time = omp_get_wtime();
schedule(scheduleStatic8,  "schedule(static, 8):   ", n);
final_time = omp_get_wtime() - init_time;
std::cout << "time: " << final_time << std::endl;

init_time = omp_get_wtime();
schedule(scheduleDynamic,  "schedule(dynamic):     ", n);
final_time = omp_get_wtime() - init_time;
std::cout << "time: " << final_time << std::endl;

init_time = omp_get_wtime();
schedule(scheduleDynamic1, "schedule(dynamic, 1):  ", n);
final_time = omp_get_wtime() - init_time;
std::cout << "time: " << final_time << std::endl;

init_time = omp_get_wtime();
schedule(scheduleDynamic4, "schedule(dynamic, 4):  ", n);
final_time = omp_get_wtime() - init_time;
std::cout << "time: " << final_time << std::endl;

init_time = omp_get_wtime();
schedule(scheduleDynamic8, "schedule(dynamic, 8):  ", n);
final_time = omp_get_wtime() - init_time;
std::cout << "time: " << final_time << std::endl;

init_time = omp_get_wtime();
schedule(scheduleGuided,   "schedule(guided):      ", n);
final_time = omp_get_wtime() - init_time;
std::cout << "time: " << final_time << std::endl;

init_time = omp_get_wtime();
schedule(scheduleGuided2,  "schedule(guided, 2):   ", n);
final_time = omp_get_wtime() - init_time;
std::cout << "time: " << final_time << std::endl;

init_time = omp_get_wtime();
schedule(scheduleGuided4,  "schedule(guided, 4):   ", n);
final_time = omp_get_wtime() - init_time;
std::cout << "time: " << final_time << std::endl;

init_time = omp_get_wtime();
schedule(scheduleGuided8,  "schedule(guided, 8):   ", n);
final_time = omp_get_wtime() - init_time;
std::cout << "time: " << final_time << std::endl;

init_time = omp_get_wtime();
schedule(scheduleAuto,     "schedule(auto):        ", n);
final_time = omp_get_wtime() - init_time;
std::cout << "time: " << final_time << std::endl;

init_time = omp_get_wtime();
schedule(scheduleRuntime,  "schedule(runtime):     ", n);
final_time = omp_get_wtime() - init_time;
std::cout << "time: " << final_time << std::endl;

return 0;
}