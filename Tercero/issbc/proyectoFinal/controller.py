import model as model

ESTADIOSORIGIN = {}
ESTADIOSEND = {}
EXCURSIONORIGIN = {}
EXCURSIONEND = {}

PLANNINGEXCURSION = model.Planning({"origin": 0, "end": 8}, "Plan de Excursion")
PLANNINGESTADIOS = model.Planning({"origin": 0, "end": 8}, "Plan de Estadios")

# Obtenermos los origenes de los estadios
for x in PLANNINGESTADIOS.getOrigins():
    ESTADIOSORIGIN[x.name] = x.id

# Obtenermos los destinos de los estadios
for x in PLANNINGESTADIOS.getEnds():
    ESTADIOSEND[x.name] = x.id

# Obtenermos los origenes de las excursiones
for x in PLANNINGEXCURSION.getOrigins():
    EXCURSIONORIGIN[x.name] = x.id

# Obtenermos los destinos de las excursiones
for x in PLANNINGEXCURSION.getEnds():
    EXCURSIONEND[x.name] = x.id

# Se planifica el evento
def PlanningEvent(domain, restriction, population):
    planning = model.Planning(restriction, domain)
    return planning.execute(population)
