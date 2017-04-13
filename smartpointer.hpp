#ifndef SMARTPOINTER_HPP
#define SMARTPOINTER_HPP

class ControlBlock;


template <typename DataType>
class ExclusivePointer
{
public:
private:
    DataType* rawPointer;
};


template <typename DataType>
class CooperativePointer
{
public:
private:
    DataType*     rawPointer;
    ControlBlock* controlBlock;
};


class ControlBlock
{
};


#endif    // SMARTPOINTER_HPP
