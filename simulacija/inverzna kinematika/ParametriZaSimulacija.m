clear all;

        cekor = 0.01;
        xyz1 = [400 11.5 185];
        xyz2 = [350 50 150];
        xyz3 = [250 200 120];
        xyz4 = [200 250 50];
        xyz5 = [250 300 0];
        xyz6 = [350 320 0];
xyz = [xyz1; xyz2; xyz3; xyz4; xyz5; xyz6];

% konstantite na upravuvacot
koef=100;
Kp = [1.8784 1.9570 1.8952 1.9813 1.9602 2.0000]*koef*10;
Kd = [0.8784 0.9570 0.8952 0.9813 0.9602 1.0000]*koef*(-1);
Ki = [0.1216 0.0430 0.1048 0.0187 0.0398 0]*koef;

% Pocetnata pozicija na robotot.
q_pocetna = [0 -90 0 5.1677896760508614e-14 -90];
% q_pocetna = q_pocetna + invkine([200 0 0]);
q_pocetna = q_pocetna*pi/180;


