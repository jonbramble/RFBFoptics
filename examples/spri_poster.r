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
sprg <- SPRG(n_entry=1.78,n_exit=1.34, points=1000) 

stack <- sprg + au
spr_curve_au_df <- data.frame(curve(stack))
spr_curve_au_df$Experiment = "Au 50nm"

stack <- sprg + au + popc
spr_curve_popc_df <- data.frame(curve(stack))
spr_curve_popc_df$Experiment = "POPC (5nm)"

stack <- sprg + au + dopc
spr_curve_dopc_df <- data.frame(curve(stack))
spr_curve_dopc_df$Experiment = "DOPC (5nm)"

df_all <- rbind(spr_curve_au_df,spr_curve_popc_df,spr_curve_dopc_df)

xlab <- expression(paste("Internal Angle (",degree,")"))

sprg_plot <- ggplot(df_all, aes(x=int_angle,y=Rpp, color=Experiment, group=Experiment))
sprg_plot + geom_line() + xlab(xlab) + ylab("Reflectivity (Rpp)") + theme_minimal(base_size=22)



