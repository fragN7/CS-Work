function[x, k] = jacobi(A, b, xo, maxint, err)
    M = diag(diag(A));
    N = M-A; T = inv(M)*N; C = M^(-1)*b;
    alpha = norm(T, inf);
    for k = 1:maxint
        x = T*xo + C;
        if norm(x - xo, inf) < (err * ((1-alpha)/alpha))
            return
        endif
        xo = x;
    endfor
end     

