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

    recs::recs_registry base;

    for (Entity i = 0; i < DEFAULT_MAX_ENTITIES; i++)
    {
        recs::Entity entity = base.CreateEntity();
        HelloWriter* hw = base.AddComponent<HelloWriter>(entity);
    }

    base.RegisterOnUpdate<HelloWriter>([&](const Entity& entity, HelloWriter& hw)
        {
            std::cout << "Hello!" << "\n";
        });


    double start = omp_get_wtime();
    
    base.Update();

    //base.ForEach<HelloWriter>([&](const Entity& entity, HelloWriter& comp) {
    //    comp.hello = entity;
    //});

    double end = omp_get_wtime() - start;
    std::cout << "Time: " << end << "\n";
}