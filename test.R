library(FBFoptics)
#library(microbenchmark)
sprg <- SPRG()  #setup an SPR simulations
sprg@points = 1000
sprg@end_angle = 60

#create some isotropic layers
au <- IsoLayer(d=49e-9,eps=-11+1.01i)
sam <- IsoLayer(d=2e-9,eps=1.45+0i)

# simply add up those layers, starting with the SPR system
stack <- sprg + au + sam
rpp <- curve(stack)

#arrmin = x[match(min(x[,2]),x[,2]),1]
#min(x[,2])

# for single points use SPR
spr <- SPR() 
spr@angle = 50
stack_spr <- spr + au + sam

min_angle <- sprmin(stack_spr)
v <- rppval(stack_spr,min_angle)

#plot results
plot(rpp[,1],rpp[,2],type="l",xlab="Angle",ylab="rpp")

sprd <- SPRD()  #setup an SPR simulations variation over d
sprd@points = 5000
sprd@angle = 54
protein <- IsoLayer(fitd=TRUE,dstart=0,dend=2e-9,eps=1.45+0i)

dstack <- sprd + au + sam + protein
rpp <- curve(dstack)

plot(rpp,type='l')

