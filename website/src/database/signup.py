#!/usr/bin/env python3
import sys
import os
import json
import uuid
from http.cookies import SimpleCookie
from urllib.parse import parse_qs

# Chemin vers la base de données JSON
DB_FILE = "./website/src/database.json"

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

session_id = generate_session_id()

created = 0
# Lire les données de l'entrée standard pour les requêtes POST
if os.environ.get("REQUEST_METHOD", "") == "POST":
	content_length = int(os.environ.get("CONTENT_LENGTH", 0))
	post_data = sys.stdin.read(content_length)  # Lecture depuis stdin
	params = parse_qs(post_data)
	username = params.get("username", [None])[0]
	password = params.get("password", [None])[0]
	if username and password and username not in db["users"]:
		db["users"][username] = {
			"password" : password,
			"session_id" : session_id
		}
		db["sessions"][session_id] = username
		created = 1

# Sauvegarder les modifications dans la base de données
save_database(db)

# Générer la réponse HTTP

CONF_FILE = "./file.conf"

def parse_conf(file_path):
	with open(file_path, 'r') as f:
		lines = f.readlines()
	config = {
		"domain": None,
		"redirects": {},
		"port" : None
	}
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
			config["redirects"]["success form"] = success_form
			config["redirects"]["fail form"] = fail_form
		if line.startswith("listen"):
			config["port"] = line.split()[1]
	return config

config = parse_conf(CONF_FILE)
domain = config.get("domain")
port = config.get("port")

print("HTTP/1.1 302 Found")
print("Content-Type: text/html")

if created == 1:
	print("Location:http://" + domain + ":" + port + config["redirects"].get("success form"))
	print(cookie.output())
	print()
	print("<html><body>")
	print("<h1> Account created, redirecting</h1>")
	print("</body></html>")
else:
	print("Location:http://" + domain + ":" + port + config["redirects"].get("fail form"))
	print(cookie.output())
	print()
	print("<html><body>")
	print("<h1> Account creation failed, redirecting</h1>")
	print("</body></html>")
