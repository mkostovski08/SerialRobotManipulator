function [dxyz, ddxyz] = GenerirajTraektorija_PosledenSegment( xyz1, xyz2, dxyz_p, td1 )
%   Ovde se presmetuvaat parametrite na traektorijata za segmentot pomegju
%   poslednata megjutocka i krajnata tocka od traektorijata.
%   Vleznite parametri na finkcijata se:
%   xyz1 = [x1, y1, z1] pocetna pozicija na segmentot
%   xyz2 = [x2, y2, z2] krajna pozicija na segmentot
%   dxyz1 = [dx1, dy1, dz1] e pocetnata brzina na pocetokot na prvotot
%   zakrivuvanje
%   td1 e vremetraenjeto na celiot (posledniot) segment
    a = 1000;

    t3 = Presmetaj_t3( xyz1, xyz2, td1, a );
    dxyz_ls1 = Presmetaj_dxyz3( xyz1, xyz2, td1, t3 );
    dxyz_k = [0 0 0];
    
    ddxyz1 = Presmetaj_ddxyz1( dxyz_p, dxyz_ls1, a );
    ddxyz2 = Presmetaj_ddxyz1( dxyz_ls1, dxyz_k, a );
    
    dxyz_sr = Novo_dxyz ((xyz2-xyz1), dxyz_p, dxyz_k, ddxyz1, ddxyz2, td1);
    
    dxyz = [dxyz_p; dxyz_sr; dxyz_k];
    ddxyz = [ddxyz1; ddxyz2];
end


function [ t ] = Presmetaj_t3( xyz3, xyz4, td23, a )
%   Odve se presmetuva vremetraenjeto na vtoroto zakrivuvanje t na
%   posledniot segment sto zavrsuva so krajna brzina 0
%   zabrzuvanjeto e konstantno i ednakvo na a
    t1 = td23 - sqrt(td23*td23-(2*(xyz4(1) - xyz3(1)))/a);
    t2 = td23 - sqrt(td23*td23-(2*(xyz4(2) - xyz3(2)))/a);
    t3 = td23 - sqrt(td23*td23-(2*(xyz4(3) - xyz3(3)))/a);
    t = [t1 t2 t3];
end


function [ dxyz ] = Presmetaj_dxyz3( xyz1, xyz2, td, t3 )
%   Ovde se presmetuva brzinata vo linearniot del na posledniot segment.
%   Posledniot segment zavrsuva so brzina ednakva na 0.
    dxyz1 = (xyz2(1) - xyz1(1))/(td - (1/2)*t3(1));
    dxyz2 = (xyz2(2) - xyz1(2))/(td - (1/2)*t3(2));
    dxyz3 = (xyz2(3) - xyz1(3))/(td - (1/2)*t3(3));
    dxyz = [dxyz1 dxyz2 dxyz3];
end


function [ ddxyz ] = Presmetaj_ddxyz1( xyz1, xyz2, a )
%   Ovde se presmetuva zabrzuvanjeto ddxyz zaedno so negoviot predznak vo
%   vtoroto zakrivuvanje na posledniot segment pri krajna brzina ednakva na
%   0. Amplitudata na zabrzuvanjeto e poznata i e ednakva na a
    a1 = a; a2 = a; a3 = a;
    ddxyz1 = sign(xyz2(1)-xyz1(1))*a1;
    ddxyz2 = sign(xyz2(2)-xyz1(2))*a2;
    ddxyz3 = sign(xyz2(3)-xyz1(3))*a3;
    ddxyz = [ddxyz1 ddxyz2 ddxyz3];
end

