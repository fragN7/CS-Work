syms x

warning('off');

f = log(1+x);

ls1 = taylor(f, x, 0, 'order', 3);
ls2 = taylor(f, x, 0, 'order', 6);
ezplot(f, [-0.9, 1]);
ezplot(ls1, [-0.9, 1]);
ezplot(ls2, [-0.9, 1]);

fs1 = taylor(log(1-x), x, 0, 'order', 8)

fs2 = taylor(log(1+x), x, 0 , 'order', 8)

res = fs2 - fs1;

res
