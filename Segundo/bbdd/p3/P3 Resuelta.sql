1.
SELECT nombrecompleto
from votantes v
where substr(dni, 8, 8) = (localidad+1);

2.
SELECT v.nombrecompleto, l.nombre
from votantes v, localidades l
where l.idlocalidad = decode(v.localidad, 1,9,2,9,3,9, v.localidad);

3.
SELECT p.siglas
from partidos p, eventos_resultados er
where p.idpartido=er.partido
group by p.siglas
having count(er.partido) = (select max(count (er.partido))
from partidos p, eventos_resultados er
where p.idpartido=er.partido
group by p.siglas);

4.
SELECT v.dni
from votantes v
where v.fechanacimiento = (select min(v.fechanacimiento) from votantes v
where v.fechanacimiento > (select min(v.fechanacimiento) from votantes v ));

5.
SELECT v.dni, count(c.votante)
from consultas c, votantes v
where v.dni=c.votante group by v.dni
order by count(c.votante) DESC;

6.
SELECT v.dni, count(c.votante)
from consultas c, votantes v
where v.dni=c.votante
group by v.dni
having count(c.votante) > (select avg(count(c.votante))
from votantes v, consultas c
where v.dni=c.votante
group by v.dni)
order by count(c.votante) DESC;

7.
SELECT v.nombrecompleto
from consultas c, votantes v
where v.dni=c.votante
group by v.nombrecompleto
having count(c.votante) > (select avg(count(c.votante))
from votantes v, consultas c
where v.dni=c.votante
group by v.nombrecompleto);

8.
SELECT v.dni, count(c.votantes)
from votantes v, consultas c
where v.dni=c.votante
where v.fechanacimiento != (select min(v.fechanacimiento) from votantes v
where v.fechanacimiento > (select min(v.fechanacimiento) from votantes v))
group by v.dni
order by count(c.votantes) DESC;

