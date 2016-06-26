#pragma once
#include <math.h>

#define PI (float)M_PI

template <typename T>
inline T sq( T val )
{
	return val * val;
}


template <typename T> 
T sgn( T val )
{
	return (T)( (T)0 <= val ) - ( val < (T)0 );
}