function [ dxyz ] = Novo_dxyz( delta_xyz, dxyz1, dxyz2, ddxyz1, ddxyz2, td )
%   Ovde se presmetuva posakuvanata vrednost na brzinata vo linearniot del
%   na segmentot taka sto toj segmentot zapocnuva so tocno opredeleni 
%   brzina dxyz1 i zabrzuvanje ddxyz1 i zavrsuva so tocno opredeleni brzina
%   dxyz2 i zabrzuvanje ddxyz2. Vremetraenjeto na segmentot e td, a
%   pominatoto rastojanie e delta_xyz.
    tmp1 = Presmetaj_dxyz_sr( delta_xyz(1), dxyz1(1), dxyz2(1), ddxyz1(1), ddxyz2(1), td );
    tmp2 = Presmetaj_dxyz_sr( delta_xyz(2), dxyz1(2), dxyz2(2), ddxyz1(2), ddxyz2(2), td );
    tmp3 = Presmetaj_dxyz_sr( delta_xyz(3), dxyz1(3), dxyz2(3), ddxyz1(3), ddxyz2(3), td );
    dxyz = [tmp1, tmp2, tmp3];
end


function [ dxyz_sr ] = Presmetaj_dxyz_sr( delta_xyz, dxyz1, dxyz2, ddxyz1, ddxyz2, td )
%   Ovde se presmetuva posakuvanata vrednost na brzinata vo linearniot del
%   na segmentot taka sto toj segmentot zapocnuva so tocno opredeleni 
%   brzina dxyz1 i zabrzuvanje ddxyz1 i zavrsuva so tocno opredeleni brzina
%   dxyz2 i zabrzuvanje ddxyz2. Vremetraenjeto na segmentot e td, a
%   pominatoto rastojanie e delta_xyz.
%   OVDE MORA DA SE NAPOMENE DEKA FUNKCIJATA E SAMO ZA EDNA KOORDINATA I
%   DOKOLKU SAKAME DA RABOTIME SO POVEKJE OD EDNA KOORDINATA FUNKCIJATA
%   MORA DA SE POVIKUVA POODDELNO ZA SEKOJA KOORDINATA.
    if ddxyz1 == 0
        dxyz_sr = dxyz1;
    elseif ddxyz2 == 0
        dxyz_sr = dxyz2;

    elseif ddxyz1 == ddxyz2
%        disp('A = 0')
        B = td + (dxyz1/ddxyz1) - (dxyz2/ddxyz2);
        C = ((dxyz2*dxyz2)/(2*ddxyz2)) - ((dxyz1*dxyz1)/(2*ddxyz1)) - delta_xyz;
        dxyz_sr = -C/B;
    else
        A = ((1/ddxyz2) - (1/ddxyz1))/2;
        B = td + (dxyz1/ddxyz1) - (dxyz2/ddxyz2);
        C = ((dxyz2*dxyz2)/(2*ddxyz2)) - ((dxyz1*dxyz1)/(2*ddxyz1)) - delta_xyz;
        if B == 0;
            dxyz_sr = sqrt(-C/A);
        elseif B > 0
%            disp('B > 0');
            dxyz_sr = (-B + sqrt(B*B-4*A*C))/(2*A);
        else
%            disp('B < 0');    
            dxyz_sr = (-B - sqrt(B*B-4*A*C))/(2*A);
        end
    end
end

