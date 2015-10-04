function [ xyz ] = qd2xyz( qd )
%   Ovde se vrsi direktnata kinematika na robotskiot manipulator.
    qd = qd .* [-1 -1 1 -1 1 -1];
%    qd = qd*pi/180;
    x = cos(qd(1))*(150*sin(qd(2)) + 213.3*sin(-qd(2)-qd(3)+(pi/2)) + 197.82*sin(-qd(2)-qd(3)-qd(4)+(pi/2)));
    y = sin(qd(1))*(150*sin(qd(2)) + 213.3*sin(-qd(2)-qd(3)+(pi/2)) + 197.82*sin(-qd(2)-qd(3)-qd(4)+(pi/2)));
    z = 150*cos(qd(2)) - 213.3*cos(-qd(2)-qd(3)+(pi/2)) - 197.82*cos(-qd(2)-qd(3)-qd(4)+(pi/2));
    xyz = [x y z];
end

