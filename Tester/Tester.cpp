#include <recs_base.h>
#include <omp.h>
#include <iostream>

using namespace recs;

int teste = 0;

enum class Event {
    OnSceneChange,
    DEFAULT
};
//
//template <class... Ts>
//void print_all(std::ostream& os, Ts const&... args) {
//    ((os << args), ...);
//    teste++;
//    std::cout << teste << "\n";
//}

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

    base.RemoveComponent<HelloWriter>(0);

    double start = omp_get_wtime();

    //auto group = base.Group<HelloWriter, Test, Test2>();
    //group.ForEach([&](const Entity& entity, HelloWriter& hello, Test& test, Test2& test2) {

    //    hello.hello = entity;
    //    test.test = entity;
    //    test2.test = test.test3;
    //    std::cout << entity << "\n";

    // });

    base.View<HelloWriter>().ForEach([&](const Entity& entity, HelloWriter& hello) {

        hello.hello = entity;

        });

    //group.ForEach([&](HelloWriter& hello, Test& test, Test2& test2) {

    //    hello.hello = 50;
    //    test.test = 50;
    //    test2.test = 50;

    //    });

    //auto view = base.View<HelloWriter>();
    //view.ForEach([&](HelloWriter& helo) {

    //    helo.hello = 25;

    //    });

    double end = omp_get_wtime() - start;
    std::cout << "Time: " << end << "\n";

}