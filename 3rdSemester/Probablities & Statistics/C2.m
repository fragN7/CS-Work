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
## @deftypefn {} {@var{retval} =} C2 (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: Alen <Alen@ALENPC>
## Created: 2022-12-14

function [m3, m4] = C2 (x, alpha)
    xmean = mean(x);
    n = length(x);
    s = std(x);
    m3 = xmean - s/sqrt(n)*tinv(1-alpha/2, n-1)
    m4 = xmean + s/sqrt(n)*tinv(1-alpha/2, n-1)
endfunction
