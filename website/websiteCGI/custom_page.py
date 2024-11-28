#!/usr/bin/env python3

import cgi
import cgitb

# Activer le mode de débogage pour les erreurs CGI
cgitb.enable()

def generate_html(parameters):
    """Génère une page HTML dynamique à partir des paramètres fournis."""
    html = """
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Page Dynamique CGI</title>
        <style>
            body {
                font-family: Arial, sans-serif;
                margin: 20px;
                padding: 20px;
                background-color: #f4f4f9;
                color: #333;
            }
            table {
                border-collapse: collapse;
                width: 50%;
                margin-top: 20px;
            }
            table, th, td {
                border: 1px solid #ccc;
            }
            th, td {
                padding: 10px;
                text-align: left;
            }
            th {
                background-color: #f9f9f9;
            }
        </style>
    </head>
    <body>
        <h1>Résultats des paramètres CGI</h1>
        <p>Les informations passées en paramètres sont :</p>
        <table>
            <thead>
                <tr>
                    <th>Nom</th>
                    <th>Valeur</th>
                </tr>
            </thead>
            <tbody>
    """
    for key, value in parameters.items():
        html += f"""
                <tr>
                    <td>{cgi.escape(key)}</td>
                    <td>{cgi.escape(value)}</td>
                </tr>
        """
    html += """
            </tbody>
        </table>
        <p><em>Cette page a été générée dynamiquement par un script CGI en Python.</em></p>
    </body>
    </html>
    """
    return html

# Récupérer les données passées en paramètres (GET ou POST)
form = cgi.FieldStorage()

# Transformer les données du formulaire en dictionnaire
parameters = {key: form.getvalue(key) for key in form.keys()}

# Générer le contenu HTML
html_content = generate_html(parameters)

# Calculer la longueur du contenu HTML
content_length = len(html_content.encode('utf-8'))  # Encodage en UTF-8 pour un calcul correct

# Générer les en-têtes HTTP avec Content-Length
print("HTTP/1.1 200 OK")
print("Content-Type: text/html")
print(f"Content-Length: {content_length}")
print()
print(html_content)
