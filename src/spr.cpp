/*
 * spr.cc
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


#include "spr.hpp"

Spr::Spr(){
	data = boost::numeric::ublas::vector<double>(100);
	setnpts(100);// set defaults
}

Spr::Spr(int N){
	data = boost::numeric::ublas::vector<double>(N);
	setnpts(N);
}

void Spr::setnpts(double _N){N = _N;}
void Spr::setna(double _na){na = _na;}
void Spr::setstartangle(double _sangle){sangle = _sangle;}
void Spr::setendangle (double _endangle){endangle = _endangle;}
void Spr::setnf(double _nf){nf = _nf;}
void Spr::setnlayers(double _size){size = _size;}
void Spr::setlayers(std::vector<Layer> _layers){   // must check these have been called
	vlayers = _layers;
}		
	
void Spr::setlambda(double _lambda){lambda = _lambda;}

void Spr::getdata(boost::numeric::ublas::vector<double>& ret_data){
	ret_data=data;
}

//A threaded version of run
void Spr::run_parallel(){
  
}

//this should find the spr minimum
void Spr::sprmin(){
  
}

void Spr::run()
{
	//make tests - need a argument testing package
	static const double s_pi = static_cast<double>(3.141592653589793238462643383279502884197L);

	matrix<complex<double> > T(4,4), ILa(4,4), Lf(4,4), Tli(4,4);
	identity_matrix<complex<double> > Id(4,4);

	complex<double>	result, zcphif2, phif, cphif;

	double end_angle_rad = endangle*(s_pi/180);
	double start_angle_rad = sangle*(s_pi/180);
	double range_rad = end_angle_rad-start_angle_rad;

	double phia, cphia, eta;
	double k0 = (2*s_pi)/lambda; // laser wavevector
	int k;
	
	// need some kind of generalised loop - will always have N points
	for(k=0;k<N;k++)
	{	
		phia = start_angle_rad+k*(range_rad/N); //input angle

		cphia = cos(phia); 
		eta = na*sin(phia); // x comp of wavevector
		zcphif2 = complex<double>(1-pow((na/nf)*sin(phia),2),0);  // this always picks the correct sector
		cphif = sqrt(zcphif2);
		
		incmat(na,cphia,ILa);
		extmat(nf,cphif,Lf);
		
		prod_seq.push_back(ILa); 
		for ( iso_it=vlayers.begin() ; iso_it<vlayers.end(); iso_it++ ){//iterate over elements
			eps = iso_it->geteps();
			d = iso_it->getd();
			gtmiso(eps,k0,eta,-1*d,Tli);
			prod_seq.push_back(Tli);
		}
		prod_seq.push_back(Lf); //add at end

		total_trans(prod_seq, T);
	
		prod_seq.clear();

		data(k) = rpp(T);    // need to choose data rpp rps etc
	}
}
