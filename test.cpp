#include "smartpointer.hpp"
#include <iostream>

using namespace std;


struct Bar
{
    void foo()
    {
        cout << "Foo!!!!!\n";
    }
};


int main()
{
    ExclusivePointer<long> p(new long(8));
    cout << *p << endl;
    (*p)++;
    cout << *p << endl;
    ExclusivePointer<Bar> pt(new Bar);
    pt->foo();
    ExclusivePointer<bool[]> bp(new bool[10]);

    for (int i = 0; i < 10; i++)
    {
        bp[i] = (i % 2 == 0);
    }

    for (int i = 0; i < 10; i++)
    {
        cout << boolalpha << bp[i] << endl;
    }

    CooperativePointer<int> ic(new int(9));
    cout << *ic << endl;
    CooperativePointer<int> ic2(ic);
    cout << ic2.getCounter() << endl;
    CooperativePointer<int> icw(ic2, true);
    cout << icw.getCounter() << endl;

    return 0;
}