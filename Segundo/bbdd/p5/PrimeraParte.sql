1.
SET SERVEROUTPUT ON;

DECLARE
    CURSOR fila IS SELECT p.presidente FROM partidos p; 
BEGIN
    FOR nombre IN fila LOOP
        IF SUBSTR(nombre.presidente, INSTR(nombre.presidente,' ',1,1)-1,1) LIKE 'o' THEN
            IF SUBSTR(nombre.presidente, INSTR(nombre.presidente,' ',1,2)-1,1) LIKE 'o' THEN
                IF SUBSTR(nombre.presidente, INSTR(nombre.presidente,' ',1,3)-1,1) LIKE 'o' THEN
                    DBMS_OUTPUT.PUT_LINE(nombre.presidente);
                END IF;
            END IF;
        END IF;
    END LOOP;
END;

2.


3. 
SET SERVEROUTPUT ON;

DECLARE
    CURSOR votantes IS SELECT v.nombrecompleto FROM votantes v WHERE SUBSTR(v.dni, LENGTH(v.dni-1), 1) LIKE localidad+1; 
    total NUMBER := 0;
BEGIN
    FOR votante IN votantes LOOP
        DBMS_OUTPUT.PUT_LINE(votante.nombrecompleto);
        total := total+1;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Hay un total de '||total||' votantes');
END;

4.