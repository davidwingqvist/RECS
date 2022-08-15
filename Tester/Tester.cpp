#include <recs_base.h>
#include <iostream>
using namespace recs;

struct HelloWriter
{
    int hello = 0;
};

int main()
{
    recs::ecs_registry base;

    base.CreateEntity();
    base.CreateEntity();
    base.CreateEntity();
    base.CreateEntity();

    base.RegisterComponent(HelloWriter());

    base.ForEach<HelloWriter>([&](Entity& entity, HelloWriter& hello)
    {
        hello.hello = entity;
        std::cout << "Hello from Entity: " << hello.hello << std::endl;
    });
}