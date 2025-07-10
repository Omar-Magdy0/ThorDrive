#pragma once
#include "AVR/hal.h"




enum class Platform: uint32_t{
    AVR_Mega328,

};


template<Platform platform>
class IHalTraits{

};

template<typename Derived>
class IUart{

};


template<typename Derived>
class ISpi{

};

template<typename Derived>
class IHal{
    
};

