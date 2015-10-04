function [ qd ] = qd_DoPoc( dqd, ddqd, td, t )
%   Ovde se presmetuva pozicijata vo prostorot na zglobovi pooddelno.

    tmp1 = qd_DoPocZg(dqd(1), ddqd(1), td, t);
    tmp2 = qd_DoPocZg(dqd(2), ddqd(2), td, t);
    tmp3 = qd_DoPocZg(dqd(3), ddqd(3), td, t);
    tmp4 = qd_DoPocZg(dqd(4), ddqd(4), td, t);
    tmp5 = qd_DoPocZg(dqd(5), ddqd(5), td, t);

    qd = [tmp1 tmp2 tmp3 tmp4 tmp5];
end

function [ qd ] = qd_DoPocZg( dqd, ddqd, td, t )
%   Ovde se presmetuva pozicijata za samo eden zglob.
persistent state;
    if isempty(state)
        state = 1;
        disp('Pocetok!!!');
    end
    if ddqd == 0
        qd = 0;
    else
        t1 = dqd/ddqd;
        t_ls = td - 2*t1;
        if t < t1
                if state==1
                    state = 2;
                    disp('Ova e prvoto zakrivuvanje');
                end
            qd = ddqd*t*t/2;
        elseif t < td - t1
                if state==2
                    state = 3;
                    disp('Ova e linearniot del od segmentot');
                end
            pom = ddqd*t1*t1/2;
            qd = pom + dqd*(t-t1);
        else
                if state==3
                    state = 4;
                    disp('Ova e vtoroto zakrivuvanje');
                end
            pom1 = ddqd*t1*t1/2;
            pom2 = dqd*t_ls;
            qd = pom1 + pom2 + dqd*(t-t1-t_ls) - ddqd*(t-t1-t_ls)*(t-t1-t_ls)/2;
        end
    end
end


