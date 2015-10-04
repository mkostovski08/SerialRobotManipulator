
xyz_presmetano = [];
q = [];

xyz = qd2xyz([0 0 0 0 0]);
xyz_p = [400 11.5 185];
q_poc = invkine(xyz_p)
td_poc = td_DoPoc(q_poc);
[dqd, ddqd] = DoPoc(q_poc, td_poc)

t = 0:cekor:td_poc;
for i=1:((td_poc/cekor)+1)
    q_pom = qd_DoPoc( dqd, ddqd, td_poc, t(i) );
    q = [q; q_pom];
    xyz_presmetano = [xyz_presmetano; qd2xyz(q_pom)];
end

st = size(t);
so = size(xyz_presmetano);
plot(t, q(:, 1)), subplot(2,2, 1)
plot(t, q(:, 2)), subplot(2,2, 2)
plot(t, q(:, 3)), subplot(2,2, 3)
plot(t, q(:, 4)), subplot(2,2, 4)


