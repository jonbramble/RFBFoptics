.libPaths("/home/mbzjpb/R/R_LIBS")
library(FBFoptics)

#create some isotropic layers
au <- IsoLayer(d=49e-9,eps=-11+1.01i)
dopc <- IsoLayer(d=5e-9,eps=1.450^2+0i)
popc <- IsoLayer(d=5e-9,eps=1.470^2+0i)
sm <- IsoLayer(d=5e-9,eps=1.525^2+0i)

sprd <- SPRD()  #setup an SPR simulations variation over d
points(sprd) <- 20000
angle(sprd) <- 52
protein <- IsoLayer(fitd=TRUE,dstart=0,dend=10e-9,eps=1.45+0i)

dstack <- sprd + au + protein
rpp <- curve(dstack)

#save(rpp,file="rpp.Rdata")
