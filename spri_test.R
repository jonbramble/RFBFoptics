library(FBFoptics)
library(ggplot2)

#create some isotropic layers
au <- IsoLayer(d=49e-9,eps=-11+1.01i)
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

sprg_plot <- ggplot(spr_curve_df, aes(x=int_angle,y=Rpp))
sprg_plot + geom_line() + xlab("Internal Angle") + ylab("Rpp") + theme_minimal()

max_array <- function(x,y){
  x[which.max(y)]
}

spri <- SPRI(n_entry=1.78)

spri_n <- function(n) {
  mod_amplitude(spri) <- 2.405
  n_exit(spri) <- n
  angle(spri) <- 55.0
  polariser(spri) <- 30
  modulator(spri) <- 30
  analyser(spri) <- 172
  stack_spri <- spri + au
  m <- run(stack_spri)[4]
}

spri_angle <- function(angle) {
  mod_amplitude(spri) <- 2.405
  n_exit(spri) <- 1.34
  angle(spri) <- angle
  polariser(spri) <- 30
  modulator(spri) <- 30
  analyser(spri) <- 172
  stack_spri <- spri + au
  m <- run(stack_spri)[4]
}

spri_pol_an <- function(angle,pol,an) {
  mod_amplitude(spri) <- 2.405
  n_exit(spri) <- 1.34
  angle(spri) <- angle
  polariser(spri) <- pol
  modulator(spri) <- pol
  analyser(spri) <- an
  stack_spri <- spri + au
  m <- run(stack_spri)[4]
}

spri_mod_amp <- function(mod_amp) {
  mod_amplitude(spri) <- mod_amp
  n_exit(spri) <- 1.34
  angle(spri) <- 55.0
  polariser(spri) <- 30
  modulator(spri) <- 30
  analyser(spri) <- 166
  stack_spri <- spri + au
  m <- run(stack_spri)[4]
}

mod_amp_seq = seq(0,5,by=0.005)
md_mod_amp <- sapply(mod_amp_seq ,spri_mod_amp)
mod_amp_df=data.frame(mod_amp_seq,md_mod_amp)
max_array(mod_amp_seq,md_mod_amp)

md_plot <- ggplot(mod_amp_df, aes(x=mod_amp_seq,y=md_mod_amp))
md_plot + geom_line() + xlab("Modulation Amplitude Input") + ylab("Modulation Responsivity") + theme_minimal()

angle_seq= seq(52,56,by=0.01)
md_angle <- sapply(angle_seq,spri_angle)
angle_df=data.frame(angle_seq,md_angle)
max_array(angle_seq,md_angle)

angle_plot <- ggplot(angle_df, aes(x=angle_seq,y=md_angle))
angle_plot + geom_line() + xlab("Incident Angle") + ylab("Modulation Responsivity") + theme_minimal()

n_exit_seq = seq(1.330,1.350,by=0.0001)
md_n_exit <- sapply(n_exit_seq,spri_n)
n_exit_df=data.frame(n_exit_seq,md_n_exit)

n_exit_plot <- ggplot(n_exit_df, aes(x=n_exit_seq,y=md_n_exit))
n_exit_plot + geom_line() + xlab("Exit Refractive Index ") + ylab("Modulation Responsivity") + theme_minimal()

## set a range of values to operator over
arange = seq(54,56,by=0.05)
prange = seq(-90,90,by=1)
anrange = seq(-90,90,by=1)

md_data <- expand.grid(prange,anrange)
output = apply(md_data, 1, function(x,y,z) spri_pol_an(54.8,x[1],x[2]))
md_data$md <- output
ggplot(md_data, aes(x=Var1,y=Var2,fill=md)) + geom_raster() + 
  theme_minimal() + scale_fill_gradient2() + xlab("Polariser") + ylab("Analyser")

md_data_angle <- expand.grid(arange,anprange)
polariser = -45
output = apply(md_data_angle, 1, function(x,y,z) spri_pol_an(x[1],polariser,x[2]))
md_data_angle$md <- output
ggplot(md_data_angle, aes(x=Var1,y=Var2,fill=md)) + geom_raster() + scale_fill_gradient2()  + ylab("Analyser") + xlab("Input Angle")


### OLD CALCULATIONS
#spri <- SPRI(angle=55.1,mod_amplitude=2,,n_exit=1.34,polariser=30,modulator=30,analyser=166)
#stack_spri <- spri + au
#stack_spri_dopc <- spri + au + dopc
#stack_spri_popc <- spri + au + popc
#stack_spri_sm <- spri + au + sm

#run(stack_spri)[4]
#run(stack_spri_dopc)[4]
#run(stack_spri_popc)[4]
#run(stack_spri_sm)[4]