x = -4:0.1:4;
y = x.^2;

y = y + randn(size(y));
plot(x,y,'.');

p = polyfit(x,y,2);

hold on;

plot(x,polyval(p,x),'r')