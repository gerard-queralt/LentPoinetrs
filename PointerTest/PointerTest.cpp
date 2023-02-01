#include <iostream>
#include <memory>
#include "AxolotlPointers.h"

using namespace std;

class A
{
public:
    A(int val) : val(val)
    {
    }
    ~A()
    {
        cout << "Deleting A with val = " << val << endl;
    }
    void foo()
    {
        cout << "Hello from foo! Val = " << val << endl;
    }
private:
    int val;
};

void bar(const AxoPtr::lent_ptr<A>& lentA)
{
    cout << "Hello from bar!" << endl;
}

int main()
{
    //create unique ptr
    std::unique_ptr<A> a = std::make_unique<A>(10);
    //create lent ptr
    AxoPtr::lent_ptr<A> lentA;
    lentA = AxoPtr::lent_ptr<A>(a.get());
    //operator ->
    lentA->foo();
    //operator *
    A test = *lentA;
    test.foo();
    //operator bool
    if (lentA)
    {
        cout << "lent ptr not empty" << endl;
    }
    //operator =nullptr
    lentA = nullptr;
    //operator !
    if (!lentA)
    {
        cout << "lent ptr empty" << endl;
    }
    //unique ptr to lent conversion
    lentA = a;
    AxoPtr::lent_ptr<A> lentA2 = a;
    //unique ptr to lent cast
    bar(a);
    //vectors
    std::vector<unique_ptr<A>> uniqueVector;
    for (int i = 0; i < 4; ++i)
    {
        uniqueVector.push_back(std::make_unique<A>(i));
    }
    std::vector<AxoPtr::lent_ptr<A>> lentVector = AxoPtr::uniqueVectorToLent(uniqueVector);
    for (int i = 0; i < lentVector.size(); ++i)
    {
        lentVector[i]->foo();
    }
    //find
    std::vector<std::unique_ptr<A>>::iterator res = std::find(std::begin(uniqueVector), std::end(uniqueVector), lentVector[0]);
    uniqueVector.erase(res);
    cout << "Now vector has size: " << uniqueVector.size() << endl;
    //comparison
    cout << "lent equal to self? " << std::boolalpha << (lentA == lentA) << endl;
    cout << "lent equal to raw? " << std::boolalpha << (lentA == a.get()) << endl;
    cout << "lent equal to unique? " << std::boolalpha << (lentA == a) << endl;
    cout << "raw equal to lent? " << std::boolalpha << (a.get() == lentA) << endl;
    cout << "unique equal to lent? " << std::boolalpha << (a == lentA) << endl;
}
