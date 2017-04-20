#ifndef SMARTPOINTER_HPP
#define SMARTPOINTER_HPP

template <typename DataType>
class ControlBlock;


template <typename DataType>
class ControlBlock<DataType[]>;


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
    ExclusivePointer<DataType>& operator=(ExclusivePointer<DataType>) = delete;

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
    ExclusivePointer<DataType[]>& operator=(ExclusivePointer<DataType[]>) = delete;

private:
    DataType* rawPointer;
};


// TODO: finish this
template <typename DataType>
class CooperativePointer
{
public:
    // Constructors
    CooperativePointer(DataType* rawPointer = nullptr);
    CooperativePointer(const CooperativePointer<DataType>& srcPointer = nullptr, bool isWeak = false);

    // Destructors
    ~CooperativePointer();

    // Observers
    DataType*     getRawPointer();
    unsigned long getCounter();
    bool          isUnique();

    // Modifiers
    void setRawPointerForThis(DataType* newPointer);
    void setRawPointerForAll(DataType* newPointer);
    void release();

    // Operators
    DataType& operator*();
    DataType* operator->();
    operator bool();

private:
    ControlBlock<DataType>* controlBlock;
    bool                    isWeak;
};


// TODO: finish this
// TODO: add assignment
template <typename DataType>
class CooperativePointer<DataType[]>
{
public:
    // Constructors
    CooperativePointer(DataType* rawPointer = nullptr);
    CooperativePointer(const CooperativePointer<DataType[]>& srcPointer = nullptr, bool isWeak = false);

    // Destructors
    ~CooperativePointer();

    // Observers
    DataType*     getRawPointer();
    unsigned long getCounter();
    bool          isUnique();

    // Modifiers
    void setRawPointerForThis(DataType* newPointer);
    void setRawPointerForAll(DataType* newPointer);
    void release();

    // Operators
    DataType& operator*();
    DataType* operator->();
    DataType operator[](int index);
    operator bool();

private:
    ControlBlock<DataType[]>* controlBlock;
    bool                      isWeak;
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

    // Modifiers
    void setRawPointer(DataType* newPointer);

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

