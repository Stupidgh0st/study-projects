function dxdy=ode(x,y)
dxdy=[y(2);5*x*exp(x)-y(1)+2*y(2)];