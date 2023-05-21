## Copyright (C) 2022 Alen
##
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <https://www.gnu.org/licenses/>.

## -*- texinfo -*-
## @deftypefn {} {@var{retval} =} C3 (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: Alen <Alen@ALENPC>
## Created: 2022-12-14

function [c1, c2, d1, d2] = C3 (x, alpha)
    ssquared = var(x);
    n = length(x);
    xsquaredalfa = chi2inv(alpha/2, n-1);
    xsquaredalfac = chi2inv(1-alpha/2, n-1);

    % this is for the variance
    c1 =  (n-1)* ssquared / xsquaredalfac
    c2 = (n-1)* ssquared /xsquaredalfa

    % this is for standard deviation
    d1 = sqrt(c1)
    d2 = sqrt(c2)
endfunction
