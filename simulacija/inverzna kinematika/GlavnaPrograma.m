function [ qd ] = GlavnaPrograma( t )
%   Ova e glavnata programa sto ja izvrsuva Matlab Function Block. Velznite
%   promenlivi se q - pozicijata na zglobovite na robotot i t e vremenskiot
%   moment vo tekot na simulacijata. Izlezot pretstavuva posakuvanite
%   pozicii na zglobovite za robotot da se postavi vo pozicijata od
%   traektorijata vo tocno toj moment t.

    persistent inicializacija;
    persistent td;
    persistent td_poc;
    persistent q_poc;
    persistent dqd;
    persistent ddqd;
    persistent xyz;
    qd = [0 0 0 0 0 0];
    
    if isempty(inicializacija)
        xyz = get_xyz(  );
        td = PosakuvaniVremetraenja( xyz );
        q_poc = invkine(xyz(1, :));
        if isequal(q_poc, [0 0 0 0]);                                       % Ovde se proveruva dali manipulatorot momentlatno se naoga vo pocetnata pozicija na traektorijata
            td_poc = 0;
        else
            td_poc = td_DoPoc(q_poc);
            [dqd, ddqd] = DoPoc(q_poc, td_poc);
        end
        inicializacija = 1;
    end
    
    if t < td_poc
        q_pom = qd_DoPoc( dqd, ddqd, td_poc, t );
        qd = [q_pom, 0] * pi/180;
        qd = qd .* [-1 -1 1 -1 1 -1];
    else
        xyz_p = Presmetaj_Pozicija( xyz, td, t-td_poc );
        qd = [invkine( xyz_p ) 0] * pi/180;
        qd = qd .* [-1 -1 1 -1 1 -1];
    end
end

