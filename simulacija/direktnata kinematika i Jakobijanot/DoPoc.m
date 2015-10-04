function [ dqd, ddqd ] = DoPoc( q_poc, td )
%   Ovde se presmetuva traektorijata na dvizenje na robotot za toj da se
%   pozicionira vo pocetnata tocka od posakuvanata traektorija na dvizenje.
    a = 1000;
    ddqd = sign(q_poc).*a;
    dqd = Novo_dq(q_poc, ddqd, td);
end


function [ dqd ] = Novo_dq( delta, a, td )
%   Ovde se presmeuva brzinata vo lineaniot del od segmentot
    if a(1) > 0
        tmp1 = (a(1)*td - sqrt( a(1)*a(1)*td*td-4*a(1)*delta(1) ))/2;
    else
        tmp1 = (a(1)*td + sqrt( a(1)*a(1)*td*td-4*a(1)*delta(1) ))/2;
    end
    if a(2) > 0
        tmp2 = (a(2)*td - sqrt( a(2)*a(2)*td*td-4*a(2)*delta(2) ))/2;
    else
        tmp2 = (a(2)*td + sqrt( a(2)*a(2)*td*td-4*a(2)*delta(2) ))/2;
    end
    if a(3) > 0
        tmp3 = (a(3)*td - sqrt( a(3)*a(3)*td*td-4*a(3)*delta(3) ))/2;
    else
        tmp3 = (a(3)*td + sqrt( a(3)*a(3)*td*td-4*a(3)*delta(3) ))/2;
    end
    if a(4) > 0
        tmp4 = (a(4)*td - sqrt( a(4)*a(4)*td*td-4*a(4)*delta(4) ))/2;
    else
        tmp4 = (a(4)*td + sqrt( a(4)*a(4)*td*td-4*a(4)*delta(4) ))/2;
    end
    if a(5) > 0
        tmp5 = (a(5)*td - sqrt( a(5)*a(5)*td*td-4*a(5)*delta(5) ))/2;
    else
        tmp5 = (a(5)*td + sqrt( a(5)*a(5)*td*td-4*a(5)*delta(5) ))/2;
    end

    dqd = [tmp1, tmp2, tmp3, tmp4, tmp5];
end

