function x = forward_sub(l, b)
    x = zeros(size(b));
    n = length(b);
    for k = 1:n
        x(k) = (b(k) - l(k, 1:k-1)*x(1:k-1))/l(k,k);
    endfor
end
    
