function [ q ] = get_q(  )
%   So ovaa funkcija se vnesuvaa poetnata pozicija, megjutockite i
%   krajnata pozicija na robotskiot manipulator. Ova e funkcija za
%   upravuvanje vo prostorot na zglobovite pa zatoa poziciite se dadeni vo
%   pozicija na zglobovite na manipulatorot.
    
    q1 = [0 0 0 0 0];
    q2 = [8.1301, -7.0018, -17.4214, 50.5380, 0];
    q3 = [38.6598, -14.4134, -9.6907, 58.7247, 0];
    q4 = [51.3402, -7.0297, -6.3489, 61.9084, 0];
    q5 = [50.1944, 17.4999, -18.6145, 49.2004, 0];
    q6 = [42.4362, 39.0145, -36.2960, 29.8306, 0];
    
    q = [q1; q2; q3; q4; q5; q6];

end

