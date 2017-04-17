#ifndef SMARTPOINTER_HPP
#define SMARTPOINTER_HPP

class ControlBlock;


template <typename DataType>
class ExclusivePointer
{
public:
    // Constructors
    explicit ExclusivePointer(DataType* rawPointer = nullptr);
    ExclusivePointer(ExclusivePointer<DataType>&& exclusivePointer);
    ExclusivePointer(const ExclusivePointer<DataType>&) = delete;

    // Destructors
    ~ExclusivePointer();

    // Observers
    DataType* getRawPointer();
    bool      isNull();

    // Modifiers
    void setRawPointer(DataType* rawPointer);
    void release();

    // Operators
    operator bool();
    DataType& operator*();
    DataType* operator->();

private:
    DataType* rawPointer;
};


template <typename DataType>
class ExclusivePointer<DataType[]>
{
public:
    // Constructors
    explicit ExclusivePointer(DataType* rawPointer = nullptr);
    ExclusivePointer(ExclusivePointer<DataType[]>&& exclusivePointer);
    ExclusivePointer(const ExclusivePointer<DataType[]>&) = delete;

    // Destructors
    ~ExclusivePointer();

    // Observers
    DataType* getRawPointer();
    bool      isNull();

    // Modifiers
    void setRawPointer(DataType* rawPointer);
    void release();

    // Operators
    operator bool();
    DataType& operator*();
    DataType& operator[](int index);
    DataType* operator->();

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


// Implementations

template <typename DataType>
ExclusivePointer<DataType>::ExclusivePointer(DataType* rawPointer)
    : rawPointer(rawPointer)
{
}


template <typename DataType>
ExclusivePointer<DataType>::ExclusivePointer(ExclusivePointer<DataType>&& exclusivePointer)
    : rawPointer(exclusivePointer.rawPointer)
{
}


template <typename DataType>
ExclusivePointer<DataType>::~ExclusivePointer()
{
    delete rawPointer;
}


template <typename DataType>
DataType* ExclusivePointer<DataType>::getRawPointer()
{
    return rawPointer;
}


template <typename DataType>
bool ExclusivePointer<DataType>::isNull()
{
    return (rawPointer == nullptr);
}


template <typename DataType>
void ExclusivePointer<DataType>::setRawPointer(DataType* rawPointer)
{
    this->rawPointer = rawPointer;
}


template <typename DataType>
void ExclusivePointer<DataType>::release()
{
    rawPointer = nullptr;
}


template <typename DataType>
ExclusivePointer<DataType>::operator bool()
{
    return (rawPointer != nullptr);
}


template <typename DataType>
DataType& ExclusivePointer<DataType>::operator*()
{
    return *rawPointer;
}


template <typename DataType>
DataType* ExclusivePointer<DataType>::operator->()
{
    return rawPointer;
}


// array specialization

template <typename DataType>
ExclusivePointer<DataType[]>::ExclusivePointer(DataType* rawPointer)
    : rawPointer(rawPointer)
{
}


template <typename DataType>
ExclusivePointer<DataType[]>::ExclusivePointer(ExclusivePointer<DataType[]>&& exclusivePointer)
    : rawPointer(exclusivePointer.rawPointer)
{
}


template <typename DataType>
ExclusivePointer<DataType[]>::~ExclusivePointer()
{
    delete[] rawPointer;
}


template <typename DataType>
DataType* ExclusivePointer<DataType[]>::getRawPointer()
{
    return rawPointer;
}


template <typename DataType>
bool ExclusivePointer<DataType[]>::isNull()
{
    return (rawPointer == nullptr);
}


template <typename DataType>
void ExclusivePointer<DataType[]>::setRawPointer(DataType* rawPointer)
{
    this->rawPointer = rawPointer;
}


template <typename DataType>
void ExclusivePointer<DataType[]>::release()
{
    rawPointer = nullptr;
}


template <typename DataType>
ExclusivePointer<DataType[]>::operator bool()
{
    return (rawPointer != nullptr);
}


template <typename DataType>
DataType& ExclusivePointer<DataType[]>::operator*()
{
    return *rawPointer;
}


template <typename DataType>
DataType* ExclusivePointer<DataType[]>::operator->()
{
    return rawPointer;
}


template <typename DataType>
DataType& ExclusivePointer<DataType[]>::operator[](int index)
{
    return rawPointer[index];
}


#endif    // SMARTPOINTER_HPP
