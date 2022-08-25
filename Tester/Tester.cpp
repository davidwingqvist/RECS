#include <recs_base.h>
#include <omp.h>
#include <iostream>

using namespace recs;

int teste = 0;

enum class Event {
    OnSceneChange,
    DEFAULT
};

int main()
{

    recs::recs_registry base;

    base.RegisterComponent<HelloWriter>();
    base.RegisterComponent<Test>();
    base.RegisterComponent<Test2>();

    for (Entity i = 0; i < DEFAULT_MAX_ENTITIES; i++)
    {
        recs::Entity entity = base.CreateEntity();
        HelloWriter* hw = base.AddComponent<HelloWriter>(entity);
        base.AddComponent<Test>(entity);
        base.AddComponent<Test2>(entity);

    }

    double start = omp_get_wtime();

    auto group = base.Group<HelloWriter, Test, Test2>();
    group.ForEach([&](const Entity& entity, HelloWriter& hello, Test& test, Test2& test2) {

		hello.test2 = test.test4 + test2.test3 + entity + test.test;

     });

    double end = omp_get_wtime() - start;
    std::cout << "Time: " << end << "\n";

}