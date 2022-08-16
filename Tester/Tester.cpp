#include <recs_base.h>
#include <iostream>
#include <omp.h>
using namespace recs;

struct HelloWriter
{
    int hello = 0;
};

struct Test
{
    int test = 0;
};

int main()
{
    recs::recs_registry base;

    base.RegisterComponent(HelloWriter());

    for (Entity i = 0; i < DEFAULT_MAX_ENTITIES; i++)
    {
        recs::Entity entity = base.CreateEntity();
        base.AddComponent<HelloWriter>(entity);
    }


    double start = omp_get_wtime();
  
    base.ForEach<HelloWriter>([&](const Entity& entity, HelloWriter& comp) {
        comp.hello = entity;
    });


    double end = omp_get_wtime() - start;
    std::cout << "Time: " << end << "\n";
}