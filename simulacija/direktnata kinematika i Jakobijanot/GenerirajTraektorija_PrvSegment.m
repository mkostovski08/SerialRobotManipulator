function [dxyz, ddxyz] = GenerirajTraektorija_PrvSegment( xyz1, xyz2, xyz3, td1, td2 )
%   Ovde se presemetuvaat parametrite na traektorijata samo za prviot
%   segment ako ni se dadeni pocetnata pozicija, prvata megjutocka,
%   vtorata megjutocka, posakuvanoto vremetraenje na prviot segment i
%   posakuvanoto vremetraenje vtoriot segment.
    a = 1000;

    [ ddxyz1 ] = Presmetaj_ddxyz1( xyz1, xyz2, a );
    [ t1 ] = Presmetaj_t1( xyz1, xyz2, td1, a );
    [ dxyz1 ] = Presmetaj_dxyz1( xyz1, xyz2, td1, t1 );
    [ dxyz2 ] = Presmetaj_dxyz2( xyz2, xyz3, td2 );
    [ ddxyz2 ] = Presmetaj_ddxyz1( dxyz1, dxyz2, a );

    ddxyz = [ddxyz1; ddxyz2];
    dxyz_p = [0 0 0];
    dxyz_k = (dxyz2 - dxyz1)/2;
    dxyz_sr = Novo_dxyz(xyz2 - xyz1, dxyz_p, dxyz_k, ddxyz1, ddxyz2, td1);
    dxyz = [dxyz_p; dxyz_sr; dxyz_k];
end


function [ ddxyz ] = Presmetaj_ddxyz1( xyz1, xyz2, a )
%   Ovde se presmetuva zabrzuvanjeto ddxyz zaedno so negoviot predznak vo
%   prvoto zakrivuvanje na prviot segment pri pocetna brzina ednakva na 0
%   amplitudata na zabrzuvanjeto e poznata i e ednakva na a. Istate
%   funkcija se koristi i pri presmetkata na zabrzuvanjeto vo vtoroto
%   zakrivuvanje od segmentot samo sto namesto poziciite vo vlezot na
%   funkcijata figuriraat brzini.
    a1 = a; a2 = a; a3 = a;
    ddxyz1 = sign(xyz2(1)-xyz1(1))*a1;
    ddxyz2 = sign(xyz2(2)-xyz1(2))*a2;
    ddxyz3 = sign(xyz2(3)-xyz1(3))*a3;
    ddxyz = [ddxyz1 ddxyz2 ddxyz3];
end


function [ t1 ] = Presmetaj_t1( xyz1, xyz2, td1, a )
%   Odve se presmetuva vremetraenjeto na prvoto zakrivuvanje t na prviot
%   segment sto zapocnuva so pocetna brzina 0.
%   zabrzuvanjeto e konstantno i ednakvo na a
    t1_1 = td1 - sqrt(td1*td1 - abs(2*(xyz2(1)-xyz1(1))/a));
    t1_2 = td1 - sqrt(td1*td1 - abs(2*(xyz2(2)-xyz1(2))/a));
    t1_3 = td1 - sqrt(td1*td1 - abs(2*(xyz2(3)-xyz1(3))/a));
    t1 = [t1_1 t1_2 t1_3];
end


function [ dxyz1 ] = Presmetaj_dxyz1( xyz1, xyz2, td12, t1 )
%   Ovde se presmetuva brzinata dxyz1 na linearniot del od prviot segment.
    dxyz1_1 = (xyz2(1)-xyz1(1))/(td12-(1/2)*t1(1));
    dxyz1_2 = (xyz2(2)-xyz1(2))/(td12-(1/2)*t1(2));
    dxyz1_3 = (xyz2(3)-xyz1(3))/(td12-(1/2)*t1(3));
    dxyz1 = [dxyz1_1 dxyz1_2 dxyz1_3];
end


function [ dxyz ] = Presmetaj_dxyz2( xyz2, xyz3, td23 )
%   Ovde se presmetuva vrednosta na brzinata vo linearniot del na
%   segment pomegju dve megjutocki.
    dxyz1 = (xyz3(1) - xyz2(1))/td23;
    dxyz2 = (xyz3(2) - xyz2(2))/td23;
    dxyz3 = (xyz3(3) - xyz2(3))/td23;
    dxyz = [dxyz1 dxyz2 dxyz3];
end


