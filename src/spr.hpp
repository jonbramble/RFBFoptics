/*
 * spr.hpp
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
#ifndef SPR_H
#define SPR_H

#include <boost/math/complex/asin.hpp>
#include <thread>
#include <mutex>

#include "fbfoptics.hpp"
#include "layer.hpp"

class Spr: public Fbfoptics {
		
	public:
	Spr();
	Spr(int N);
	
	void setstartangle(double _sangle);
	void setendangle (double _endangle);
	void setna( double _na);
	void setnf( double _nf);
	void setnlayers(double _size);
	void setlayers(std::vector<Layer> _layers);
	void setlambda(double _lambda);
	
  void run();
  void sprmin();
  
  void rpp_array();
  
	void getdata(boost::numeric::ublas::vector<double>& ret_data);
	
	private:

	void setnpts(double _N);
	double na, nf, sangle, endangle, lambda, end_angle_rad, start_angle_rad, range_rad;
  
	int N, size;
  std::mutex mu;
  
  void rpp_segments(int, int);
  double rpp_phia(double phia);

	boost::numeric::ublas::vector<double> data;
	std::vector<Layer> vlayers;

};



#endif
