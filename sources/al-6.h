#pragma once
#include <iostream>
#include <fstream>
#include "Exceptions.h"



using namespace std;


template <typename To, typename From>
To container_cast(From && from) {
    
    return To(begin(from), end(from));
}
