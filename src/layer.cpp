/*
 * layer.cc
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
#include "layer.hpp"

void Layer::setd(double _d){ d = _d; }
double Layer::getd(){ return d; }

void Layer::setname(char* _name){ name = _name; }
char* Layer::getname(){ return name; }

void Layer::seteps(complex<double> _eps){ eps = _eps; }
std::complex<double> Layer::geteps(){ return eps; }
