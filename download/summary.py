#!/usr/bin/env python3

import time

# Envoi immédiat de l'entête HTTP
print("Content-Type: text/html\n")

# Simulation d'une exécution longue
time.sleep(10)  # Attente de 10 secondes

# Envoi de la réponse HTML
print("""
<!DOCTYPE html>
<html>
<head>
    <title>Sommaire CGI en Python</title>
</head>
<body>
    <h1>Bienvenue sur la page sommaire générée par un script CGI en Python !</h1>
    <p>Ceci est une page sommaire générée dynamiquement par un script CGI en Python.</p>
</body>
</html>
""")

