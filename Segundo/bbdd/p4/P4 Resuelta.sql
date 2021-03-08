1.
set serveroutput on;
BEGIN
   DBMS_OUTPUT.PUT_LINE('Hola mundo, hoy es '||sysdate);
END;

2.
set serveroutput on;
DECLARE
   v_apellido votantes.nombrecompleto%type;
   v_dni votantes.dni%type;
BEGIN
   SELECT v.dni INTO v_dni
   FROM votantes v
   WHERE fechanacimiento =
     (SELECT min(fechanacimiento)
     FROM votantes);
   SELECT SUBSTR(nombrecompleto, INSTR(nombrecompleto, ' '), (INSTR (nombrecompleto, ' ',1,2)- INSTR(nombrecompleto, ' '))) INTO v_apellido
   FROM votantes
   WHERE fechanacimiento =
     (SELECT min(fechanacimiento)
     FROM votantes);

   DBMS_OUTPUT.PUT_LINE(v_apellido ||', con dni '||v_dni||' es el/la votante con mas años');
END;

3.
set serveroutput on;
DECLARE
   v_nombre votantes.nombrecompleto%type;
   v_correo votantes.email%type;
   mydni NUMBER := 30983712;
BEGIN
   SELECT nombrecompleto, email INTO v_nombre, v_correo
   FROM votantes
   WHERE dni = mydni;

   DBMS_OUTPUT.PUT_LINE(v_nombre ||' con correo: '||v_correo);
END;

4.
set serveroutput on;
DECLARE
   v_apellidos votantes.nombrecompleto%type;
   mydni NUMBER := 30983712;
BEGIN
   SELECT SUBSTR(nombrecompleto, INSTR(nombrecompleto,' '), LENGTH(nombrecompleto)) INTO v_apellidos
   FROM votantes
   WHERE dni = mydni;

   DBMS_OUTPUT.PUT_LINE('Pepe'||v_apellidos);
END;

5.
set serveroutput on;
DECLARE
   v_fechaMayor votantes.fechanacimiento%type;
   v_fechaMenor votantes.fechanacimiento%type;
BEGIN
   SELECT fechanacimiento INTO v_fechaMayor
   FROM votantes
   WHERE fechanacimiento =
     (SELECT min(fechanacimiento)
     FROM votantes);

   SELECT fechanacimiento INTO v_fechaMenor
   FROM votantes
   WHERE fechanacimiento =
     (SELECT max(fechanacimiento)
     FROM votantes);
   DBMS_OUTPUT.PUT_LINE(v_fechaMayor);
   DBMS_OUTPUT.PUT_LINE(v_fechaMenor);
   DBMS_OUTPUT.PUT_LINE(ceil((v_fechaMenor - v_fechaMayor)/365.25));
END;

