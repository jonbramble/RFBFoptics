/*
 * sprd.cc
 * Copyright (C) Jonathan Bramble 2014
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

#include "sprd.hpp"

SPRD::SPRD(int N){
  data = boost::numeric::ublas::vector<double>(N);
  cores = std::thread::hardware_concurrency();
  setnpts(N);
}

void SPRD::setnpts(double _N){N = _N;}