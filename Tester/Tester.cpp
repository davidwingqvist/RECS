#include <../../../recs_base.h>
#include <omp.h>
#include <iostream>

//using namespace recs;

struct Test
{
    int i = 0;
    float j = 6;
};

struct Test2
{
    int i = 0;
};

struct Test3
{
    char i[2];
};

int main()
{
    recs::recs_registry base(5);

    for (recs::Entity i = 0; i < 5; i++)
    {
        recs::Entity entity = base.CreateEntity();
        base.AddComponent<Test2>(entity)->i = 56 + (i * 100);
        base.AddComponent<Test>(entity)->j = 100 + i * 50;
        const char t = (char)(65 + i);
        Test3* test3 = base.AddComponent<Test3>(entity);
        test3->i[0] = t;
        test3->i[1] = 's';
    }

    base.RegisterDataToState(Test2());
    base.RegisterDataToState(Test3());
    base.RegisterDataToState(Test());

    double start = omp_get_wtime();

    //base.SaveData();
    base.LoadData();

    base.View<Test>().ForEach([&](Test& test) {

        std::cout << test.j << std::endl;

        });

    double end = omp_get_wtime() - start;
    std::cout << "Time: " << end << "\n";
}