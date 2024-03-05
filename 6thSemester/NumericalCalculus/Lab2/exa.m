syms x

warning('off');

f = exp(x);

f1 = taylor(f,x, 0, 'Order', 2);
f2 = taylor(f,x, 0, 'Order', 3);
f3 = taylor(f,x, 0, 'Order', 4);
f4 = taylor(f,x, 0, 'Order', 5);
f5 = taylor(f,x, 0, 'Order', 6);

ezplot(f2, [-pi,pi])
ezplot(f4, [-pi,pi])
ezplot(f5, [-pi,pi])


vpa(exp(1),7)
subs(f1,x,1)
vpa(subs(f4, x, 1), 7)

for k = 6:20
    T=taylor(f,x,0,'Order',k);
    k
    vpa(subs(T,x,1),7)
end