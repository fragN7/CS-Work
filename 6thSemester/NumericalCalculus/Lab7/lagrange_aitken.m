function x = lagrange_aitken(xi, fi, x)
    n = length(xi);
    p = zeros(n);
    for i = 1:n
        p(i,1) = fi(i);
        for j = 1:i-1
            p(i, j+1) = ((x-xi(j))* p(i,j) - (x- xj(i)) * p(j,j)) / (xi(i)-xi(j));
        end
    end
endfunction