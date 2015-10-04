out = [];
td = PosakuvaniVremetraenja( xyz );

t = 0:cekor:(1+td(1)+td(2)+td(3)+td(4)+td(5)-cekor);
for i=1:((1/cekor)*(1+td(1)+td(2)+td(3)+td(4)+td(5)))
    out = [out; Presmetaj_Pozicija( xyz, td, t(i) )];
end
st = size(t);
so = size(out);
plot(t, out(:, 1))

