function x = gauss_pivot(a, b)
    x = zeros(size(b));
    [r, n] = size(a);
    a = [a, b];
    
    for j = 1:n-1
        [u, p] = max(abs(a(j:n, j)))
        
        a([j, p+j-1], :) = a([p+j-1, j], :)
        
        for i = j+1:r
            m = a(i, j)/a(j, j);
            a(i, :) = a(i, :) - m*a(j, :)
        endfor
    endfor
    x = backward_sub(a(:,1:n), a(:, n+1))
end
    