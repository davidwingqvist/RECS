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

struct Test3
{
    const char* i = "";
};

int main()
{
    recs::recs_registry base;

    base.RegisterComponent<Test>();

    for (recs::Entity i = 0; i < 450; i++)
    {
        recs::Entity entity = base.CreateEntity();
        base.AddComponent<Test2>(entity)->i = i;
        base.AddComponent<Test>(entity)->i = "s";
        base.AddComponent<Test3>(entity);
    }

    double start = omp_get_wtime();

    double end = omp_get_wtime() - start;
    std::cout << "Time: " << end << "\n";
}