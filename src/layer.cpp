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

void Layer::setepsx(double _epsx){ epsx = _epsx; }
double Layer::getepsx(){ return epsx; }

void Layer::setepsy(double _epsy){ epsy = _epsy; }
double Layer::getepsy(){ return epsy; }

void Layer::setepsz(double _epsz){ epsz = _epsz; }
double Layer::getepsz(){ return epsz; }

void Layer::settheta(double _theta){ theta = _theta; }
double Layer::gettheta(){ return theta; }

void Layer::setphi(double _phi){ phi = _phi; }
double Layer::getphi(){ return phi; }

void Layer::setiso(bool _is_iso){ is_iso = _is_iso; }
bool Layer::getiso(){ return is_iso; }
