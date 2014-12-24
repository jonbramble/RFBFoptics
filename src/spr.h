/*
 * spr.h
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
#ifndef SPR_H
#define SPR_H

// now only has responsibility of single value calculations, all vector based calculations to be handled by child classes

#include <boost/math/complex/asin.hpp>
#include <boost/math/constants/constants.hpp>

#include "fbfoptics.h"
#include "isolayer.h"
#include "anisolayer.h"

class SPR: public Fbfoptics {
		
		public:
		
		  SPR();
		
		  void setna( double _na);
		  void setnf( double _nf);
		  void setnlayers(double _size);
		  void setlayers(std::vector<IsoLayer> _layers);
		  void setlambda(double _lambda);
		  void setangle(double _angle);
      double getangle();
		
		  void sprmin();
		  void sprval();
		  void getmin(double& min);
		  void getval(double& val);
		
		protected:
		
		  double s_pi, angle;
		  double rpp_phia(double phia);
      double rpp_phia(double phia, double d);
		
		private:
		
		  int size;
		
		  double na, nf, lambda, min, val;
		  double rpp_p1(double phia);
		  double rpp_p2(double phia);
		
		  std::vector<IsoLayer> vlayers;
  
};



#endif
