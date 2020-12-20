function [W, bias, Y0] = dnn_mat2gb (W, bias, Y0)
%DNN_MAT2GB convert sparse deep neural network from MATLAB to GraphBLAS
%
% Usage:
%
%   [W, bias, Y0] = dnn_matlab2gb (W, bias, Y0) ;
%
% This is mostly optional since GrB.* methods can take inputs that are either
% GrB objects or MATLAB sparse matrices.  The problem is converted to single
% precision since it gives the same result.  This is a bit faster, but MATLAB
% doesn't have sparse single precision matrices, so a conversion from one to
% the other needs to be made.
%
% The bias{i} matrix differs, and this needs to be modified here (or in
% dnn_matlab.m).  For dnn_matlab.m, bias{i} is a 1-by-n row vector.  For the
% GraphBLAS semiring, it is an n-by-n diagonal matrix.  When comparing GrB.dnn
% and dnn_matlab.m, this code should not be considered extra work, since the
% problem could be generated in GraphBLAS format to begin with.  In that case,
% dnn_matlab.m would include this conversion code, to convert the problem from
% GraphBLAS format to MATLAB sparse matrices.
%
% In any case, the setup time is very low.
%
% See also GrB.dnn, dnn_matlab.

% SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2020, All Rights Reserved.
% SPDX-License-Identifier: Apache-2.0

% fmt = 'by row' ;
fmt = 'sparse/hyper by row' ;

d = struct ('format', fmt) ;
n = size (Y0, 2) ;
Y0 = GrB (Y0, 'single', fmt) ;
for k=1:length(W)
    W {k} = GrB (W {k}, 'single', fmt) ;
    bias {k} = GrB.build (1:n, 1:n, bias {k}, n, n, '+', 'single', d) ;
end

