#include <../../../recs_base.h>
#include <omp.h>
#include <iostream>

//using namespace recs;

struct Transform
{
    float x;
    float y;
    float z;
};

struct ID
{
    int id;
};

int main()
{
    recs::recs_registry base(500); 

    for (recs::Entity i = 0; i < 500; i++)
    {
        recs::Entity entity = base.CreateEntity();
        ID* transform = base.AddComponent<ID>(entity);
        //transform->x = 50 + i;
        //transform->y = 100 * i;
        //transform->z = 2 + i;
    }


    double start = omp_get_wtime();

    double end = omp_get_wtime() - start;
    std::cout << "Time: " << end << "\n";
}