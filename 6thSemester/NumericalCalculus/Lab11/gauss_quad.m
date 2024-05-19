function [I, g_nodes, g_coeff] = gauss_quad(f, n, g_type)
    alpha = zeros(1, n);
    switch g_type
    case 1 #Legendre
        beta = [2, (4-(1:n-1).^(-2).^(-1))];
    case 2 #Chebyshev 1
        beta = [pi, 1/2, 1/4*ones(1, n-2)];
    case 3 #Chebushev 2
        beta = [pi, 1/4*ones(1, n-1)];
    case 4 #Laguerre
        beta = [(1+a), k*(k+a)*ones(1, n-1)];
    case 5 #Hermite
        beta = [sqrt(n), k/2*ones(1, n-1)];
    end
    J = diag(alpha) + diag(sqrt(beta(2:n)), 1) + diag(sqrt(beta(2:n)), -1);
    [v, d] = eig(J);
    g_nodes = diag(d);
    g_coeff = beta(1) * v(1,:).^2;
    I = g_coeff * f(g_nodes);
end