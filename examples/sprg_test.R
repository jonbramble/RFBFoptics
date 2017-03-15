library(FBFoptics)

sprg <- SPRG()  #setup an SPR simulations
points(sprg) <- 5000
end_angle(sprg) <- 60
n_exit(sprg) <- 1.33

au <- IsoLayer(d=49e-9,eps=-11+1.01i)

stack <- sprg + au
rpp <- rpp_curve(stack)

#plot results
plot(rpp[,1],rpp[,2],type="l",xlab="Angle",ylab="rpp")
