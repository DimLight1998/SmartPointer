#include "smartpointer.hpp"
#include <iostream>

using namespace std;

int main()
{
    cout << boolalpha;

    // test ExclusivePointer

    // null ExclusivePointer
    ExclusivePointer<string> exclusivePointer_1;
    cout << exclusivePointer_1.getRawPointer() << endl;
    cout << exclusivePointer_1.isNull() << endl;
    cout << bool(exclusivePointer_1) << endl;

    // not null ExclusivePointer
    ExclusivePointer<string> exclusivePointer_2(new string("foobar"));
    cout << exclusivePointer_2.getRawPointer() << endl;
    cout << exclusivePointer_2.isNull() << endl;
    cout << *exclusivePointer_2 << endl;
    cout << bool(exclusivePointer_2) << endl;

    string* ePointer_2_raw = exclusivePointer_2.getRawPointer();

    exclusivePointer_2.release();
    cout << exclusivePointer_2.getRawPointer() << endl;
    cout << exclusivePointer_2.isNull() << endl;
    cout << bool(exclusivePointer_2) << endl;

    exclusivePointer_2.setRawPointer(new string("foobar2"));
    cout << exclusivePointer_2.getRawPointer() << endl;
    cout << *exclusivePointer_2 << endl;

    delete ePointer_2_raw;

    // test rvalue
    ExclusivePointer<string> exclusivePointer_3 = []() { return ExclusivePointer<string>(new string("foobar3")); }();
    cout << exclusivePointer_3.getRawPointer() << endl;
    cout << *exclusivePointer_3 << endl;

    // test array
    ExclusivePointer<string[]> exclusivePointer_4(new string[3]);
    cout << exclusivePointer_4.getRawPointer() << endl;
    cout << exclusivePointer_4.isNull() << endl;

    exclusivePointer_4[0] = "foobar4";
    exclusivePointer_4[1] = "foobar5";
    exclusivePointer_4[2] = "foobar6";

    cout << *exclusivePointer_4 << endl;

    for (int i = 0; i < 3; i++)
    {
        cout << exclusivePointer_4[i] << endl;
    }

    string* ePointer_4_raw = exclusivePointer_4.getRawPointer();

    exclusivePointer_4.setRawPointer(new string[1]);
    *exclusivePointer_4 = "foobar7";
    cout << exclusivePointer_4.getRawPointer() << endl;
    cout << *exclusivePointer_4 << endl;

    delete[] ePointer_4_raw;

    // test CooperativePointer
    CooperativePointer<string> cooperativePointer_1;
    cout << cooperativePointer_1.getRawPointer() << endl;
    cout << cooperativePointer_1.getCounter() << endl;
    cout << cooperativePointer_1.isUnique() << endl;
    cout << bool(cooperativePointer_1) << endl;

    CooperativePointer<string> cooperativePointer_2(cooperativePointer_1);
    cout << cooperativePointer_2.getRawPointer() << endl;
    cout << cooperativePointer_2.getCounter() << endl;
    cout << cooperativePointer_2.isUnique() << endl;
    cout << bool(cooperativePointer_2) << endl;

    cooperativePointer_1.setRawPointerForAll(new string("barfoo"));
    cout << *cooperativePointer_1 << endl;
    cout << *cooperativePointer_2 << endl;

    cooperativePointer_1.setRawPointerForThis(new string("barfoo2"));
    cout << *cooperativePointer_1 << endl;
    cout << *cooperativePointer_2 << endl;

    CooperativePointer<string> cooperativePointer_3(cooperativePointer_1, true);
    cout << cooperativePointer_3.getRawPointer() << ' ' << cooperativePointer_1.getRawPointer() << endl;
    cout << cooperativePointer_3.getCounter() << ' ' << cooperativePointer_1.getCounter() << endl;
    cout << cooperativePointer_3.isUnique() << ' ' << cooperativePointer_1.isUnique() << endl;
    cout << *cooperativePointer_3 << ' ' << *cooperativePointer_1 << endl;

    cooperativePointer_1.release();
    cout << cooperativePointer_1.getRawPointer() << endl;
    cout << cooperativePointer_1.getCounter() << endl;

    cout << cooperativePointer_3.getRawPointer() << endl;
    cout << cooperativePointer_3.getCounter() << endl;

    CooperativePointer<string> cooperativePointer_4(new string);
    CooperativePointer<string> cooperativePointer_5(cooperativePointer_4);

    cout << cooperativePointer_4.getRawPointer() << endl;
    cout << cooperativePointer_5.getRawPointer() << endl;

    cout << cooperativePointer_4.getCounter() << endl;
    cout << cooperativePointer_5.getCounter() << endl;

    cooperativePointer_4.setRawPointerForThis(new string);

    cout << cooperativePointer_4.getCounter() << endl;
    cout << cooperativePointer_5.getCounter() << endl;

    string* cPointer_4_raw = cooperativePointer_4.getRawPointer();
    cooperativePointer_4   = cooperativePointer_5;

    cout << cooperativePointer_4.getCounter() << endl;
    cout << cooperativePointer_5.getCounter() << endl;

    delete cPointer_4_raw;

    cout << cooperativePointer_4.getRawPointer() << endl;

    cPointer_4_raw = cooperativePointer_4.getRawPointer();
    cooperativePointer_4.setRawPointerForAll(new string("barfoo3"));

    cout << cooperativePointer_4.getRawPointer() << endl;
    cout << cooperativePointer_4.getCounter() << endl;
    cout << cooperativePointer_5.getRawPointer() << endl;
    cout << cooperativePointer_5.getCounter() << endl;

    delete cPointer_4_raw;

    // test array

    CooperativePointer<string[]> cooperativePointer_6(new string[3]);
    CooperativePointer<string[]> cooperativePointer_7(cooperativePointer_6);

    *cooperativePointer_6   = "foobar_0";
    cooperativePointer_7[1] = "foobar_1";
    cooperativePointer_6[2] = "foobar_2";

    for (int i = 0; i < 3; i++)
    {
        cout << cooperativePointer_6[i] << endl;
    }

    return 0;
}