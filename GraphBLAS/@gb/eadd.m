function Cout = eadd (varargin)
%GB.EADD sparse matrix addition
%
% Usage:
%
%   Cout = gb.eadd (op, A, B, desc)
%   Cout = gb.eadd (Cin, accum, op, A, B, desc)
%   Cout = gb.eadd (Cin, M, op, A, B, desc)
%   Cout = gb.eadd (Cin, M, accum, op, A, B, desc)
%
% gb.eadd computes the element-wise 'addition' T=A+B.  The result T has the
% pattern of the union of A and B. The operator is used where A(i,j) and
% B(i,j) are present.  Otherwise the entries in A and B are copied directly
% into T:
%
%   if (A(i,j) and B(i,j) is present)
%       T(i,j) = op (A(i,j), B(i,j))
%   elseif (A(i,j) is present but B(i,j) is not)
%       T(i,j) = A(i,j)
%   elseif (B(i,j) is present but A(i,j) is not)
%       T(i,j) = B(i,j)
%
% T is then accumulated into C via C<#M,replace> = accum (C,T).
%
% Cin, M, accum, and the descriptor desc are the same as all other
% gb.methods; see gb.mxm and gb.descriptorinfo for more details.  For the
% binary operator, see gb.binopinfo.
%
% See also gb.emult.

[args is_gb] = get_args (varargin {:}) ;
if (is_gb)
    Cout = gb (gbeadd (args {:})) ;
else
    Cout = gbeadd (args {:}) ;
end
