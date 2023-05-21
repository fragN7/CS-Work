supplier_a = [1021, 980, 1017, 988, 1005, 998, 1014, 985, 995, 1004, 1030, 1015, 995, 1023]
supplier_b = [1070, 970, 993, 1013, 1006, 1002, 1014, 997, 1002, 1010, 975]
alpha = 0.05

%a

[h, p, ci, stats] = vartest2(supplier_a, supplier_b, "alpha", alpha, 'tail', 'both')

if h == 0
  fprintf('Variances do not differ at 5 significance level \n');
else
  fprintf('Variances differ at the 5 significance level \n');
end


%b

[h, p, ci, stats] = ttest2(supplier_a, supplier_b, 'Vartype', 'unequal', "alpha", alpha)

if h == 0
  fprintf('The suppliers seem to be equally reliable at 5 significance level\n');
else
  fprintf('Supplier A seems to be more reliable at 5 significance level\n');
end
