library(FBFoptics)

delta_shift <- function(val, shift){
  result = val+shift
  if(result < 50){
    result = result + 360
  }
  return(result)
}

#create some isotropic layers
au <- IsoLayer(d=49e-9,eps=-11+1.01i)
dopc <- IsoLayer(d=5e-9,eps=1.450^2+0i)
popc <- IsoLayer(d=5e-9,eps=1.470^2+0i)
sm <- IsoLayer(d=5e-9,eps=1.525^2+0i)
#glass <- IsoLayer(d=0.2e-3,eps=1.5^2+0i)

# simply add up those layers, starting with the SPR system
stack <- sprg + au
rpp <- curve(stack)

#plot results
plot(rpp[,1],rpp[,2],type="l",xlab="Angle",ylab="rpp")

#arrmin = x[match(min(x[,2]),x[,2]),1]
#min(x[,2])

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

ang = seq(50,60,0.01)
delta_vals <- lapply(ang,delta,stack=stack_spr)
delta_vals_n <- lapply(delta_vals,delta_shift,shift=140)
delta(stack_spr,49)

plot(ang,delta_vals_n)
plot(rpp[,1],rpp[,2],type="l",xlab="Angle",ylab="rpp")
abline(h = c(-180,180), v = c(min_angle,min_angle), col = "gray60")

delta(stack_spr,min_angle)






