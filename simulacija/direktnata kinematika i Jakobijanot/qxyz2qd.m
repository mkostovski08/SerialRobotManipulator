function [ qd ] = qxyz2qd( q, xyz )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

    x = xyz(1);
    y = xyz(2);
    z = xyz(3);
    
    xyz_t = q2xyz(q);
    dx = x-xyz_t(1);
    dy = y-xyz_t(2);
    dz = z-xyz_t(3);
    dxyz = [dx dy dz];

    if x == 0
        if y > 0
            theta1 = pi/2;
        elseif y < 0
            theta1 = -pi/2;
        else
            % disp("nezavisno od prvata koordinata")
            theta1 = 0;
        end
    else
        theta1 = atan(y/x);
    end
    theta4 = (pi/2) * (1 - ((x*x+y*y+z*z)/(580*580)));
    
    A1 = (150*cos(q(2)) - 213.3*sin(q(2)+q(3)) - 197.82*sin(q(2)+q(3)+theta4)) * sin(theta1);
    A2 = (- 213.3*sin(q(2)+q(3)) - 197.82*sin(q(2)+q(3)+theta4)) * sin(theta1);
    
    B1 = -150*sin(q(2)) - 213.3*cos(q(2)+q(3)) - 197.82*cos(q(2)+q(3)+theta4);
    B2 = -213.3*cos(q(2)+q(3)) - 197.82*cos(q(2)+q(3)+theta4);
    
    delta = A1*B2 - A2*B1;
    delta2 = dx*B2-A2*dz;
    delta3 = A1*dz-dx*B1;
    
    dtheta2 = delta2/delta;
    dtheta3 = delta3/delta;
    
    theta2 = q(2)+(dtheta2*pi/180);
    theta3 = q(3)+(dtheta3*pi/180);
    qd = [theta1 theta2 theta3 theta4 0];
end


















