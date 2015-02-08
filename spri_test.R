library(FBFoptics)

#create some isotropic layers
au <- IsoLayer(d=49e-9,eps=-11+1.01i)
dopc <- IsoLayer(d=5e-9,eps=1.450^2+0i)
popc <- IsoLayer(d=5e-9,eps=1.470^2+0i)
sm <- IsoLayer(d=5e-9,eps=1.525^2+0i)

# loop over the index to calc mod depth - should this be -ve ?
arange = seq(1.330,1.350,by=0.0001)
md = array(dim=length(arange))
k=1
for (n in arange)
{
  spri <- SPRI(mod_amplitude=2,n_exit=n,polariser=30,modulator=30,analyser=166)
  angle(spri) <- 55.0
  stack_spri <- spri + au
  m <- run(stack_spri)[4]
  md[k] <- m
  k=k+1
}
plot(arange,md)


spri <- SPRI(angle=55.1,mod_amplitude=2)
stack_spri <- spri + au
stack_spri_dopc <- spri + au + dopc
stack_spri_popc <- spri + au + popc
stack_spri_sm <- spri + au + sm
run(stack_spri)[4]
run(stack_spri_dopc)[4]
run(stack_spri_popc)[4]
run(stack_spri_sm)[4]

# loop over the angles to calc mod depth - should this be -ve ?
spri <- SPRI(mod_amplitude=2,polariser=30,modulator=30,analyser=166)
arange = seq(52,56,by=0.01)
md = array(dim=length(arange))
k=1
for (n in arange)
{
  angle(spri) <- n
  stack_spri <- spri + au
  m <- run(stack_spri)[4]
  md[k] <- m
  k=k+1
}
plot(arange,md)