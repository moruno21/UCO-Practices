1.
SELECT SUBSTR(v.nombrecompleto, 1, INSTR(v.nombrecompleto,' ')) AS nombrepila, l.nombre AS nombrelocalidad, p.comunidad AS nombrecomunidad
FROM votantes v, localidades l, provincias p
WHERE v.localidad = l.idlocalidad
AND l.provincia = p.idprovincia
AND v.localidad IN (1,3,9);

2.
SELECT (l.nombre || ' va antes que ' ||(
  SELECT nombre
  FROM localidades
  WHERE idlocalidad=l.idlocalidad+1)
)
AS ordenacion
FROM localidades l
WHERE l.nombre != 'Valencia'
ORDER BY l.idlocalidad;

3.
SELECT NOMBRE FROM LOCALIDADES
WHERE NUMEROHABITANTES > (
  SELECT NUMEROHABITANTES FROM LOCALIDADES WHERE IDLOCALIDAD = (
    SELECT LOCALIDAD FROM VOTANTES WHERE FECHANACIMIENTO = (
      SELECT MIN(FECHANACIMIENTO) FROM VOTANTES WHERE FECHANACIMIENTO > (
        SELECT MIN(FECHANACIMIENTO) FROM VOTANTES
      )
    )
  )
);

4.
SELECT v.nombrecompleto, v.localidad, DECODE(TRUNC((sysdate - to_date(v.fechanacimiento)) / 365.25), 
0, 'menor edad', 1, 'menor edad', 2, 'menor edad', 3, 'menor edad', 4, 'menor edad', 
5, 'menor edad', 6, 'menor edad', 7, 'menor edad', 8, 'menor edad', 9, 'menor edad', 
10, 'menor edad', 11, 'menor edad', 12, 'menor edad', 13, 'menor edad', 14, 'menor edad',
15, 'menor edad', 16, 'menor edad', 17, 'menor edad', 'mayor edad') AS edad
FROM
    votantes v
WHERE
    v.localidad IN (2,4,8);
/*Buscar el funcionamiento de TRUNC() para entender el ejercicio*/

5.
SELECT l.nombre as localidad, l.numerohabitantes as poblacion, p.comunidad as comunidad
FROM provincias p, localidades l
WHERE p.idprovincia=l.provincia
AND p.idprovincia IN (1,2,3)
AND l.numerohabitantes > ANY (
  SELECT lo.numerohabitantes
  FROM localidades lo
  WHERE lo.provincia = '4'
);

6.
SELECT v.nombrecompleto
FROM votantes v, consultas c
WHERE c.votante=v.dni
AND v.situacionlaboral = 'Activo'
GROUP BY v.nombrecompleto
HAVING COUNT(c.evento) > AVG(c.evento);
  
7.
SELECT l.nombre
FROM localidades l, votantes v
WHERE l.idlocalidad = v.localidad
GROUP BY l.nombre
ORDER BY AVG(DECODE(v.estudiossuperiores, 'Ninguno', 0, 'Basicos', 1, 'Superiores', 2, 'Doctorado', 3)) DESC;

8.
SELECT l.nombre
FROM localidades l, votantes v
WHERE l.idlocalidad = v.localidad
HAVING AVG(DECODE(v.estudiossuperiores,'Ninguno', 0, 'Basicos', 1, 'Superiores', 2, 'Doctorado', 3)) > 
  ALL (
    SELECT AVG(DECODE(v.estudiossuperiores, 'Ninguno', 0, 'Basicos', 1, 'Superiores', 2, 'Doctorado', 3))
    FROM localidades l, votantes v
    WHERE l.idlocalidad = v.localidad
    GROUP BY localidades.provincia /*Agrupamos por provincias para que la comparacion se haga con la media de las provincias*/
  )
GROUP by localidades.nombre;

