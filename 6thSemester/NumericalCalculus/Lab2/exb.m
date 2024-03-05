syms x

warning('off');

f = sin(x);

ts3 = taylor(f, x, 0, 'order' , 1);
ezplot(f, [-pi, pi]);

%for k = 2:20
%    T = taylor(f, x, 0, 'order', k);
%    vpa(subs(T,x,pi/5), 6)
%end

for k = 2:20
    T = taylor(f, x, 0, 'order', k);
    vpa(subs(T,x,-pi/3), 6)
end
