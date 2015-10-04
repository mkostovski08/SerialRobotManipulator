function [ td ] = PosakuvaniVremetraenja( xyz )
%   Ovde se presmetuva posakuvanoto vremetraenje td na daden segment kako
%   rastojanie pomegju tockite pomnozeno so odredena konstanta. Taa
%   konstanta ja definira brzinata na dvizenje na robotot.

    koef = 1/50;
    s = size(xyz);
    td = [];
    for i = 1:(s(1)-1);
        td = [td PosakuvanoVremetraenje(xyz(i, :), xyz(i+1, :))];
    end
    td = td*koef;
end


function [ td ] = PosakuvanoVremetraenje( xyzi, xyzj )
%   Ovde se presmetuva rastojanieto pomegju tockite xyzi i xyzj
    td = sqrt(((xyzi(1)-xyzj(1))^2) + ((xyzi(2)-xyzj(2))^2) + ((xyzi(3)-xyzj(3))^2));
end

