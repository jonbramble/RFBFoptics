library(FBFoptics)
library(ggplot2)

#create some isotropic layers
au <- IsoLayer(d=50e-9,eps=-11+1.01i)
dopc <- IsoLayer(d=5e-9,eps=1.450^2+0i)
popc <- IsoLayer(d=5e-9,eps=1.470^2+0i)
sm <- IsoLayer(d=5e-9,eps=1.525^2+0i)

## Check the SPR minimum
spr <- SPR(n_entry=1.78,n_exit=1.34) 
stack_spr <- spr + au
min_angle <- sprmin(stack_spr)
print(min_angle)

## Plot the SPR curve
sprg <- SPRG(n_entry=1.78,n_exit=1.34) 
stack <- sprg + au
spr_curve_df <- data.frame(curve(stack))

sprg_plot <- ggplot(spr_curve_df, aes(x=int_angle,y=Rpp)) + geom_line() + xlab("Internal Angle") + ylab("Rpp") + theme_minimal()

max_array <- function(x,y){
  x[which.max(y)]
}

spri <- SPRI(n_entry=1.78)
adlayer <- IsoLayer(d=5e-9,eps=1.45^2+0i)
d(adlayer) <- 1e-9

spri_d <- function(t) {
  mod_amplitude(spri) <- 2.405
  n_exit(spri) <- 1.33
  angle(spri) <- 55.5
  polariser(spri) <- 43
  modulator(spri) <- 43
  analyser(spri) <- 176.8
  d(adlayer) <- t
  stack_spri <- spri + au + adlayer
  m <- run(stack_spri)[4]
}

