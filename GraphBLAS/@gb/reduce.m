function Cout = reduce (varargin)
%GB.REDUCE reduce a matrix to a scalar
%
% Usage:
%
%   cout = gb.reduce (monoid, A)
%   cout = gb.reduce (monoid, A, desc)
%   cout = gb.reduce (cin, accum, monoid, A)
%   cout = gb.reduce (cin, accum, monoid, A, desc)
%
% gb.reduce reduces a matrix to a scalar, using the given monoid.  The
% valid monoids are: '+', '*', 'max', and 'min' for all but the 'logical'
% type, and '|', '&', 'xor', and 'ne' for the 'logical' type.  See 'help
% gb.monoidinfo' for more details.
%
% The monoid and A arguments are required.  All others are optional.  The
% op is applied to all entries of the matrix A to reduce them to a single
% scalar result.
%
% accum: an optional binary operator (see 'help gb.binopinfo' for a list).
%
% cin: an optional input scalar into which the result can be accumulated
%       with cout = accum (cin, result).
%
% See also gb.vreduce; sum, prod, max, min (with the 'all' parameter).

% FUTURE: add complex monoids.

[args is_gb] = get_args (varargin {:}) ;
if (is_gb)
    Cout = gb (gbreduce (args {:})) ;
else
    Cout = gbreduce (args {:}) ;
end
