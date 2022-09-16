function hw2()

x0 = fminbnd(@myFun,-pi,pi);

figure; 
x = -pi:.01:pi; 
plot(x,myFun(x));

end


function y = myFun(x);
    y = cos(4*x).*sin(10*x).*exp(-abs(x));
end

