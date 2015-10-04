function [ dq ] = Novo_dq( delta_q, dq1, dq2, ddq1, ddq2, td )
%   Ovde se presmetuva posakuvanata vrednost na brzinata vo linearniot del
%   na segmentot taka sto toj segmentot zapocnuva so tocno opredeleni 
%   brzina dq1 i zabrzuvanje ddq1 i zavrsuva so tocno opredeleni brzina
%   dq2 i zabrzuvanje ddq2. Vremetraenjeto na segmentot e td, a
%   pominatoto rastojanie e delta_q.
    tmp1 = Presmetaj_dq_sr( delta_q(1), dq1(1), dq2(1), ddq1(1), ddq2(1), td );
    tmp2 = Presmetaj_dq_sr( delta_q(2), dq1(2), dq2(2), ddq1(2), ddq2(2), td );
    tmp3 = Presmetaj_dq_sr( delta_q(3), dq1(3), dq2(3), ddq1(3), ddq2(3), td );
    tmp4 = Presmetaj_dq_sr( delta_q(4), dq1(4), dq2(4), ddq1(4), ddq2(4), td );
    tmp5 = Presmetaj_dq_sr( delta_q(5), dq1(5), dq2(5), ddq1(5), ddq2(5), td );
    dq = [tmp1, tmp2, tmp3, tmp4, tmp5];
end


function [ dq_sr ] = Presmetaj_dq_sr( delta_q, dq1, dq2, ddq1, ddq2, td )
%   Ovde se presmetuva posakuvanata vrednost na brzinata vo linearniot del
%   na segmentot taka sto toj segment zapocnuva so tocno opredeleni 
%   brzina dq1 i zabrzuvanje ddq1 i zavrsuva so tocno opredeleni brzina
%   dq2 i zabrzuvanje ddq2. Vremetraenjeto na segmentot e td, a
%   pominatoto rastojanie e delta_q.
%   OVDE MORA DA SE NAPOMENE DEKA FUNKCIJATA E SAMO ZA EDEN ZGLOB I
%   DOKOLKU SAKAME DA RABOTIME SO POVEKJE OD EDEN ZGLOB FUNKCIJATA
%   MORA DA SE POVIKUVA POODDELNO ZA SEKOJ ZGLOB.
    if ddq1 == 0
        dq_sr = dq1;
    elseif ddq2 == 0
        dq_sr = dq2;
    elseif ddq1 == ddq2
%        disp('A = 0')
        B = td + (dq1/ddq1) - (dq2/ddq2);
        C = ((dq2*dq2)/(2*ddq2)) - ((dq1*dq1)/(2*ddq1)) - delta_q;
        dq_sr = -C/B;
    else
        A = ((1/ddq2) - (1/ddq1))/2
        B = td + (dq1/ddq1) - (dq2/ddq2)
        C = ((dq2*dq2)/(2*ddq2)) - ((dq1*dq1)/(2*ddq1)) - delta_q
        if B == 0;
            dq_sr = sqrt(-C/A);
        elseif B > 0
%            disp('B > 0');
            dq_sr = (-B + sqrt(B*B-4*A*C))/(2*A);
        else
%            disp('B < 0');    
            dq_sr = (-B - sqrt(B*B-4*A*C))/(2*A);
        end
    end
end



