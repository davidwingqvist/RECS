#include <../../../recs_base.h>
#include <omp.h>
#include <iostream>

//using namespace recs;

struct Test
{
    int i;
};

int main()
{
    recs::recs_registry base;

    for (recs::Entity i = 0; i < recs::DEFAULT_MAX_ENTITIES; i++)
    {
        recs::Entity entity = base.CreateEntity();
        base.AddComponent<Test>(entity)->i = i;
    }

    for (recs::Entity i = 0; i < recs::DEFAULT_MAX_ENTITIES; i++)
    {
        std::cout << base.GetComponent<Test>(i)->i << std::endl;
    }

    double start = omp_get_wtime();

    double end = omp_get_wtime() - start;
    std::cout << "Time: " << end << "\n";

}