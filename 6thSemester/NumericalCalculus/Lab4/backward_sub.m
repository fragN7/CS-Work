function x = backward_sub(u, b)
    x = zeros(size(b));
    n = length(b);
    for k = n:-1:1
        x(k) = (b(k) - u(k, k+1:n)*x(k+1:n))/u(k,k);
    endfor
end
    
