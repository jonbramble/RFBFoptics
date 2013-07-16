/*
 * complex_methods.hpp
 * Copyright (C) Jonathan Bramble 2011
 * 
FBF-Optics is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FBF-Optics is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef COMPLEX_METHODS_HPP
#define COMPLEX_METHODS_HPP
 
// names are taken to match those in gsl library for convenience 

#include <complex>

template <class T> std::complex<T> complex_sub_real(const std::complex<T>& a, const T& b){
	return std::complex<T>(real(a)-b,imag(a));	
 }
 
 #endif //COMPLEX_METHODS_HPP
