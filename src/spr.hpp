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
	void getdata(boost::numeric::ublas::vector<double>& ret_data);
	
	private:
		// layer class? good plan
	void setnpts(double _N);
	double na, nf,sangle, endangle, lambda;
	int N, size;

	boost::numeric::ublas::vector<double> data; // how can i pass the ref to the 'main' data allocation?
	std::vector<Layer> vlayers;
	std::vector<Layer>::iterator iso_it;
	std::vector<boost::numeric::ublas::matrix<complex<double> > > prod_seq;
	
	complex<double> eps;
	double d;
		
		

};



#endif
