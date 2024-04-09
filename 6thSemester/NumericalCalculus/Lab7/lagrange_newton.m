function f = lagrange_newton(xi, d, x)
    for k = 1:length(x)
        y = x(k) - xi;
        f(k) = d(1, :) * [1, cumprod(y(1:length(y)-1))]';
    end
endfunction