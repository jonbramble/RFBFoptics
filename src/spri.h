/*
 * spri.h
 * Copyright (C) Jonathan Bramble 2015
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
 
#ifndef SPRI_H
#define SPRI_H

#include "spr.h"
#include <thread>
#include <mutex>

class SPRI : public SPR {
  // this class calculates the dc, rw, r2w values for the custom camera - this could go in the ellipsometry package
  
  public:
  
  SPRI(int N);
  
  //int N, cores; // single thread for now

  // inputs M, A angles, Amplitude of phase modulation
  // outputs DC, 1f, 2f  
  double get_dc();
  double get_Rw();
  double get_R2w();
  
  void setanalyser(double _A);
  void setmodulator(double _M);
  void setpolariser(double _P);
  void setdelta(double _D);
  
  void run();
  
  private:
  
  double dc, Rw, R2w;
  
  double Rp, Rs, rpr, rpi, rsr, rsi, Mr, Rpc2, Rss2;
  
  double phia;
  
  double A, M, P, Delta;
  
  void setreflectivities();
  
  void DC_phia();
  void Rw_phia();
  void R2w_phia();  
  
  double bessel_j(int v, double x);
  
};

#endif
