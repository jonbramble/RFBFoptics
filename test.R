library(FBFoptics)
#library(microbenchmark)
sprg <- SPRG()  #setup an SPR simulations
points(sprg) <- 5000
end_angle(sprg) <- 60

#create some isotropic layers
au <- IsoLayer(d=49e-9,eps=-11+1.01i)
dopc <- IsoLayer(d=5e-9,eps=1.450^2+0i)
popc <- IsoLayer(d=5e-9,eps=1.470^2+0i)
sm <- IsoLayer(d=5e-9,eps=1.525^2+0i)
#glass <- IsoLayer(d=0.2e-3,eps=1.5^2+0i)

# simply add up those layers, starting with the SPR system
stack <- sprg + au + dopc
rpp <- curve(stack)

spri <- SPRI()
angle(spri) <- 55.1
mod_amplitude(spri) <- 2
sim <- spri + au + dopc
run(sim)

#plot results
plot(rpp[,1],rpp[,2],type="l",xlab="Angle",ylab="rpp")

arrmin = x[match(min(x[,2]),x[,2]),1]
min(x[,2])

# for single points use SPR
spr <- SPR() 
spr@n_entry <- 1.78
validObject(spr)

stack_spr <- spr + au
stack_spr_dopc <- spr + au + dopc
stack_spr_popc <- spr + au + popc
stack_spr_sm <- spr + au + sm

min_angle <- sprmin(stack_spr)
min_angle
sprmin(stack_spr_dopc)
sprmin(stack_spr_popc)
sprmin(stack_spr_sm)

q <- rppval(stack_spr,min_angle)
q_dopc <- rppval(stack_spr_dopc,min_angle)
q_popc <- rppval(stack_spr_popc,min_angle)
q_sm <- rppval(stack_spr_sm,min_angle)

sprd <- SPRD()  #setup an SPR simulations variation over d
points(sprd) <- 8000
angle(sprd) <- 52
protein <- IsoLayer(fitd=TRUE,dstart=0,dend=2e-9,eps=1.45+0i)

dstack <- sprd + au + sam + protein
rpp <- curve(dstack)

plot(rpp,type='l')

