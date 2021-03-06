function [f, EDGE] = ada_spdiff_response(angle1,angle2,stride,edge_method,row,col,LN, varargin)

eta = .00001;
% we can save computations by passing a previously computed EDGE for the
% given sigma

% if nargin > 8
%     LN = varargin{3};
% else
%     LN = [];
% end

if nargin > 7
    EDGE = varargin{1};
    [d1 EDGE]   = single_spedge(angle1, stride, edge_method, row, col, LN, EDGE, 'edge');
    [d2]        = single_spedge(angle2, stride, edge_method, row, col, LN, EDGE, 'edge');
    %f = d1 - d2;
    f = (d1 - d2) / (d1 + eta);   % test to see if normalizing helps
else
    I = varargin{1};
    [d1 EDGE]   = single_spedge(angle1, stride, edge_method, row, col, LN, I);
    [d2]        = single_spedge(angle2, stride, edge_method, row, col, LN, EDGE, 'edge');
    %f = d1 - d2;
    f = (d1 - d2) / (d1 + eta);   % test to see if normalizing helps
end