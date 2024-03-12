function[z, t] = double_nodes(x, f, df)
    n = length(x);
    z = repelem(x, 2);
    t = zeros(2 * n);
    t(:, 1) = repelem(f, 2)';
    t(1:2:2*n - 1, 2) = df';
    t(2:2:2*n - 2, 2) = (diff(f)./diff(x))';
    for k = 3:2*n
        t(1:2*n-k+1, k) = diff(t(1:2*n-k+2, k-1))./(z(k:2*n) - z(1:2*n-k+1))';
    end
end
