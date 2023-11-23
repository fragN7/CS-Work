asup = [1021 980 1017 988 1005 998 1014 985 995 1004 1030 1015 995 1023]
bsup = [1070 970 993 1013 1006 1002 1014 997 1002 1010 975]

alpha = 0.05

[h, p, ci, stats] = vartest2(asup, bsup, alpha, 0)

fprintf('%d\n', h);
fprintf('%f\n', p);
fprintf('%f\n', stats.fstat);
