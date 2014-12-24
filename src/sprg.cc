/*
 * sprg.cc
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

#include "sprg.hpp"

SPRG::SPRG(int N){
  data = boost::numeric::ublas::vector<double>(N);
  cores = std::thread::hardware_concurrency();
  setnpts(N);
}

void SPRG::setstartangle(double _sangle){sangle = _sangle;}
void SPRG::setendangle (double _endangle){endangle = _endangle;}
void SPRG::setnpts(double _N){N = _N;}

void SPRG::getdata(boost::numeric::ublas::vector<double>& ret_data){ret_data=data;}

void SPRG::run(){rpp_array();}

void SPRG::rpp_array(){ 
  std::vector<std::thread> threads;  //parallel processing part
  
  int parts = N / cores;
  int extra = N % cores;
  int start, end;
  
  end_angle_rad = endangle*(s_pi/180);
  start_angle_rad = sangle*(s_pi/180);
  range_rad = end_angle_rad-start_angle_rad;

  for (int i=0; i<cores; ++i) // 1 per core:
  {
    start = i*parts;
    end = (i+1)*parts;
    if(i==cores-1)
      end += extra;
    threads.push_back( std::thread(&SPRG::rpp_segments, this, start, end) );
  }

  for (std::thread& t : threads) // new range-based for:
   t.join(); // runs those threads
}

void SPRG::rpp_segments(int start, int end){
  int k; 
  double phia, result;
  for(k=start;k<end;k++){
    phia = start_angle_rad+k*(range_rad/N); //input angle
    result = rpp_phia(phia);
    mu.lock(); // lock here for writing to data
     data(k) = result;
    mu.unlock();
  }
}
