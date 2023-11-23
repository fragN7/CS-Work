s = 5;
alpha = input("Alpha = \n");
miu = 9;
[h, p, ci, zstat] = ztest(x, miu, s, 'alpha', alpha, 'tail', 'left')

fprintf('The value of the statistic = %4.4f \n',zstat);
fprintf('The p value = %4.4f \n',p);

rr = [-inf, norminv(alpha)]
fprintf('Rejection region is (%1.1f, %1.1f) \n', rr);

fptrintf('Part A done\n');

[h,p,ci,tstat] = ttest(x, miu, "alpha", alpha, 'tail', 'right')

n = length(x);

fprintf('the value of the statistic = %4.4f \n',tstat);
fprintf('the p value = %4.4f \n',p);
rr1 = [tinv(1-l, n-1), inf]

fprintf('rejection region is (%1.1f, %1.1f)\n', rr1);
