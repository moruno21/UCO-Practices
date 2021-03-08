Ejercicios de la P2 de BBDD

1.
SELECT nombrecompleto 
from votantes 
where nombrecompleto LIKE '%n';

2.
SELECT dni 
from votantes 
where dni like '%5%5%5%';

3.
SELECT nombrecompleto 
from votantes 
WHERE fechanacimiento > '1/1/1990';

4.
SELECT v.nombrecompleto, l.nombre 
from votantes v, localidades l 
WHERE numerohabitantes > '300000' 
and v.localidad = l.idlocalidad; 

5.
SELECT v.nombrecompleto, p.comunidad 
from votantes v, provincias p, localidades l 
WHERE l.numerohabitantes > '300000' 
and v.localidad = l.idlocalidad 
and l.provincia = p.idprovincia;

6.
SELECT cd.partido, count(cd.consulta) 
from consultas_datos cd 
group by cd.partido 
having(count(cd.consulta)>0);

7.
SELECT cd.partido, count(cd.consulta) 
from consultas_datos cd 
group by cd.partido;

8.
SELECT p.nombrecompleto 
from partidos p, consultas_datos cd 
where p.idpartido = cd.partido 
group by p.nombrecompleto 
having count(cd.consulta)>10;

9.
SELECT p.nombrecompleto, count(cd.consulta) 
from partidos p, consultas_datos cd 
where p.idpartido = cd.partido 
group by p.nombrecompleto 
having count(cd.consulta)>10;

10.
SELECT p.nombrecompleto, count(cd.consulta) 
from partidos p, consultas_datos cd 
where p.idpartido = cd.partido 
and cd.respuesta='Si' 
and cd.certidumbre>'0,8' 
group by p.nombrecompleto;

