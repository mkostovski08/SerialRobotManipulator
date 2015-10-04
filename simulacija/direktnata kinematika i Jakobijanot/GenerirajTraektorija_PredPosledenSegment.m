function [dxyz, ddxyz] = GenerirajTraektorija_PredPosledenSegment( xyz1, xyz2, xyz3, dxyz_p, td1, td2 )
%   Ovde se presmetuvaat parametrite na traektorijata za pretposledniot
%   segment od traektorijata.
%   Vleznite parametri na finkcijata se:
%   xyz1 = [x1, y1, z1] pocetna pozicija na segmentot
%   xyz2 = [x2, y2, z2] krajna pozicija na segmentot
%   xyz3 = [x3, y3, z3] e krajna pozicija na sledniot segment
%   dxyz1 = [dx1, dy1, dz1] e pocetnata brzina na pocetokot na prvotot
%   zakrivuvanje
%   td1 e vremetraenjeto na celiot (pretposledniot) segment
%   td2 e vremetraenjeto na sledniot (posledniot) segment
    a = 1000;

    t3 = Presmetaj_t3( xyz2, xyz3, td2, a );
    dxyz_ls2 = Presmetaj_dxyz3( xyz2, xyz3, td2, t3 );
    dxyz_ls1 = Presmetaj_dxyz2( xyz1, xyz2, td1 );
    dxyz_k = (dxyz_ls1 + dxyz_ls2)/2;
    
    ddxyz1 = Presmetaj_ddxyz1( dxyz_p, dxyz_ls1, a );
    ddxyz2 = Presmetaj_ddxyz1( dxyz_ls1, dxyz_ls2, a );
    
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
%   Ovde se presmetuva brzinata vo linearniot del od posledniot segment.
%   Posledniot segment sekogas zavrsuva so brzina ednakva na nula.
    dxyz1 = (xyz2(1) - xyz1(1))/(td - (1/2)*t3(1));
    dxyz2 = (xyz2(2) - xyz1(2))/(td - (1/2)*t3(2));
    dxyz3 = (xyz2(3) - xyz1(3))/(td - (1/2)*t3(3));
    dxyz = [dxyz1 dxyz2 dxyz3];
end


function [ dxyz ] = Presmetaj_dxyz2( xyz2, xyz3, td23 )
%   Ovde se presmetuva vrednosta na brzinata vo linearniot del na
%   segment pomegju dve megjutocki.
    dxyz1 = (xyz3(1) - xyz2(1))/td23;
    dxyz2 = (xyz3(2) - xyz2(2))/td23;
    dxyz3 = (xyz3(3) - xyz2(3))/td23;
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











