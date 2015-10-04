function [ td ] = td_DoPoc( q )
%   Ovde se presmetuva vremetraenjeto sto mu e potrebno na robotot da se
%   pozicionira vo pocetnata tocka od traektorijata ako toj ne e vekje vo
%   pocetnata tocka od traektorijata.
    
    koef = 1/50;
    s = size(q);
    td = 0;
    for i = 1:(s(2));
        if td < q(i)
            td = q(i);
        end
    end
    td = td*koef;
end

