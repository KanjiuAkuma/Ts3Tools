/**
  * Created by Joscha Vack on 12/9/2019.
  *
  **/

#ifndef TS3TOOLS_UTIL_H
#define TS3TOOLS_UTIL_H

#include <boost/container/vector.hpp>

template <typename T>
boost::container::vector<T>* asVector(T *arr) {
    boost::container::vector<T>* v = new boost::container::vector<T>(arrayLength(arr));

    for (int i = 0; arr[i]; i++) {
        (*v)[i] = arr[i];
    }
    return v;
}

template <typename T>
int arrayLength(T* arr) {
    int count = 0;
    for (;arr[count]; count++);
    return count;
}

#endif //TS3TOOLS_UTIL_H
