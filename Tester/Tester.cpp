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
        base.AddComponent<Test2>(entity)->i = i;
    }

    //base.UseOpenMP(true);

    double start = omp_get_wtime();


    base.View<Test2>().ForEach([](Test2& test) {

        ++test.i;

        });

    double end = omp_get_wtime() - start;
    std::cout << "Time: " << end << "\n";
}