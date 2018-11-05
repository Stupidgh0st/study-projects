function f=objective_fun(x)
t=[0.2 0.4 0.6 0.8 1 3 5 7 9 11];
y=[-2.32 -0.73 -0.12 0.65 0.9 3.3 4.12 4.98 5.29 5.9];
n=length(y);
f=0;
for i=1:n
       f=f+(x(1)./t(i)+x(2)-y(i))^2;
end
end