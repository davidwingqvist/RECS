#include <../../../recs_base.h>
#include <omp.h>
#include <iostream>

//using namespace recs;

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
        const char t = (char)(65 + i);
        Test3* test3 = base.AddComponent<Test3>(entity);
        test3->i[0] = t;
        test3->i[1] = 's';
    }

    base.RegisterDataToState(Test2());

    double start = omp_get_wtime();

    base.SaveData();
    base.LoadData();

    double end = omp_get_wtime() - start;
    std::cout << "Time: " << end << "\n";
}