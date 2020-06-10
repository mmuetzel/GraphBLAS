function s = issigned (arg)
%GRB.ISSIGNED Determine if a type is signed or unsigned.
% s = GrB.issigned (type) returns true if type is the string 'double',
% 'single', 'single complex', 'double complex', 'int8', 'int16', 'int32',
% or 'int64'.
%
% s = GrB.issigned (A), where A is a matrix, is the same as
% s = GrB.issigned (GrB.type (A)).
%
% See also GrB/isinteger, GrB/isreal, GrB/isnumeric, GrB/isfloat, GrB.type.

% SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2020, All Rights
% Reserved. http://suitesparse.com.  See GraphBLAS/Doc/License.txt.

if (ischar (arg))
    type = arg ;
elseif (isobject (arg))
% assert(false) ;
    arg = arg.opaque ;
    type = gbtype (arg) ;
else
% assert(false) ;
    type = gbtype (arg) ;
end

s = gb_issigned (type) ;

