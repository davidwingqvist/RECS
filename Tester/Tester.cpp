#include <recs_base.h>
#include <iostream>
#include <omp.h>
using namespace recs;

struct HelloWriter
{
    int hello = 0;
};

int main()
{
    recs::ecs_registry base;

    base.RegisterComponent(HelloWriter());


    double start = omp_get_wtime();

    base.ForEach<HelloWriter>([&](Entity& entity, HelloWriter& comp) {

        comp.hello = entity * entity / 2.35f * 6.54f / 100.5f + 3.53;
        //std::cout << "Hello from Entity: " << comp.hello << std::endl;

    });

    double end = omp_get_wtime() - start;
    std::cout << "Time: " << end << "\n";
}