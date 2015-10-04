out = [];
xyz_tocno=[];
xyz_presmetano = [];
td = 15;


t = 0:cekor:td;
for i=1:((td/cekor)+1)
    [qd] = GlavnaPrograma( t(i) );
    qd = qd .* [-1 -1 1 -1 1 -1];
    out = [out; qd];
    xyz_presmetano = [xyz_presmetano; qd2xyz(qd*180/pi)];
end
st = size(t);
so = size(xyz_presmetano);
subplot(2, 2, 1)
plot(t, xyz_presmetano(:, 1));
subplot(2, 2, 2)
plot(t, xyz_presmetano(:, 2));
subplot(2, 2, 3)
plot(t, xyz_presmetano(:, 3));
% plot(t, xyz_presmetano(:, 4)), subplot(2, 2, 4)

