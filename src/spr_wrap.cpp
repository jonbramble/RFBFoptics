#include <Rcpp.h>
#include "spr.hpp"
//using namespace Rcpp;

// [[Rcpp::export]]
Rcpp::NumericVector spr(int N, double lambda, double n_entry, double n_exit, double start_angle, double end_angle, Rcpp::List layers) {
    
    Spr *spr_simulation = new Spr(N);  // create simulation
    Rcpp::NumericVector y(N); // create rcpp numeric vector
    boost::numeric::ublas::vector<double> result(N); // allocation boost vector for result
    
    int layer_count = 0;            // initial count zero
    std::vector<Layer> vlayers(0);  // vector of layers
    
    layer_count = layers.size();    // set number of layers from size of layer list
    
    // convert to layers    // could use std::transform 
    for(int i=0;i<layer_count;i++)      // loop over layers to push into vlayer
    {
       //SEXP ll = 
       Rcpp::S4 S4layer((SEXP)layers[i]);            // get the layer S4 object from the list
       
       double layer_d = S4layer.slot("d");  //get the data from the slots
       complex<double> layer_eps = S4layer.slot("eps"); 
       
       Layer a_layer;
       a_layer.seteps(layer_eps);
       a_layer.setd(layer_d);
    
       vlayers.push_back(a_layer);
    }
     
    spr_simulation->setnlayers(layer_count);
	  spr_simulation->setlayers(vlayers);

	  spr_simulation->setstartangle(start_angle); 
	  spr_simulation->setendangle(end_angle);
	  spr_simulation->setna(n_entry);
	  spr_simulation->setnf(n_exit);
	  spr_simulation->setlambda(lambda);

	  spr_simulation->run();  //more error handling required probabily
	  spr_simulation->getdata(result);
    
    delete spr_simulation;  
    
    for(int k=0;k<N;k++){
      y[k]=result[k];
    }
    
    return y;
}