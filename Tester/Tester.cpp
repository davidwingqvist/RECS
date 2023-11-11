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
        base.AddComponent<Test>(entity)->i = "Number is: " + std::to_string(i);
        base.AddComponent<Test2>(entity)->i = i;

    }

    

    base.View<Test>().ForEach([](Test& test) {

        std::cout << test.i << "\n";

        });

    double start = omp_get_wtime();

    double end = omp_get_wtime() - start;
    std::cout << "Time: " << end << "\n";

}