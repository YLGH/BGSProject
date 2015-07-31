r = 25;
n = 0:62500;
lx = length(n);
x = sin(2*pi*n*1000) + sin(2*pi*n);
x2 = sin(2*pi*n);

%plot(0:lx-1,x,'o')
%hold off
%y = decimate(x,r,82,'fir');
%stem(0:r:lx-1,y,'ro','filled','markersize',4)

hold on

plot(x)
plot(x2)


%legend('Original','Decimated','Location','south')
%xlabel('Sample number')
%ylabel('Signal')

