library(FBFoptics)
library(microbenchmark)

s_curve <- SPRG()  #setup an SPR simulations
s_curve@points = 1000
s_curve@end_angle = 60

#create some isotropic layers
au <- IsoLayer(d=49e-9,eps=-11+1.01i)
sam <- IsoLayer(d=2e-9,eps=1.45+0i)



#microbenchmark(
#)

# simply add up those layers, starting with the SPR system
l <- s_curve + au + sam

rpp <- curve(l)
#arrmin = x[match(min(x[,2]),x[,2]),1]
#min(x[,2])

q <- sprmin(l)
v <- rppval(l,q)

print(arrmin)
print(v)
print(q)

#plot results
plot(rpp[,1],rpp[,2],type="l",xlab="Angle",ylab="rpp")


