function [dq, ddq] = GenerirajTraektorija_PredPosledenSegment( q1, q2, q3, dq_p, td1, td2 )
%   Ovde se presmetuvaat parametrite na traektorijata za pretposledniot
%   segment od traektorijata.
%   Vleznite parametri na finkcijata se:
%   q1 = [q11, q12, q13, q14, q15] pocetna pozicija na segmentot
%   q2 = [q21, q22, q23, q24, q25] krajna pozicija na segmentot
%   q3 = [q31, q32, q33, q34, q35] e krajna pozicija na sledniot segment
%   dq_p = [dq_p1, dq_p2, dq_p3, dq_p4, dq_p5] e pocetnata brzina na
%   pocetokot na prvotot zakrivuvanje
%   td1 e vremetraenjeto na celiot (pretposledniot) segment
%   td2 e vremetraenjeto na sledniot (posledniot) segment
    a = 1000;

    t3 = Presmetaj_t3( q2, q3, td2, a );
    dq_ls2 = Presmetaj_dq3( q2, q3, td2, t3 );
    dq_ls1 = Presmetaj_dq2( q1, q2, td1 );
    dq_k = (dq_ls1 + dq_ls2)/2;
    
    ddq1 = Presmetaj_ddq1( dq_p, dq_ls1, a );
    ddq2 = Presmetaj_ddq1( dq_ls1, dq_ls2, a );
    
    dq_sr = Novo_dq ((q2-q1), dq_p, dq_k, ddq1, ddq2, td1);
    
    dq = [dq_p; dq_sr; dq_k];
    ddq = [ddq1; ddq2];

end


function [ t ] = Presmetaj_t3( q3, q4, td23, a )
%   Odve se presmetuva vremetraenjeto na vtoroto zakrivuvanje t na
%   posledniot segment sto zavrsuva so krajna brzina 0
%   zabrzuvanjeto e konstantno i ednakvo na a
    t1 = td23 - sqrt(td23*td23-(2*(q4(1) - q3(1)))/a);
    t2 = td23 - sqrt(td23*td23-(2*(q4(2) - q3(2)))/a);
    t3 = td23 - sqrt(td23*td23-(2*(q4(3) - q3(3)))/a);
    t4 = td23 - sqrt(td23*td23-(2*(q4(4) - q3(4)))/a);
    t5 = td23 - sqrt(td23*td23-(2*(q4(5) - q3(5)))/a);
    t = [t1 t2 t3 t4 t5];
end


function [ dq ] = Presmetaj_dq3( q1, q2, td, t3 )
%   Ovde se presmetuva brzinata vo linearniot del od posledniot segment.
%   Posledniot segment sekogas zavrsuva so brzina ednakva na nula.
    dq1 = (q2(1) - q1(1))/(td - (1/2)*t3(1));
    dq2 = (q2(2) - q1(2))/(td - (1/2)*t3(2));
    dq3 = (q2(3) - q1(3))/(td - (1/2)*t3(3));
    dq4 = (q2(4) - q1(4))/(td - (1/2)*t3(4));
    dq5 = (q2(5) - q1(5))/(td - (1/2)*t3(5));
    dq = [dq1 dq2 dq3 dq4 dq5];
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


function [ ddq ] = Presmetaj_ddq1( q1, q2, a )
%   Ovde se presmetuva zabrzuvanjeto ddq zaedno so negoviot predznak vo
%   vtoroto zakrivuvanje na posledniot segment pri krajna brzina ednakva na
%   0. Amplitudata na zabrzuvanjeto e poznata i e ednakva na a
    ddq1 = sign(q2(1)-q1(1))*a;
    ddq2 = sign(q2(2)-q1(2))*a;
    ddq3 = sign(q2(3)-q1(3))*a;
    ddq4 = sign(q2(4)-q1(4))*a;
    ddq5 = sign(q2(5)-q1(5))*a;
    ddq = [ddq1 ddq2 ddq3 ddq4 ddq5];
end











