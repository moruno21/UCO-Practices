#!/bin/bash

who | awk '{printf "El usuario " $1 " lleva conectado desde las " $4 " y lleva ausente " $5 "\n" }'