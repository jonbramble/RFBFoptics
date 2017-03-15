/*
 * sprg.cc
 * Copyright (C) Jonathan Bramble 2014
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

#include "sprg.h"

SPRG::SPRG(int N){
  data = boost::numeric::ublas::vector<double>(N);
  cores = std::thread::hardware_concurrency();
  setnpts(N);
}

void SPRG::setstartangle(double _sangle){sangle = _sangle;}
void SPRG::setendangle (double _endangle){endangle = _endangle;}
void SPRG::setnpts(double _N){N = _N;}

void SPRG::getdata(boost::numeric::ublas::vector<double>& ret_data){ret_data=data;}

void SPRG::run_rpp(){
  auto f_rpp = bind(&SPRG::Rpp_phia_w,this,_1);                 //bind the member function to calc Rpp
  val_array(f_rpp);                                             //run threaded calcs
}

void SPRG::run_delta(){
  auto f_delta = bind(&SPRG::delta_phia_w,this,_1);             //bind the member function to calc delta
  val_array(f_delta);
}

void SPRG::val_array(function<double(double)> param){ 
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
    threads.push_back( std::thread(&SPRG::val_segments, this, param, start, end) );
  }
  
  for (std::thread& t : threads)  // new range-based for:
    t.join();                     // runs those threads
}

void SPRG::val_segments(function<double(double)> param, int start, int end){
  int k; 
  double phia, result;
  for(k=start;k<end;k++){
    phia = start_angle_rad+k*(range_rad/N); //input angle
    result = param(phia);     // calls function param here to calculate desired value
    mu.lock();                // lock here for writing to data
     data(k) = result;
    mu.unlock();
  }
}

//wrapper function
double SPRG::Rpp_phia_w(double phia){
  return Rpp_phia(phia);
}

double SPRG::delta_phia_w(double phia){
  return delta_phia(phia);
}


