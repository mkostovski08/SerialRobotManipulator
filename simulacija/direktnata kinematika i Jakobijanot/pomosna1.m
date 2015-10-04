out = [];
xyz_presmetano = [];
td = PosakuvaniVremetraenja( xyz );

t = 0:cekor:(1+td(1)+td(2)+td(3)+td(4)+td(5)-cekor);
for i=1:((1/cekor)*(1+td(1)+td(2)+td(3)+td(4)+td(5)))
    qd = GlavnaPrograma( t(i) );
    qd = qd .* [-1 -1 1 -1 1 -1];
    out = [out; qd];
    xyz_presmetano = [xyz_presmetano; qd2xyz(qd)];
end
st = size(t);
so = size(xyz_presmetano);
plot(t, xyz_presmetano(:, 1))

