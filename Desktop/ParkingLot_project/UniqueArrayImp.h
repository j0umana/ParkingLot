#ifndef PARKINGLOT_UNIQUEARRAYIMP_H
#define PARKINGLOT_UNIQUEARRAYIMP_H

template<class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(unsigned int size) :
        Array(new Element*[size]),size(size){
    for(int i=0;i<size;i++){
        Array[i]=nullptr;
    }
}

//------------------------------------------------------------------------------

template <class Element, class Compare>
UniqueArray<Element,Compare> :: UniqueArray(const UniqueArray& other) :
        Array(new Element*[other.size]),size(other.size){
    for(int i=0;i<size;i++){
        if(other.Array[i]==nullptr) {
            Array[i]=nullptr;
            continue;
        }
        Array[i]=new Element(*(other.Array[i]));
    }
}

//------------------------------------------------------------------------------
template <class Element, class Compare>
UniqueArray<Element,Compare> :: ~UniqueArray() {
    for(int i=0;i<size;i++){
        delete this->Array[i];
    }
    delete[] Array;
}

//------------------------------------------------------------------------------

template <class Element, class Compare>
unsigned int UniqueArray<Element,Compare> :: insert(const Element& element){
    for(int i=0;i<size;i++){
        if(Array[i] == nullptr)
            continue;
        if(compareObject(*Array[i],element)){
            return i;
        }
    }
    for(int i=0;i<size;i++){
        if(Array[i]==nullptr) {
            Array[i]= new Element(element);
            return i;
        }
    }

    throw UniqueArrayIsFullException();
}

//------------------------------------------------------------------------------

template <class Element, class Compare>
bool UniqueArray<Element,Compare> :: getIndex(const Element& element,
                                              unsigned int& index) const{

    for(int i=0;i<size;i++){
        if(Array[i] == nullptr)
            continue;
        if(compareObject(*Array[i],element)){
            index=i;
            return true;
        }
    }
    index=size+1;
    return false;
}

//------------------------------------------------------------------------------

template <class Element, class Compare>
const Element* UniqueArray<Element,Compare> ::
operator[] (const Element& element) const {
    for (int i = 0; i<size; i++) {
        if(Array[i]== nullptr)
            continue;
        if (compareObject(element, *Array[i])) {
            return Array[i];
        }
    }
    return nullptr;
}

//------------------------------------------------------------------------------
template <class Element, class Compare>
bool UniqueArray<Element,Compare> :: remove(const Element& element){
    for (int i = 0; i<size; i++) {
        if(Array[i] == nullptr)
            continue;
        if (compareObject(element, *Array[i])) {
            delete(Array[i]);
            Array[i]=nullptr;
            return true;
        }
    }
    return false;
}

//------------------------------------------------------------------------------

template <class Element, class Compare>
unsigned int UniqueArray<Element,Compare> :: getCount() const{
    int counter=0;
    for(int i=0;i<size;i++){
        if(Array[i]!=nullptr){
            counter++;
        }
    }
    return counter;
}

//------------------------------------------------------------------------------

template <class Element, class Compare>
unsigned int UniqueArray<Element,Compare> :: getSize() const{
    return size;
}

//------------------------------------------------------------------------------

template <class Element, class Compare>
UniqueArray<Element,Compare> UniqueArray<Element,Compare> ::
filter(const Filter& f) const{
    UniqueArray newArray(size);
    for(int i=0;i<size;i++){
        if(f(*Array[i])) {
            newArray.Array[i] = new Element(*(Array[i]));
        }
    }
    return newArray;
}

//------------------------------------------------------------------------------

template<class Element, class Compare>
Element *
UniqueArray<Element, Compare>::findElementByIndex(unsigned int index) const{
    return Array[index];
}

//------------------------------------------------------------------------------

template<class Element, class Compare>
const Element* UniqueArray<Element, Compare>::
constFindElementByIndex(unsigned int index) const{
    return Array[index];
}

//------------------------------------------------------------------------------
template<class Element, class Compare>
void UniqueArray<Element,Compare>::
returnFirstNull(unsigned int& index){
    for(int i=0;i<size;i++){
        if(Array[i] == nullptr) {
            index = i;
            return;
        }
    }
}

//------------------------------------------------------------------------------

#endif //PARKINGLOT_UNIQUEARRAYIMP_H
