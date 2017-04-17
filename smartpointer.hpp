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
    ControlBlock* controlBlock;
};


template <typename DataType>
class ControlBlock
{
public:
    // Constructors
    ControlBlock(DataType* rawPointer);

    // Destructors
    ~ControlBlock();

    // Observers
    DataType*     getRawPointer();
    unsigned long getCounter();

    // Friends
    friend CooperativePointer<DataType>;

private:
    // Modifiers
    void increaseCounter();
    void decreaseCounter();

    unsigned long counter;
    DataType*     rawPointer;
};


template <typename DataType>
class ControlBlock<DataType[]>
{
public:
    // Constructors
    ControlBlock(DataType* rawPointer);

    // Destructors
    ~ControlBlock();

    // Observers
    DataType*     getRawPointer();
    unsigned long getCounter();

    // Friends
    friend CooperativePointer<DataType[]>;

private:
    // Modifiers
    void increaseCounter();
    void decreaseCounter();

    unsigned long counter;
    DataType*     rawPointer;
};


// Implementations

// ExclusivePointer<DataType>

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

// ExclusivePointer<DataType[]>

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

// ControlBlock<DataType>

template <typename DataType>
ControlBlock<DataType>::ControlBlock(DataType* rawPointer)
    : rawPointer(rawPointer)
    , counter(1)
{
}


template <typename DataType>
ControlBlock<DataType>::~ControlBlock()
{
}


template <typename DataType>
DataType* ControlBlock<DataType>::getRawPointer()
{
    return rawPointer;
}


template <typename DataType>
unsigned long ControlBlock<DataType>::getCounter()
{
    return counter;
}


template <typename DataType>
void ControlBlock<DataType>::increaseCounter()
{
    counter++;
}


template <typename DataType>
void ControlBlock<DataType>::decreaseCounter()
{
    counter--;

    if (counter <= 0)
    {
        delete rawPointer;
        rawPointer = nullptr;
        delete this;    // suicide
    }
}

// ControlBlock<DataType[]>

template <typename DataType>
ControlBlock<DataType[]>::ControlBlock(DataType* rawPointer)
    : rawPointer(rawPointer)
    , counter(1)
{
}


template <typename DataType>
ControlBlock<DataType[]>::~ControlBlock()
{
}


template <typename DataType>
DataType* ControlBlock<DataType[]>::getRawPointer()
{
    return rawPointer;
}


template <typename DataType>
unsigned long ControlBlock<DataType[]>::getCounter()
{
    return counter;
}


template <typename DataType>
void ControlBlock<DataType[]>::increaseCounter()
{
    counter++;
}


template <typename DataType>
void ControlBlock<DataType[]>::decreaseCounter()
{
    counter--;

    if (counter <= 0)
    {
        delete[] rawPointer;
        rawPointer = nullptr;
        delete this;    // suicide
    }
}


#endif    // SMARTPOINTER_HPP
