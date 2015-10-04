function [ qd ] = GlavnaPrograma( t )
%   Ova e glavnata programa sto ja izvrsuva Matlab Function Block. Velznite
%   promenlivi se q - pozicijata na zglobovite na robotot i t e vremenskiot
%   moment vo tekot na simulacijata. Izlezot pretstavuva posakuvanite
%   pozicii na zglobovite za robotot da se postavi vo pozicijata od
%   traektorijata vo tocno toj moment t.

    persistent inicializacija;
    persistent td;
    persistent q;
    if isempty(inicializacija)
        q = get_q(  )
        td = PosakuvaniVremetraenja( q )
        inicializacija = 1;
    end
    
    q_p = Presmetaj_Pozicija( q, td, t );
    q_p = q_p .* [-1 -1 1 -1 1];
    q_p = q_p * pi/180;
    qd = [q_p 0];
end

