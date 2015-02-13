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

#sprg_plot <- ggplot(spr_curve_df, aes(x=int_angle,y=Rpp))
#sprg_plot + geom_line() + xlab("Internal Angle") + ylab("Rpp") + theme_minimal()

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

step = 0.1e-9
d_seq= seq(0,20e-9,by=step)
md_d <- sapply(d_seq,spri_d)
d_df=data.frame(d_seq,md_d)

max_array(angle_seq,md_angle)

d_plot <- ggplot(d_df, aes(x=d_seq,y=md_d))
d_plot + geom_line() + xlab("Thickness") + ylab("Modulation Responsivity") + theme_minimal()

md_angle_diff <- diff(md_angle)/step
angle_diff_seq = seq(54+step/2,56,by=step)
angle_diff_df=data.frame(angle_diff_seq,md_angle_diff)
max_array(angle_diff_seq,md_angle_diff)

angle_plot_diff <- ggplot(angle_diff_df, aes(x=angle_diff_seq,y=md_angle_diff))
angle_plot_diff + geom_line() + xlab("Incident Angle") + ylab("Modulation Responsivity") + theme_minimal()

step = 0.0001
n_exit_seq = seq(1.330,1.350,by=step)
md_n_exit <- sapply(n_exit_seq,spri_n)
n_exit_df=data.frame(n_exit_seq,md_n_exit)

n_exit_plot <- ggplot(n_exit_df, aes(x=n_exit_seq,y=md_n_exit))
n_exit_plot + geom_line() + xlab("Exit Refractive Index ") + ylab("Modulation Responsivity") + theme_minimal()

n_exit_diff <- diff(md_n_exit/step)  # to match paper
n_exit_diff_seq = seq(1.330+step/2,1.350,by=step)
n_exit_diff_df=data.frame(n_exit_diff_seq,n_exit_diff)

n_exit_diff_plot <- ggplot(n_exit_diff_df, aes(x=n_exit_diff_seq,y=n_exit_diff))
n_exit_diff_plot + geom_line() + xlab("Exit Refractive Index ") + ylim(c(0,1200)) + ylab("Modulation Responsivity /RIU") + theme_minimal()

## set a range of values to operator over
arange = seq(54,56,by=0.1)
prange = seq(-90,90,by=1)
anrange = seq(-10,10,by=0.1)

md_data <- expand.grid(prange,anrange)
output = apply(md_data, 1, function(x,y,z) spri_pol_an(55.5,x[1],x[2]))
md_data$md <- output
ggplot(md_data, aes(x=Var1,y=Var2,fill=md)) + geom_raster() + 
  theme_minimal() + scale_fill_gradient2() + xlab("Polariser") + ylab("Analyser")

md_data <- expand.grid(prange,anrange)
output = apply(md_data, 1, function(x,y,z) spri_pol_an_dn(pol=x[1],an=x[2]))
md_data$md <- output
ggplot(md_data, aes(x=Var1,y=Var2,fill=md)) + geom_raster() + 
  theme_minimal() + scale_fill_gradient2() + xlab("Polariser") + ylab("Analyser")

md_data_angle <- expand.grid(arange,anrange)
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