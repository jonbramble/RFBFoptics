library(ggplot2)
sprg <- SPRG(n_entry=3.9,n_exit=1.33,start_angle=50,end_angle=90,points=5000) 

#al <- IsoLayer(d=50e-9,eps=-51+18i)
al <- IsoLayer(d=50e-9,eps=-34+0.9i)
au <- IsoLayer(d=50e-9,eps=-11+1.01i)

stack <- sprg + al

spr_curve_df <- data.frame(curve(stack))

sprg_plot <- ggplot(spr_curve_df, aes(x=int_angle,y=Rpp))
sprg_plot + geom_line() + xlab("Internal Angle") + ylab("Rpp") + theme_minimal()
