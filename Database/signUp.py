#!/usr/bin/env python3

import os
import json
import uuid
from http.cookies import SimpleCookie
from urllib.parse import parse_qs

# Chemin vers la base de données JSON
DB_FILE = "database.json"

# Fonction pour lire la base de données
def load_database():
    try:
        with open(DB_FILE, 'r') as f:
            return json.load(f)
    except FileNotFoundError:
        return {"users": {}, "sessions": {}}

# Fonction pour écrire dans la base de données
def save_database(db):
    with open(DB_FILE, 'w') as f:
        json.dump(db, f, indent=4)

# Fonction pour générer un session_id unique
def generate_session_id():
    return str(uuid.uuid4())

# Charger la base de données
db = load_database()

# Gérer les cookies
cookie = SimpleCookie(os.environ.get("HTTP_COOKIE", ""))

if session_id:
    session_id = session_id.value
else:
    session_id = generate_session_id()
    cookie["session_id"] = session_id
    cookie["session_id"]["path"] = "/"

# Associer session_id à un utilisateur (exemple simplifié)
if session_id not in db["sessions"]:
    db["sessions"][session_id] = {"user": None}  # Pas encore associé à un utilisateur

# Lire les données de l'entrée standard pour les requêtes POST
if os.environ.get("REQUEST_METHOD", "") == "POST":
    content_length = int(os.environ.get("CONTENT_LENGTH", 0))
    post_data = os.stdin.read(content_length)  # Lecture depuis stdin
    params = parse_qs(post_data)
    username = params.get("username", [None])[0]

    if username and username in db["users"]:
        db["sessions"][session_id]["user"] = username

# Sauvegarder les modifications dans la base de données
save_database(db)

# Générer la réponse HTTP
print("HTTP/1.1 302 Found")
print("Content-Type: text/html")
print(cookie.output())  # Ajouter le cookie à la réponse

CONF_FILE = "../file.conf"

def parse_conf(file_path):
    with open(file_path, 'r') as f:
        lines = f.readlines()

    config = {
        "domain": None,
        "redirects": {}
    }

    current_redirect_form = None

    # Lire chaque ligne
    for line in lines:
        line = line.strip()

        # Trouver le domaine
        if line.startswith("domain"):
            config["domain"] = line.split()[1]

        # Trouver les redirections
        if line.startswith("redirect form"):
            success_form = line.split()[2]  # Recupere "/success"
			fail_form = line.split()[3] # Recupere "/fail"
            config["redirects"]["sucess form"] = success_form
			config["redirects"]["fail form"] = fail_form

    return config

config = parse_conf(CONF_FILE)

domain = config.get("domain")

if db["sessions"][session_id]["user"]:
	print("Location:http://" + domain + config["redirects"].get("success form"))
else:
    print("Location:http://" + domain + config["redirects"].get("fail form"))
print()
print("<html><body>")
print("<h1> Redirecting to form treatment </h1>")
print("</body></html>")
