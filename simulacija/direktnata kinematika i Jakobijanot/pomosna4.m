clear all;

q = [1.6468, 4.9887, -28.4963, 38.0019, 0];
[ td ] = td_DoPoc( q );
[ dqd, ddqd ] = DoPoc( q, td );

qd = [];
cekor = 0.01;
t = 0:cekor:td;
for i=1:((1/cekor)*td)
    qd = [qd; qd_DoPoc( dqd, ddqd, td, t(i) )];
end

plot(t(1:((1/cekor)*td)), qd(:, 2))