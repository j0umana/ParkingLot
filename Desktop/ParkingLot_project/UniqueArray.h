#ifndef MTMPARKINGLOT_UNIQUEARRAY_H
#define MTMPARKINGLOT_UNIQUEARRAY_H

template <class Element, class Compare = std::equal_to<Element>>
class UniqueArray {
    Element **Array;
    const int size;
    Compare compareObject;

public:

    explicit UniqueArray(unsigned int size);
    UniqueArray(const UniqueArray& other);
    ~UniqueArray();
    UniqueArray& operator=(const UniqueArray&) = delete;
    unsigned int insert(const Element& element);
    bool getIndex(const Element& element, unsigned int& index) const;
    const Element* operator[] (const Element& element) const;
    bool remove(const Element& element);
    unsigned int getCount() const;
    unsigned int getSize() const;

    /**
     * Element* operator[] (unsigned int index): an overload to operator []
     * were it returns a pointer to the element that is in the array in the
     * given index.
     * @param index
     * @return a pointer to the element that is in the Array[index]
     */
    Element* findElementByIndex (unsigned int index) const;

    /**
   * const Element* operator[] (unsigned int index) const:
     * does the same thing as Element* operator[] (unsigned int index), but
     * is type of const, and returns pointer to the element of type const
   * @param index
   * @return a pointer (const) to the element that is in the Array[index]
   */
    const Element* constFindElementByIndex(unsigned int index) const;
    void returnFirstNull(unsigned int& index);


    class Filter {
    public:
        virtual bool operator() (const Element&) const = 0;
    };
    UniqueArray filter(const Filter& f) const;

    class UniqueArrayIsFullException{};

};



#include "UniqueArrayImp.h"


#endif //MTMPARKINGLOT_UNIQUEARRAY_H
