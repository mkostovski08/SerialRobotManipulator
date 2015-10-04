function [ out ] = Presmetaj_Pozicija( q, td, t )
%   Ovde se generira traektorija. Taa traektorija pretstavuva isprekrsena
%   prava linija so parabolicni zakrivuvanja na kraevite i na mestata na
%   prekrsuvanje.
%   Vlezni parametri se:
%   q = [qi1, qi2, qi3, qi4, qi5] kade sto qi1, qi2, qi3, qi4, qi5 za i = 1
%   se koordinati na pocetokot na traektorijata. qij za i=2:n-1
%   se koordinatite na prekrsuvanje na traektorijata i qij za i = 1 .. n se
%   koordinatite na zavrsetotkot na traektorijata. td se vremetraenjata na
%   dvizenjeto po traektorijata za sekoj od segmentite na traektorijata. t
%   momentalnoto vreme. Izlezot na funkcijata se koordinatite q1, q2 ... q5
%   koi ja opredeluvaat polozbata od traektorijata vo koja se naogjame vo
%   momentot t dadena vo prostorot na zglobovite.

persistent Seg;
persistent t_PocSeg;
persistent br_Seg;
persistent dq;
persistent ddq;

    if isempty(Seg)
        Seg = 1;
        [dq, ddq] = GenerirajTraektorija_PrvSegment( q(1, :), q(2, :), q(3, :), td(1), td(2) );
        t_PocSeg = 0;
        s = size(q);
        br_Seg = s(1)-1;
    elseif Seg == br_Seg+1;
        dq = [0 0 0 0 0; 0 0 0 0 0; 0 0 0 0 0];
        ddq = [0 0 0 0 0; 0 0 0 0 0];
    elseif t > (t_PocSeg + td(Seg))
        Seg = Seg + 1;
        t_PocSeg = t_PocSeg + td(Seg-1)
        if Seg == 2
            [dq, ddq] = GenerirajTraektorija_VtorSegment( q(2, :), q(3, :), q(4, :), dq(3, :), td(2), td(3) );
        elseif Seg == (br_Seg - 1)
            [dq, ddq] = GenerirajTraektorija_PredPosledenSegment( q(Seg, :), q(Seg+1, :), q(Seg+2, :), dq(3, :), td(Seg), td(Seg+1) );
        elseif Seg == br_Seg
            [dq, ddq] = GenerirajTraektorija_PosledenSegment( q(Seg, :), q(Seg+1, :), dq(3, :), td(Seg) );
        elseif and(Seg>2, Seg<(br_Seg-1))
            [dq, ddq] = GenerirajTraektorija_VtorSegment( q(Seg, :), q(Seg+1, :), q(Seg+2, :), dq(3, :), td(Seg), td(Seg+1) );
        end
    end

    if Seg < br_Seg+1
        out = Forward( q(Seg, :), dq, ddq, td(Seg), t-t_PocSeg );
    else
        out = q(br_Seg+1, :);
    end

end












