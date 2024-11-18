#!/usr/bin/env python3

import time
# Imprime la ligne de statut HTTP
print("HTTP/1.1 200 OK")

# Imprime les headers nécessaires
print("Content-Type: text/html")
print("Content-Length: 241")  # Longueur calculée du body
print()  # Ligne vide pour séparer les headers du body

time.sleep(5)
# Imprime le contenu HTML
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
