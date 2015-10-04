function [ out ] = Presmetaj_Pozicija( xyz, td, t )
%   Ovde se generira traektorija. Taa traektorija pretstavuva isprekrsena
%   prava linija so parabolicni zakrivuvanja na kraevite i na mestata na
%   prekrsuvanje.
%   Vlezni parametri se:
%   xyz = [x1, y1, z1; x2, y2, z2; ... ... ...; xn, yn, zn] kade sto x1,
%   y1, z1 se koordinati na pocetokot na traektorijata. xi, yi, zi za i=0:n
%   se koordinatite na prekrsuvanje na traektorijata i xn, yn, zn se
%   koordinatite na zavrsetotkot na traektorijata. td se vremetraenjata na
%   dvizenjeto po traektorijata za sekoj od segmentite na traektorijata. t
%   momentalnoto vreme. Izlezot na funkcijata se koordinatite x, y i z koi 
%   ja opredeluvaat polozbata od traektorijata vo koja se naogjame vo
%   mmomentot t.
persistent Seg;
persistent t_PocSeg;
persistent br_Seg;
persistent dxyz;
persistent ddxyz;

    if isempty(Seg)
        Seg = 1;
        [dxyz, ddxyz] = GenerirajTraektorija_PrvSegment( xyz(1, :), xyz(2, :), xyz(3, :), td(1), td(2) );
        t_PocSeg = 0;
        s = size(xyz);
        br_Seg = s(1)-1;
    elseif Seg == br_Seg+1
        dxyz = [0 0 0; 0 0 0; 0 0 0];
        ddxyz = [0 0 0; 0 0 0];
    elseif t > (t_PocSeg + td(Seg))
        Seg = Seg + 1;
        t_PocSeg = t_PocSeg + td(Seg-1);
        if Seg == 2
            [dxyz, ddxyz] = GenerirajTraektorija_VtorSegment( xyz(2, :), xyz(3, :), xyz(4, :), dxyz(3, :), td(2), td(3) );
        elseif Seg == (br_Seg - 1)
            [dxyz, ddxyz] = GenerirajTraektorija_PredPosledenSegment( xyz(Seg, :), xyz(Seg+1, :), xyz(Seg+2, :), dxyz(3, :), td(Seg), td(Seg+1) );
        elseif Seg == br_Seg
            [dxyz, ddxyz] = GenerirajTraektorija_PosledenSegment( xyz(Seg, :), xyz(Seg+1, :), dxyz(3, :), td(Seg) );
        elseif and(Seg>2, Seg<(br_Seg-1))
            [dxyz, ddxyz] = GenerirajTraektorija_VtorSegment( xyz(Seg, :), xyz(Seg+1, :), xyz(Seg+2, :), dxyz(3, :), td(Seg), td(Seg+1) );
        end
    end

    if Seg < br_Seg+1
        out = Forward( xyz(Seg, :), dxyz, ddxyz, td(Seg), t-t_PocSeg );
    else
        out = xyz(br_Seg+1, :);
    end

end












