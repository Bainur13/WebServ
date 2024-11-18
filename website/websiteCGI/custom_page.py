#!/usr/bin/env python3

import time

print("Content-Type: text/html\n")



time.sleep(10)

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
