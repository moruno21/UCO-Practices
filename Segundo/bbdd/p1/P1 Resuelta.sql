1.
Cargar votacion.sql

2.
SELECT table_name 
FROM user_tables;

3.
DESCRIBE consultas;
DESCRIBE consultas_datos;
DESCRIBE eventos;
DESCRIBE eventos_resultados;
DESCRIBE localidades;
DESCRIBE partidos;
DESCRIBE provincias;
DESCRIBE votantes;

4.
DROP TABLE consultas CASCADE CONSTRAINTS;
DROP TABLE consultas_datos CASCADE CONSTRAINTS;
DROP TABLE eventos CASCADE CONSTRAINTS;
DROP TABLE eventos_resultados CASCADE CONSTRAINTS;
DROP TABLE localidades CASCADE CONSTRAINTS;
DROP TABLE partidos CASCADE CONSTRAINTS;
DROP TABLE provincias CASCADE CONSTRAINTS;
DROP TABLE votantes CASCADE CONSTRAINTS;

5.
INSERT INTO votantes
VALUES (30653845, 'Maria Gonzalez Ramirez', 'Doctorado', 'Activo', 'goram@telefonica.es', 1, '21/08/1989', 677544822);

6.
SELECT * 
FROM votantes;

7.
DELETE 
FROM votantes v 
WHERE v.dni = 30653845;

8.
Realizar inserciones con:
INSERT INTO tabla
VALUES (dni, nombre, ...);

9.
SELECT nombre, tipo, fecha 
FROM eventos;

10.
SELECT nombre||' de tipo '||tipo AS convocatoria 
FROM eventos;

11.
Concatenar columas