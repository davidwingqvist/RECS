#include <recs_base.h>
#include <iostream>
using namespace recs;

struct HelloWriter
{
    int hello = 0;
    HelloWriter()
    {
        std::cout << "Hello LOL!" << std::endl;
    }
};

int main()
{
    recs::ecs_registry base;

    base.CreateEntity();
    base.CreateEntity();
    base.CreateEntity();
    base.CreateEntity();

    base.RegisterComponent(HelloWriter(), 1000);
}