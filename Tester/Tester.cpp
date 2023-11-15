#include <../../../recs_base.h>
#include <omp.h>
#include <iostream>

//using namespace recs;

struct Test
{
    std::string i = "";
};

struct Test2
{
    int i = 0;
};

int main()
{
    recs::recs_registry base;

    for (recs::Entity i = 0; i < recs::DEFAULT_MAX_ENTITIES; i++)
    {
        recs::Entity entity = base.CreateEntity();
        base.AddComponent<Test>(entity);
    }

    double start = omp_get_wtime();

    base.Pool();

    double end = omp_get_wtime() - start;
    std::cout << "Time: " << end << "\n";

}