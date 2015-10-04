function [dxyz, ddxyz] = GenerirajTraektorija_VtorSegment( xyz1, xyz2, xyz3, dxyz_p, td1, td2 )
%   Ovde se presmetuvaat parametrite na traektorijata za segmentot pomegju
%   dve megjutocki, osven pretposledniot segment.
%   Vleznite parametri na finkcijata se:
%   xyz1 = [x1, y1, z1] pocetna pozicija na segmentot
%   xyz2 = [x2, y2, z2] krajna pozicija na segmentot
%   xyz3 = [x3, y3, z3] e krajna pozicija na sledniot segment
%   dxyz1 = [dx1, dy1, dz1] e pocetnata brzina na pocetokot na prvoto
%   zakrivuvanje
%   td1 e vremetraenjeto na celiot segment
%   td2 e vremetraenjeto na sledniot segment
    a = 1000;


    dxyz_ls = Presmetaj_dxyz2( xyz1, xyz2, td1 );
    dxyz_ls2 = Presmetaj_dxyz2( xyz2, xyz3, td2 );
    dxyz_k = (dxyz_ls + dxyz_ls2)/2;
    
    ddxyz1 = Presmetaj_ddxyz1( dxyz_p, dxyz_ls, a );
    ddxyz2 = Presmetaj_ddxyz1( dxyz_ls, dxyz_k, a );

    ddxyz = [ddxyz1; ddxyz2];
    dxyz_sr = Novo_dxyz((xyz2-xyz1), dxyz_p, dxyz_k, ddxyz1, ddxyz2, td1);
    dxyz = [dxyz_p; dxyz_sr; dxyz_k];

end


function [ dxyz ] = Presmetaj_dxyz2( xyz2, xyz3, td23 )
%   Ovde se presmetuva vrednosta na brzinata vo linearniot del na
%   segment pomegju dve megjutocki.
    dxyz1 = (xyz3(1) - xyz2(1))/td23;
    dxyz2 = (xyz3(2) - xyz2(2))/td23;
    dxyz3 = (xyz3(3) - xyz2(3))/td23;
    dxyz = [dxyz1 dxyz2 dxyz3];
end


function [ ddxyz ] = Presmetaj_ddxyz1( dxyz1, dxyz2, a )
%   Ovde se presmetuva zabrzuvanjeto ddxyz zaedno so negoviot predznak vo
%   zakrivuvanjeto na segmentot pri pocetna brzina ednakva na dxyz1 i
%   krajna brzina ednakva na dxyz2. Amplitudata na zabrzuvanjeto e poznata
%   i e ednakva na a.
    ddxyz1 = sign(dxyz2(1)-dxyz1(1))*a;
    ddxyz2 = sign(dxyz2(2)-dxyz1(2))*a;
    ddxyz3 = sign(dxyz2(3)-dxyz1(3))*a;
    ddxyz = [ddxyz1 ddxyz2 ddxyz3];
end


















