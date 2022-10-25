function hw3()
[t,y] = ode45(@chem,[0 0.5],[0 1]);

plot(t,y(:,1),'k','LineWidth',1.5);
hold on;
plot(t,y(:,2),'k','LineWidth',1.5);
legend('A','B');
xlabel('Time(s)');
ylabel('Amount of chemical (g)');
title('Chem Reaction');
end

function dydt = chem(t,y)
dydt = zeros(2,1);
dydt(1) = -10*y(1)+50*y(2);
dydt(2) = 10*y(1)-50*y(2);
end