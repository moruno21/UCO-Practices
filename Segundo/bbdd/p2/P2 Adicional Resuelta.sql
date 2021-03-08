Ejercicios de la P2 Adicional BBDD

1.
SELECT dni
from votantes
where telefono like '%6%6%'
and telefono not like '%6%6%6%';

2.
SELECT telefono
from votantes
where telefono like '%66%6%'
or telefono like '%6%66%'
or telefono like '%666%'
and telefono not like '%6%6%6%6%';

3.
SELECT p.nombre, l.nombre
from localidades l, provincias p
where substr(l.numerohabitantes, -1,1) like l.provincia
and l.provincia=p.idprovincia;

4.
SELECT nombrecompleto
from votantes
where substr(telefono,-1,1) like substr(dni,-1,1);

5.
SELECT nombrecompleto
from votantes
where nombrecompleto like '%s%'
and fechanacimiento < '12/2/1990';

6.
SELECT distinct c.votante
from consultas c
order by votante desc;

7.
SELECT v.dni
from votantes v, consultas c
where c.votante=v.dni
group by dni
having count(c.evento)>3;

8.
SELECT v.nombrecompleto, count(c.evento)
from votantes v, consultas c
where c.votante=v.dni
group by v.nombrecompleto
having count(c.evento)>3
order by count(evento) asc;

9.
SELECT v.nombrecompleto, l.nombre
from votantes v, localidades l
where l.idlocalidad=v.localidad
and l.numerohabitantes > '300000';

10.
SELECT p.nombrecompleto, max(cd.certidumbre)
from partidos p, consultas_datos cd
where cd.partido=p.idpartido
group by p.nombrecompleto;

11.
SELECT v.nombrecompleto, avg(cd.certidumbre)
from votantes v, consultas_datos cd, consultas c
where cd.consulta=c.idconsulta
and v.dni=c.votante
and cd.respuesta='Si'
group by v.nombrecompleto;

12.
SELECT v.nombrecompleto, avg(cd.certidumbre)
from votantes v, consultas_datos cd, consultas c
where cd.consulta=c.idconsulta
and v.dni=c.votante
and cd.respuesta='Si'
having avg(cd.certidumbre)<=0.8 and  avg(cd.certidumbre)>=0.5
group by v.nombrecompleto;

13.
SELECT p.nombrecompleto, avg(cd.certidumbre)
from partidos p, consultas_datos cd
where p.idpartido=cd.partido
and cd.respuesta= 'No'
and cd.certidumbre>=0.6
group by p.nombrecompleto;
