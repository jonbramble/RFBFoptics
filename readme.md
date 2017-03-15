#Description

* Package: FBFoptics
* Type: Package
* Title: 4x4 Optics Calculations
* Version: 0.1
* Date: 2013-07-15
* Author: Jonathan Bramble
* Description: Package to calculate reflectivity and other parameters from
    Surface Plasmon Resonance (SPR) and Evanescent Wave Ellipsometry
    experiments in a prism configuration
    Currently produces spr curves and values for single angles and for a single layer with a thickness change
* License: GPL-3
* Depends:
    * Rcpp (>= 0.10.4)
* LinkingTo: Rcpp

# Notes

The angles used here are internal to the prism. If you want external angles they need to be transformed, but you will need to know the external angle of your prism.

The current code handles n layers with complex refractive index

The exit media index must be real 

SPR is for single values of reflectivity at a fixed angle and also spr minimum searching

SPRG is for a general curve and uses parallel processing

SPRD is for finding the reflectivity with a layer which has a variable thickness parameter and uses parallel processing

SPRI is functions relating to sampling SPR instrumentation - incomplete

SPRAN is for working with anisotropic materials - incomplete

# Usage

### Simple Curve
For a simple curve with a starting angle of 40 and ending angle of 60, with a prism (entry) index of 1.85 and exit index of 1.33

```
library(FBFoptics)  #load the library
sprg <- SPRG()  # setup a SPR simulations
points(sprg) <- 1000  #set the number of points

start_angle(sprg) <- 40  #set the end angle
end_angle(sprg) <- 60  #set the end angle
n_entry(sprg)

#create some isotropic layers
au <- IsoLayer(d=49e-9,eps=-11+1.01i) 
sam <- IsoLayer(d=2e-9,eps=1.45+0i)

# simply add up those layers, starting with the SPR system
stack <- sprg + au     
rpp <- curve(stack)

#plot results
plot(rpp[,1],rpp[,2],type="l",xlab="Angle",ylab="rpp") 
```

### Spot Reflectivities
```
spr <- SPR() 
angle(spr) <- 51
validObject(spr)
stack_spr <- spr + au + sam

min_angle <- sprmin(stack_spr)
v <- rppval(stack_spr,min_angle)
```

### Thickness variation
```
sprd <- SPRD()  #setup an SPR simulations variation over d
points(sprd) <- 8000
angle(sprd) <- 52
protein <- IsoLayer(fitd=TRUE,dstart=0,dend=2e-9,eps=1.45+0i)  #setup the range of values here

dstack <- sprd + au + sam + protein
rpp <- curve(dstack)

plot(rpp,type='l')
```


