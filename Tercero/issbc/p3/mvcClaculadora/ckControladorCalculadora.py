# -*- coding: utf-8 -*-
"""
Created on Mon Nov 17 16:26:13 2014

@author: acalvo
"""

import ckModAppCalculadora as mapp

def eventSumar(a,b):
    suma=mapp.suma(a,b)
    return suma
     

def eventRestar(a,b):
    resta=mapp.resta(a,b)
    return resta

def eventMultiplicar(a,b):
    producto=mapp.producto(a,b)
    return producto
    

def eventDividir(a,b):
    division=mapp.division(a,b)
    return division
    
def eventModulo(a,b):
    modulo=mapp.modulo(a,b)
    return modulo

