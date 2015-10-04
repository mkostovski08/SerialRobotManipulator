function [dq, ddq] = GenerirajTraektorija_PrvSegment( q1, q2, q3, td1, td2 )
%   Ovde se presemetuvaat parametrite na traektorijata samo za prviot
%   segment ako ni se dadeni pocetnata pozicija, prvata megjutocka,
%   vtorata megjutocka, posakuvanoto vremetraenje na prviot segment i
%   posakuvanoto vremetraenje vtoriot segment.
    a = 1000;

    [ ddq1 ] = Presmetaj_ddq1( q1, q2, a );
    [ t1 ] = Presmetaj_t1( q1, q2, td1, a );
    [ dq1 ] = Presmetaj_dq1( q1, q2, td1, t1 );
    [ dq2 ] = Presmetaj_dq2( q2, q3, td2 );
    [ ddq2 ] = Presmetaj_ddq1( dq1, dq2, a );

    ddq = [ddq1; ddq2];
    dq_p = [0 0 0 0 0];
    dq_k = (dq2 - dq1)/2;
    dq_sr = Novo_dq(q2 - q1, dq_p, dq_k, ddq1, ddq2, td1);
    dq = [dq_p; dq_sr; dq_k];
end


function [ ddq ] = Presmetaj_ddq1( q1, q2, a )
%   Ovde se presmetuva zabrzuvanjeto ddq zaedno so negoviot predznak vo
%   prvoto zakrivuvanje na prviot segment pri pocetna brzina ednakva na 0
%   amplitudata na zabrzuvanjeto e poznata i e ednakva na a. Istate
%   funkcija se koristi i pri presmetkata na zabrzuvanjeto vo vtoroto
%   zakrivuvanje od segmentot samo sto namesto poziciite vo vlezot na
%   funkcijata figuriraat brzini.
    ddq1 = sign(q2(1)-q1(1))*a;
    ddq2 = sign(q2(2)-q1(2))*a;
    ddq3 = sign(q2(3)-q1(3))*a;
    ddq4 = sign(q2(4)-q1(4))*a;
    ddq5 = sign(q2(5)-q1(5))*a;
    ddq = [ddq1 ddq2 ddq3 ddq4 ddq5];
end


function [ t1 ] = Presmetaj_t1( q1, q2, td1, a )
%   Odve se presmetuva vremetraenjeto na prvoto zakrivuvanje t na prviot
%   segment sto zapocnuva so pocetna brzina 0.
%   zabrzuvanjeto e konstantno i ednakvo na a
    t1_1 = td1 - sqrt(td1*td1 - abs(2*(q2(1)-q1(1))/a));
    t1_2 = td1 - sqrt(td1*td1 - abs(2*(q2(2)-q1(2))/a));
    t1_3 = td1 - sqrt(td1*td1 - abs(2*(q2(3)-q1(3))/a));
    t1_4 = td1 - sqrt(td1*td1 - abs(2*(q2(4)-q1(4))/a));
    t1_5 = td1 - sqrt(td1*td1 - abs(2*(q2(5)-q1(5))/a));
    t1 = [t1_1 t1_2 t1_3 t1_4 t1_5];
end


function [ dq1 ] = Presmetaj_dq1( q1, q2, td12, t1 )
%   Ovde se presmetuva brzinata dxyz1 na linearniot del od prviot segment.
    dq1_1 = (q2(1)-q1(1))/(td12-(1/2)*t1(1));
    dq1_2 = (q2(2)-q1(2))/(td12-(1/2)*t1(2));
    dq1_3 = (q2(3)-q1(3))/(td12-(1/2)*t1(3));
    dq1_4 = (q2(4)-q1(4))/(td12-(1/2)*t1(4));
    dq1_5 = (q2(5)-q1(5))/(td12-(1/2)*t1(5));
    dq1 = [dq1_1 dq1_2 dq1_3 dq1_4 dq1_5];
end


function [ dq ] = Presmetaj_dq2( q2, q3, td23 )
%   Ovde se presmetuva vrednosta na brzinata vo linearniot del na
%   segment pomegju dve megjutocki.
    dq1 = (q3(1) - q2(1))/td23;
    dq2 = (q3(2) - q2(2))/td23;
    dq3 = (q3(3) - q2(3))/td23;
    dq4 = (q3(4) - q2(4))/td23;
    dq5 = (q3(5) - q2(5))/td23;
    dq = [dq1 dq2 dq3 dq4 dq5];
end


