% Ova e idealnata funkcija za presmetka na inverznata kinematika
% rabotniot prostor e svera so radiusi 160 i 560. nadvor od tie radiusi
% robotot ne e vo sostojba da dofati i resenieto na inverznata kinematika
% ke bide pogresno.

function angles = invkine(xyz)
% Ova e funkcijata so koja se presmetuva inverznata kinematika na
% robotskata raka.
% theta230 = [theta20 theta30]
% xyz = [x y z]
% b = [x z theta1 theta4]
    theta230=[0 0];
    theta4 = (pi/2) * (1 - ((xyz(1)*xyz(1)+xyz(2)*xyz(2)+xyz(3)*xyz(3))/(580*580)));

    if xyz(1)==0
        if xyz(2) > 0
            theta1 = pi/2;
        elseif xyz(2) < 0
            theta1 = -pi/2;
        else
            % disp("nezavisno od prvata koordinata")
            theta1 = 0;
        end
    else
        theta1 = atan(xyz(2)/xyz(1));
    end

    b = [xyz(1) xyz(2) xyz(3) theta1 theta4];

    options = optimoptions('fsolve','Display','none');
    f = @(theta230) myfun_new(theta230, b);
    jointangles = fsolve(f, theta230, options);

    angles = [theta1 jointangles theta4 0]*180/pi;
    angles = poednostavi(angles);
end


function F = myfun(theta230, b)
% Ova e funkcijata so koja se presmetuvaat aglite na vtoriot i tretiot
% zglob na robotot vo zavisnost od pozicijata na krajniot izvrsen element.
% Pri toa se koristi iterativna postapka pri koja theta0 = [theta(2) theta(3)]
% dodeka vlezot vo funkcijata e b = [x, z, theta(1) theta(4)]
    theta = [b(3) theta230(1) theta230(2) b(4)];
    x = b(1);
    z = b(2);

    F = [(3555*cos(theta(2)+theta(3)) - 3297*sin(theta(2)+theta(3)+theta(4)) + 2500*cos(theta(2)) - 50*x/(3*cos(theta(1))));    
         (9891*cos(theta(2)+theta(3)+theta(4)) + 10665*sin(theta(2)+theta(3)) + 7500*sin(theta(2)) - 50*z + 1492)];
 
end


function xyz = pom1(theta)
% Ova e pomosna funkcija so koja se dobivat funkciite za presmetka na x, 
% y i z koordinatite na krajniot izvrsen element vo zavisnost od 
% vrednostite na aglite na zglobovite na robotot.
    d1 = 29.84; a2 = 150; a3 = 213.3; d5 = 197.82;

    L1 = Link([theta(1) d1 0 pi/2]);
    L2 = Link([theta(2) 0  a2 0]);
    L3 = Link([theta(3) 0  a3 0]);
    L4 = Link([theta(4) 0  0 -pi/2]);
    L5 = Link([theta(5) d5 0 0]);
    R = SerialLink([L1 L2 L3 L4 L5], 'name', 'Robot');

    T = R.fkine(theta);

    x = T(1, 4);
    y = T(2, 4);
    z = T(3, 4);
    xyz = [x, y, z];
end


function theta_iz = poednostavi(theta_vl)
% Ovaa funkcija vrsi poednostavuvanje na matricata od agli. So drugi
% zborovi gi normalizira vrednostite na aglite da bidat vo granicite od
% (-180,180)

    s = size(theta_vl);
    n = s(2);
    for i=1:n
        if theta_vl(i) > 180
            theta_iz(i) = theta_vl(i) - 360;
        elseif theta_vl(i) < -180
            theta_iz(i) = theta_vl(i) + 360;
        else
            theta_iz(i) = theta_vl(i);
        end
    end
end


function F = myfun_new(theta230, b)
% Ova e funkcijata so koja se presmetuvaat aglite na vtoriot i tretiot
% zglob na robotot vo zavisnost od pozicijata na krajniot izvrsen element.
% Pri toa se koristi iterativna postapka pri koja theta230 = [theta(2) theta(3)]
% dodeka vlezot vo funkcijata e b = [x, z, theta(1) theta(4)]
    theta = [b(4) theta230(1) theta230(2) b(5)];
    xyz = [b(1) b(2) b(3)];
    if b(1) == 0
        x = b(2);
    else
        x = b(1)/cos(theta(1));
    end
    
    z = b(3);

    F = [(150*sin(theta(2)) + 213.3*sin(-theta(2)-theta(3)+(pi/2)) + 197.82*sin(-theta(2)-theta(3)-theta(4)+(pi/2)) - x);    
         (150*cos(theta(2)) - 213.3*cos(-theta(2)-theta(3)+(pi/2)) - 197.82*cos(-theta(2)-theta(3)-theta(4)+(pi/2)) - z)];
 
end
