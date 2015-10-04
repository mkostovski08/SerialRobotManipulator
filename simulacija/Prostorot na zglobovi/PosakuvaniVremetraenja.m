function [ td ] = PosakuvaniVremetraenja( q )
%   Ovde se presmetuva posakuvanoto vremetraenje td na daden segment kako
%   rastojanie pomegju tockite pomnozeno so odredena konstanta. Taa
%   konstanta ja definira brzinata na dvizenje na robotot.

    koef = 1/25;
    s = size(q);
    td = [];
    for i = 1:(s(1)-1);
        td = [td PosakuvanoVremetraenje(q(i, :), q(i+1, :))];
    end
    td = td*koef;
end


function [ td ] = PosakuvanoVremetraenje( qi, qj )
%   Ovde se presmetuva rastojanieto pomegju tockite xyzi i xyzj
    td = sqrt(((qi(1)-qj(1))^2) + ((qi(2)-qj(2))^2) + ((qi(3)-qj(3))^2));
end

