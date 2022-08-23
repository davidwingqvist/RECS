#include <recs_base.h>
#include <omp.h>
#include <iostream>

using namespace recs;

enum class Event {
    OnSceneChange,
    DEFAULT
};

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

    base.RegisterComponent<HelloWriter>();
    base.RegisterComponent<Test>();

    for (Entity i = 0; i < DEFAULT_MAX_ENTITIES; i++)
    {
        recs::Entity entity = base.CreateEntity();
        HelloWriter* hw = base.AddComponent<HelloWriter>(entity);
    }

    double start = omp_get_wtime();

    base.GetGroup<HelloWriter>();

    //recs::create_lua_file("../","Test");

    double end = omp_get_wtime() - start;
    std::cout << "Time: " << end << "\n";
}