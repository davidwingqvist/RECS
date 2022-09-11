#include <recs_base.h>
#include <omp.h>
#include <iostream>

struct Test
{
    unsigned int i = 0;
};

using namespace recs;

int main()
{
    recs::recs_registry base;

    base.SetNumberOfThreads();

    base.RegisterComponent<Test>();

    for (Entity i = 0; i < DEFAULT_MAX_ENTITIES; i++)
    {
        recs::Entity entity = base.CreateEntity();
        base.AddComponent<Test>(entity)->i = i;
    }

    double start = omp_get_wtime();

    base.View<Test>().ForEach([](const Entity& entity, Test& test) {

        test.i = 5 * 1.353f / 0.352f + 2.5f;

        });

    double end = omp_get_wtime() - start;
    std::cout << "Time: " << end << "\n";

    start = omp_get_wtime();

    base.View<Test>().ForEach_mult([](const Entity& entity, Test& test) {

        test.i = 5 * 1.353f / 0.352f + 2.5f;

        });

    end = omp_get_wtime() - start;
    std::cout << "Mult Time: " << end << "\n";

}