    // Modifiers
    void setRawPointer(DataType* newPointer);

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
void ControlBlock<DataType>::setRawPointer(DataType* newPointer)
{
    rawPointer = newPointer;
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
void ControlBlock<DataType[]>::setRawPointer(DataType* newPointer)
{
    rawPointer = newPointer;
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

// CooperativePointer<DataType>

template <typename DataType>
CooperativePointer<DataType>::CooperativePointer(DataType* rawPointer)
// cannot construct a weak pointer from a raw pointer
// any pointers constructed in this way have a not-null controlBlock, unless bad_alloc is thrown
{
    controlBlock = new ControlBlock<DataType>(rawPointer);
}


template <typename DataType>
CooperativePointer<DataType>::CooperativePointer(const CooperativePointer<DataType>& srcPointer, bool isWeak)
// works for both weak pointers and strong pointers
// normally, controlBlock won't be null
{
    controlBlock = srcPointer.controlBlock;

    if ((!isWeak) && (controlBlock != nullptr))
    {
        controlBlock->increaseCounter();
    }
}


template <typename DataType>
CooperativePointer<DataType>::~CooperativePointer()
// works for both weak pointers and strong pointers
{
    if ((!isWeak) && (controlBlock != nullptr))
    {
        controlBlock->decreaseCounter();
    }
}


template <typename DataType>
DataType* CooperativePointer<DataType>::getRawPointer()
// need to assume that controlBlock is not null, which is normally true
// Observers don't need the pointer be strong
{
    return controlBlock->getRawPointer();
}


template <typename DataType>
unsigned long CooperativePointer<DataType>::getCounter()
// need to assume that controlBlock is not null, which is normally true
// Observers don't need the pointer be strong
{
    return controlBlock->getCounter();
}


template <typename DataType>
bool CooperativePointer<DataType>::isUnique()
// need to assume that controlBlock is not null, which is normally true
// Observers don't need the pointer be strong
{
    if (isWeak)
    {
        return false;
    }
    return (controlBlock->getCounter() == 1);
}


template <typename DataType>
void CooperativePointer<DataType>::setRawPointerForThis(DataType* newPointer)
// need to assume that controlBlock is not null, which is normally true
// controlBlock will change but is not null, unless bad_alloc is thrown
// if the pointer is weak, nothing happens
{
    if (!isWeak)
    {
        controlBlock->decreaseCounter();
        controlBlock = new ControlBlock<DataType>(newPointer);
    }
}


template <typename DataType>
void CooperativePointer<DataType>::setRawPointerForAll(DataType* newPointer)
// need to assume that controlBlock is not null, which is normally true
// if the pointer is weak, nothing happens
{
    if (!isWeak)
    {
        controlBlock->setRawPointer(newPointer);
    }
}


template <typename DataType>
void CooperativePointer<DataType>::release()
// set controlBlock pointing to nullptr to ensure that controlBlock is not null
// if the pointer is weak, nothing happens
// TODO have better solution?
{
    if (!isWeak)
    {
        controlBlock->decreaseCounter();
        controlBlock = new ControlBlock<DataType>(nullptr);
    }
}


template <typename DataType>
DataType& CooperativePointer<DataType>::operator*()
// need to assume that controlBlock is not null, which is normally true
// Observers don't need the pointer be strong
{
    return *(controlBlock->getRawPointer());
}


template <typename DataType>
DataType* CooperativePointer<DataType>::operator->()
// need to assume that controlBlock is not null, which is normally true
// Observers don't need the pointer be strong
{
    return controlBlock->getRawPointer();
}


template <typename DataType>
CooperativePointer<DataType>::operator bool()
// need to assume that controlBlock is not null, which is normally true
// Observers don't need the pointer be strong
{
    return (controlBlock->getRawPointer() != nullptr);
}

// CooperativePointer<DataType[]>

template <typename DataType>
CooperativePointer<DataType[]>::CooperativePointer(DataType* rawPointer)
{
    controlBlock = new ControlBlock<DataType[]>(rawPointer);
}


template <typename DataType>
CooperativePointer<DataType[]>::CooperativePointer(const CooperativePointer<DataType[]>& srcPointer, bool isWeak)
{
    controlBlock = srcPointer.controlBlock;

    if ((!isWeak) && (controlBlock != nullptr))
    {
        controlBlock->increaseCounter();
    }
}


template <typename DataType>
CooperativePointer<DataType[]>::~CooperativePointer()
{
    if ((!isWeak) && (controlBlock != nullptr))
    {
        controlBlock->decreaseCounter();
    }
}


template <typename DataType>
DataType* CooperativePointer<DataType[]>::getRawPointer()
{
    return controlBlock->getRawPointer();
}


template <typename DataType>
unsigned long CooperativePointer<DataType[]>::getCounter()
{
    return controlBlock->getCounter();
}


template <typename DataType>
bool CooperativePointer<DataType[]>::isUnique()
{
    if (isWeak)
    {
        return false;
    }
    return (controlBlock->getCounter() == 1);
}


template <typename DataType>
void CooperativePointer<DataType[]>::setRawPointerForThis(DataType* newPointer)
{
    if (!isWeak)
    {
        controlBlock->decreaseCounter();
        controlBlock = new ControlBlock<DataType[]>(newPointer);
    }
}


template <typename DataType>
void CooperativePointer<DataType[]>::setRawPointerForAll(DataType* newPointer)
{
    if (!isWeak)
    {
        controlBlock->setRawPointer(newPointer);
    }
}


template <typename DataType>
void CooperativePointer<DataType[]>::release()
{
    if (!isWeak)
    {
        controlBlock->decreaseCounter();
        controlBlock = new ControlBlock<DataType[]>(nullptr);
    }
}


template <typename DataType>
DataType& CooperativePointer<DataType[]>::operator*()
{
    return *(controlBlock->getRawPointer());
}


template <typename DataType>
DataType* CooperativePointer<DataType[]>::operator->()
{
    return controlBlock->getRawPointer();
}


template <typename DataType>
DataType CooperativePointer<DataType[]>::operator[](int index)
{
    return controlBlock->getRawPointer()[index];
}


template <typename DataType>
CooperativePointer<DataType[]>::operator bool()
{
    return (controlBlock->getRawPointer() != nullptr);
}

#endif    // SMARTPOINTER_HPP
