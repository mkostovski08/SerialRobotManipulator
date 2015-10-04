function [dq, ddq] = GenerirajTraektorija_VtorSegment( q1, q2, q3, dq_p, td1, td2 )
%   Ovde se presmetuvaat parametrite na traektorijata za segmentot pomegju
%   dve megjutocki, osven pretposledniot segment.
%   Vleznite parametri na finkcijata se:
%   q1 = [q11, q12, q13, q14, q15] pocetna pozicija na segmentot
%   q2 = [q21, q22, q23, q24, q25] krajna pozicija na segmentot
%   q3 = [q31, q32, q33, q34, q35] e krajna pozicija na sledniot segment
%   dq1 = [dq1, dq1, dq1, dq4, dq5] e pocetnata brzina na pocetokot na
%   prvotot zakrivuvanje
%   td1 e vremetraenjeto na celiot segment
%   td2 e vremetraenjeto na sledniot segment
    a = 1000;

    dq_ls = Presmetaj_dq2( q1, q2, td1 );
    dq_ls2 = Presmetaj_dq2( q2, q3, td2 );
    dq_k = (dq_ls + dq_ls2)/2;
    
    ddq1 = Presmetaj_ddq1( dq_p, dq_ls, a );
    ddq2 = Presmetaj_ddq1( dq_ls, dq_k, a );

    ddq = [ddq1; ddq2];
    dq_sr = Novo_dq((q2-q1), dq_p, dq_k, ddq1, ddq2, td1);
    dq = [dq_p; dq_sr; dq_k];

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


function [ ddq ] = Presmetaj_ddq1( dq1, dq2, a )
%   Ovde se presmetuva zabrzuvanjeto ddxyz zaedno so negoviot predznak vo
%   zakrivuvanjeto na segmentot pri pocetna brzina ednakva na dxyz1 i
%   krajna brzina ednakva na dxyz2. Amplitudata na zabrzuvanjeto e poznata
%   i e ednakva na a.
    a1 = a; a2 = a; a3 = a;
    ddq1 = sign(dq2(1)-dq1(1))*a;
    ddq2 = sign(dq2(2)-dq1(2))*a;
    ddq3 = sign(dq2(3)-dq1(3))*a;
    ddq4 = sign(dq2(4)-dq1(4))*a;
    ddq5 = sign(dq2(5)-dq1(5))*a;
    ddq = [ddq1 ddq2 ddq3 ddq4 ddq5];
end


















