/*
 * spr_wrap.cc
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

#include <Rcpp.h>
#include "sprg.h"
#include "sprd.h"
#include "spri.h"

using namespace Rcpp;

void convert_layer(std::vector<IsoLayer>&vlayers, List layers, int layer_count){
  IsoLayer a_layer;
  double layer_d;
  bool layer_fitd;
  
  for(int i=0;i<layer_count;i++)// loop over layers to push into vlayer
  {
    S4 S4layer((SEXP)layers[i]);// get the layer S4 object from the list
       
    layer_d = S4layer.slot("d");//get the data from the slots
    layer_fitd = S4layer.slot("fitd");//get the data from the slots
    
    complex<double> layer_eps = S4layer.slot("eps"); 
    a_layer.seteps(layer_eps);
    
    if(layer_fitd){
      double dstart, dend;
      dstart = S4layer.slot("dstart");  
      dend = S4layer.slot("dend");
      a_layer.setfitd(true);
      a_layer.setdstart(dstart);
      a_layer.setdend(dend);
    }
    else
    {
      a_layer.setfitd(false);
      a_layer.setd(layer_d);
    }
    // check that there is only one fitted layer per stack with a counter
    vlayers[i]=a_layer;
  }
}

void setsim(S4 fullstack, SPRD *spr_simulation){
  
  int layer_count;
  double lambda, n_entry, n_exit, angle, dstart, dend;
  Rcpp::List layers;
  
  lambda = fullstack.slot("lambda");
  n_entry = fullstack.slot("n_entry");
  n_exit = fullstack.slot("n_exit");
  angle = fullstack.slot("angle");
  layers = fullstack.slot("layers");
  
  layer_count = layers.size();
  std::vector<IsoLayer> vlayers(layer_count);   // vector of layers
  convert_layer(vlayers,layers,layer_count);    // r to layer conversion
  
   for(int i=0;i<layer_count;i++)// loop over layers -swaps d data into sprd structure
   {
     if(vlayers[i].getfitd()){
       dstart = vlayers[i].getdstart();
       dend = vlayers[i].getdend();
       spr_simulation->setdstart(dstart);
       spr_simulation->setdend(dend);
     }
     // need to check for more than one layers with fitd true 
   }
  
  spr_simulation->setnlayers(layer_count);
  spr_simulation->setlayers(vlayers);

  spr_simulation->setangle(angle); 
  spr_simulation->setna(n_entry);
	spr_simulation->setnf(n_exit);
	spr_simulation->setlambda(lambda);

  return; 
}

void setsim(S4 fullstack, SPRG *spr_simulation){
  
  int N, layer_count;
  double lambda, n_entry, n_exit, start_angle, end_angle;
  Rcpp::List layers;
  
  N = fullstack.slot("points");
  lambda = fullstack.slot("lambda");
  n_entry = fullstack.slot("n_entry");
  n_exit = fullstack.slot("n_exit");
  start_angle = fullstack.slot("start_angle");
  end_angle = fullstack.slot("end_angle");
  layers = fullstack.slot("layers");
  
  layer_count = layers.size();
  std::vector<IsoLayer> vlayers(layer_count);   // vector of layers
  convert_layer(vlayers,layers,layer_count);    // r to layer conversion
  
  spr_simulation->setnlayers(layer_count);
  spr_simulation->setlayers(vlayers);

  spr_simulation->setstartangle(start_angle); 
	spr_simulation->setendangle(end_angle);
	spr_simulation->setna(n_entry);
	spr_simulation->setnf(n_exit);
	spr_simulation->setlambda(lambda);
  
  return;
}

void setsim(S4 fullstack, SPR *spr_simulation){
  
  int layer_count;
  double lambda, n_entry, n_exit, angle;
  Rcpp::List layers;
  
  lambda = fullstack.slot("lambda");
  n_entry = fullstack.slot("n_entry");
  n_exit = fullstack.slot("n_exit");
  angle = fullstack.slot("angle");
  layers = fullstack.slot("layers");
  
  layer_count = layers.size();
  std::vector<IsoLayer> vlayers(layer_count);   // vector of layers
  convert_layer(vlayers,layers,layer_count);    // r to layer conversion
  
  spr_simulation->setnlayers(layer_count);
  spr_simulation->setlayers(vlayers);

  spr_simulation->setangle(angle); 

	spr_simulation->setna(n_entry);
	spr_simulation->setnf(n_exit);
	spr_simulation->setlambda(lambda);
  
  return; 
}

void setsim(S4 fullstack, SPRI *spr_simulation){
  
  int layer_count;
  double lambda, n_entry, n_exit, angle, modulator,analyser,polariser,mod_amplitude;
  Rcpp::List layers;
  
  lambda = fullstack.slot("lambda");
  n_entry = fullstack.slot("n_entry");
  n_exit = fullstack.slot("n_exit");
  angle = fullstack.slot("angle");
  layers = fullstack.slot("layers");
  modulator = fullstack.slot("modulator");
  analyser = fullstack.slot("analyser");
  polariser = fullstack.slot("polariser");
  mod_amplitude = fullstack.slot("mod_amplitude");
  
  layer_count = layers.size();
  std::vector<IsoLayer> vlayers(layer_count);   // vector of layers
  convert_layer(vlayers,layers,layer_count);    // r to layer conversion
  
  spr_simulation->setnlayers(layer_count);
  spr_simulation->setlayers(vlayers);

  spr_simulation->setangle(angle); 

  spr_simulation->setna(n_entry);
	spr_simulation->setnf(n_exit);
	spr_simulation->setlambda(lambda);
  
  spr_simulation->setmodulator(modulator);
  spr_simulation->setanalyser(analyser);
  spr_simulation->setpolariser(polariser);
  spr_simulation->setdelta(mod_amplitude);
  
  return; 
}

// return the value of rpp only at a chosen angle for the layers specified
// [[Rcpp::export]]
NumericVector S4_SPRVAL(S4 fullstack, NumericVector angle){
  SPR *spr_simulation = new SPR();
  setsim(fullstack, spr_simulation);
  
  double d_angle = (double)angle[0];
  spr_simulation->setangle(d_angle); 
  
  Rcpp::NumericVector y(1);             // create rcpp numeric vector for result
  double result;                        
  
  spr_simulation->sprval();                //more error handling required probabily
	spr_simulation->getval(result);      // this could be more efficient with less unness code execution
  
  delete spr_simulation;  
  y = result;
  return y;
}

// return the full set of data
// [[Rcpp::export]]
NumericVector S4_SPRG(S4 fullstack){
  int N = fullstack.slot("points"); 
  SPRG *spr_simulation = new SPRG(N);     // create simulation with N points
  setsim(fullstack, spr_simulation);      // set parameters
  
  Rcpp::NumericVector y(N);               // create rcpp numeric vector for result
  boost::numeric::ublas::vector<double> result(N); // allocation boost vector for result

	spr_simulation->run();  //more error handling required probabily
	spr_simulation->getdata(result);
    
  delete spr_simulation;  
  y = result;
  return y;
}

// return the full set of data for thickness change at fixed angle
// [[Rcpp::export]]
NumericVector S4_SPRD(S4 fullstack){
  int N = fullstack.slot("points"); 
  SPRD *spr_simulation = new SPRD(N);     // create simulation with N points
  setsim(fullstack, spr_simulation);      // set parameters
    
  Rcpp::NumericVector y(N);               // create rcpp numeric vector for result
  boost::numeric::ublas::vector<double> result(N); // allocation boost vector for result

  spr_simulation->run();  //more error handling required probabily
	spr_simulation->getdata(result);
    
  delete spr_simulation;  
  y = result;
  return y;
}

// return the min angle
// [[Rcpp::export]]
NumericVector S4_SPRMIN(S4 fullstack){
  NumericVector y(1);  
  double result;
  
  SPR *spr_simulation = new SPR();     // create simulation with N points
  setsim(fullstack, spr_simulation);    // set parameters
  
  spr_simulation->sprmin();  //more error handling required probabily
  spr_simulation->getmin(result);
  
  delete spr_simulation;  
  y = result;
  return y;
}

// This part is for a Phase Modulated System, not strictly SPR so could be moved to ellipsometry section
// [[Rcpp::export]]
NumericVector S4_SPRI(S4 fullstack){
  //NumericVector y(3);
  double dc, Rw, R2w;
  
  SPRI *spr_simulation = new SPRI(1);
  setsim(fullstack, spr_simulation);    // set parameters
  
  spr_simulation->run();
  
  dc = spr_simulation->get_dc();  // this is not like the other functions
  Rw = spr_simulation->get_Rw();  // this is not like the other functions
  R2w = spr_simulation->get_R2w();  // this is not like the other functions - pass by ref

  NumericVector results = NumericVector::create(dc,Rw,R2w);
}