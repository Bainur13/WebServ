#!/usr/bin/env python3
import os
import cgi
from datetime import datetime

# Fonction pour déterminer le signe astrologique
def get_astrological_sign(day, month):
    signs = [
        ("Capricorn", 12, 22, 1, 19),
        ("Aquarius", 1, 20, 2, 18),
        ("Pisces", 2, 19, 3, 20),
        ("Aries", 3, 21, 4, 19),
        ("Taurus", 4, 20, 5, 20),
        ("Gemini", 5, 21, 6, 20),
        ("Cancer", 6, 21, 7, 22),
        ("Leo", 7, 23, 8, 22),
        ("Virgo", 8, 23, 9, 22),
        ("Libra", 9, 23, 10, 22),
        ("Scorpio", 10, 23, 11, 21),
        ("Sagittarius", 11, 22, 12, 21),
    ]
    for sign, start_month, start_day, end_month, end_day in signs:
        if (month == start_month and day >= start_day) or (month == end_month and day <= end_day):
            return sign
    return "Capricorne"

# Fonction pour générer la page HTML
def generate_html(first_name, last_name, sign):
    descriptions = {
        "Capricorn": "Ambitious and determined.",
        "Aquarius": "Creative and independent.",
        "Pisces": "Emotional and intuitive.",
        "Aries": "Energetic and courageous.",
        "Taurus": "Reliable and patient.",
        "Gemini": "Curious and communicative.",
        "Cancer": "Protective and empathetic.",
        "Leo": "Charismatic and confident.",
        "Virgo": "Analytical and perfectionist.",
        "Libra": "Diplomatic and charming.",
        "Scorpio": "Passionate and intense.",
        "Sagittarius": "Optimistic and adventurous.",
    }
    description = descriptions.get(sign, "Description indisponible.")
    return f"""
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>Astro CGI</title>
    </head>
    <body>
        <h1>Hello, {first_name} {last_name}!</h1>
        <h2>Your astrological sign is: {sign}</h2>
        <p>{description}</p>
        <a href="javascript:history.back()">Go back</a>
    </body>
    </html>
    """

# Récupérer les données de la requête
form = cgi.FieldStorage()

# Extraire les champs
first_name = form.getvalue("firstName", "Inconnu")
last_name = form.getvalue("lastName", "Inconnu")
birth_date = form.getvalue("birthday", "2000-01-01")

# Calculer le signe astrologique
try:
    birth_date = datetime.strptime(birth_date, "%Y-%m-%d")
    sign = get_astrological_sign(birth_date.day, birth_date.month)
except ValueError:
    sign = "Inconnu"

# Générer la page HTML
html_content = generate_html(first_name, last_name, sign)

# Encode the HTML content in UTF-8 and calculate the content length
html_content_utf8 = html_content.encode('utf-8')
content_length = len(html_content_utf8)

# Print the HTTP headers and content
print("HTTP/1.1 200 OK")
print("Content-Type: text/html; charset=UTF-8")
print(f"Content-Length: {content_length - 2}")
print()
print(html_content)  # Decode it back to a string to print
