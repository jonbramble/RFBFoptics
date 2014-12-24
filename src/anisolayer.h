/*
 * anisolayer.h
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

#ifndef ANISOLAYER_H_
#define ANISOLAYER_H_

#include "layer.h"

class AnisoLayer : public Layer {
  
  public:
    void setepsx(double _epsx);
		void setepsy(double _epsy);
		void setepsz(double _epsz);
		void settheta(double _theta);
		void setphi(double _phi);

		double getepsx();
		double getepsy();
		double getepsz();
		double gettheta();
		double getphi();
    
  private:   
    double epsx, epsy, epsz, theta, phi;
  
};



#endif