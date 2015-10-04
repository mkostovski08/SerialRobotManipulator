function [ out ] = Forward( q, dq, ddq, td, t )
%Ovde se presmetuva pozicijata na sekoj od zglobovite vo momentot t.
%   Vleznite promenlivi vo funkciojata se:
%   q=[q1;q2;q3;q4;q5] - pocetna pozicija na segmentot
%   dq=[dq11,dq12,dq13;dq21,dq22,dq23; ... ;dq51,dq52,dq53];
%       - dq1i e brzinata na pocetotkot na prvoto zakrivuvanje,
%       - dq2i e brzinata vo linearniot del na segmentot,
%       - dq3i brzinata na krajot na vtorotot zaktivavanje
%   ddq=[ddq11,ddq12,ddq13,ddq14,ddq15; ddq21,ddq22,ddq23,ddq24,ddq25]
%       - ddx1 zabrzuvanje vo prvotot zakrivuvanje
%       - ddx2 e zabrzuvanjeto vo vtoroto zakrivuvanje
%   td e vkupnoto vremetraenje na segmentot
%   t e vremenskiot moment za koj se presmetuva pozicijata.
    out1 = ForwardX( q(1), dq(:, 1), ddq(:, 1), td, t );
    out2 = ForwardX( q(2), dq(:, 2), ddq(:, 2), td, t );
    out3 = ForwardX( q(3), dq(:, 3), ddq(:, 3), td, t );
    out4 = ForwardX( q(4), dq(:, 4), ddq(:, 4), td, t );
    out5 = ForwardX( q(5), dq(:, 5), ddq(:, 5), td, t );
    out = [out1 out2 out3 out4 out5];
end


function [ out ] = ForwardX( x, dx, ddx, td, t )
%   Ovde se presmetuva polozbata vo momentot t po samo 1 koordinata
%   Vleznite promenlivi vo funkciojata se:
%   x - pocetna pozicija na segmentot
%   dx=[dx1; dx2; dx3]
%       - dx1 e brzinata na pocetotkot na prvoto zakrivuvanje,
%       - dx2 e brzinata vo linearniot del na segmentot,
%       - dx3 brzinata na krajot na vtoroto zaktivavanje
%   ddx=[ddx1; ddx2]
%       - ddx1 zabrzuvanje vo prvotot zakrivuvanje
%       - ddx2 e zabrzuvanjeto vo vtoroto zakrivuvanje
%   td e vkupnoto vremetraenje na segmentot
%   t e vremenskiot moment za koj se presmetuva pozicijata.

    if ddx(1) == 0
        if ddx(2) == 0
            out = x(1) + dx(2)*t;
        else
            t2 = (dx(3)-dx(2))/ddx(2);
            t3 = td - t2;
            if t < t3
                out = x(1) + dx(2)*t;
            else
                out1 = x(1) + dx(2)*t3;
                out = out1 + dx(2)*(t-t3) + ddx(2)*(t-t3)*(t-t3)/2;
            end
        end
    elseif ddx(2) == 0
        t1 = (dx(2)-dx(1))/ddx(1);
        if t < t1
            out = x(1) + dx(1)*t + ddx(1)*t*t/2;
        else
            out1 = x(1) + dx(1)*t1 + ddx(1)*t1*t1/2;
            out = out1 + dx(2)*(t-t1);
        end
    else
        t1 = (dx(2)-dx(1))/ddx(1);                                              % t1 e vremetraenje na prvoto zakrivuvanje od segmentot
        t2 = (dx(3)-dx(2))/ddx(2);                                              % t2 e vremetraenje na vtoroto zakrivuvanje od segmentot
        if t < t1
            out = x(1) + dx(1)*t + ddx(1)*t*t/2;
        elseif t < td - t2
            out1 = x(1) + dx(1)*t1 + ddx(1)*t1*t1/2;
            out = out1 + dx(2)*(t-t1);
        else
            out1 = x(1) + dx(1)*t1 + ddx(1)*t1*t1/2;
            out2 = out1 + dx(2)*(td-t1-t2);
            t3 = t1 + (td - t1 - t2);
            out = out2 + dx(2)*(t - t3) + ddx(2)*(t-t3)*(t-t3)/2;
            
        end
    end
end

