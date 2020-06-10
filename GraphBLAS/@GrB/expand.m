function C = expand (scalar, S, type)
%GRB.EXPAND expand a scalar into a matrix.
% C = GrB.expand (scalar, S) expands the scalar into a matrix with the
% same size and pattern as S, as C = scalar*spones(S).  C has the same
% type as the scalar.  C = GrB.expand (scalar, S, type) allows the type of
% C to be specified.  The numerical values of S are ignored; only the
% pattern of S is used.
%
% Example:
%   A = sprand (4, 4, 0.5)
%   C1 = pi * spones (A)
%   C2 = GrB.expand (pi, A)
%   C3 = GrB.expand (pi, A, 'single complex')
%
% See also GrB.assign.

% SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2020, All Rights
% Reserved. http://suitesparse.com.  See GraphBLAS/Doc/License.txt.

% FUTURE: as much as possible, replace scalar expansion with binary
% operators used in a unary apply, when they are added to
% SuiteSparse:GraphBLAS from the v1.3 C API.

if (isobject (scalar))
    % do not use gb_get_scalar, to keep it sparse
    scalar = scalar.opaque ;
    if (~gb_isscalar (scalar))
% assert(false) ;
        error ('input parameter (%s) must be a scalar', inputname (1)) ;
    end
end

if (isobject (S))
    S = S.opaque ;
end

if (nargin < 3)
    type = gbtype (scalar) ;
end

C = GrB (gb_expand (scalar, S, type)) ;

