/*
 * anisolayer.cc
 * Copyright (C) Jonathan Bramble 2011
 * 
 * FBF-Optics is free software: you can redistribute it and/or modify it
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

#include "anisolayer.h"

void AnisoLayer::setepsx(double _epsx){ epsx = _epsx; }
double AnisoLayer::getepsx(){ return epsx; }

void AnisoLayer::setepsy(double _epsy){ epsy = _epsy; }
double AnisoLayer::getepsy(){ return epsy; }

void AnisoLayer::setepsz(double _epsz){ epsz = _epsz; }
double AnisoLayer::getepsz(){ return epsz; }

void AnisoLayer::settheta(double _theta){ theta = _theta; }
double AnisoLayer::gettheta(){ return theta; }

void AnisoLayer::setphi(double _phi){ phi = _phi; }
double AnisoLayer::getphi(){ return phi; }