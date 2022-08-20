#include <recs_base.h>
#include <iostream>
#include <omp.h>

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

    for (Entity i = 0; i < DEFAULT_MAX_ENTITIES; i++)
    {
        recs::Entity entity = base.CreateEntity();
        HelloWriter* hw = base.AddComponent<HelloWriter>(entity);
    }

    base.RegisterOnUpdate<HelloWriter>([&](const Entity& entity, HelloWriter& hw)
        {
            std::cout << "Hello!" << "\n";
        });

    int testing = 0;

    base.RegisterEvent<Event, Event::DEFAULT>([&] {

        std::cout << typeid(Event).name() << std::endl;

        });

    base.RegisterEvent<Event, Event::OnSceneChange>([&] {

        testing++;

        std::cout << "Hello! " << testing << std::endl;

        });

    base.RunEvent<Event, Event::OnSceneChange>();
    base.RunEvent<Event, Event::DEFAULT>();


    double start = omp_get_wtime();
    
    //base.Update();

    double end = omp_get_wtime() - start;
    std::cout << "Time: " << end << "\n";
}