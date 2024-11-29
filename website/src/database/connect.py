#!/usr/bin/env python3

import os
import sys
import json
import uuid
from http.cookies import SimpleCookie
from urllib.parse import parse_qs

# Chemin vers la base de données JSON
DB_FILE = "../database.json"

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

# Charger la base de données
db = load_database()

# Gérer les cookies
cookie = SimpleCookie(os.environ.get("HTTP_COOKIE", ""))

MATCH = 0
# Lire les données de l'entrée standard pour les requêtes POST
if os.environ.get("REQUEST_METHOD", "") == "POST":
	content_length_str = os.environ.get("CONTENT_LENGTH", "0")
	content_length = int(content_length_str)
	post_data = sys.stdin.read(content_length)  # Lecture depuis stdin
	params = parse_qs(post_data)
	username = params.get("username", [None])[0]
	password = params.get("password", [None])[0]

	if username and password and username in db["users"] and db["users"][username]["password"] == password:
		MATCH = 1

CONF_FILE = "/tmp/Webserv/file.conf"

def parse_conf(file_path):
	with open(file_path, 'r') as f:
		lines = f.readlines()

	config = {
		"domain": None,
		"redirects": {}
	}

	current_redirect_form = None

	for line in lines:
		line = line.strip()

		if line.startswith("domain"):
			config["domain"] = line.split()[1]

		if line.startswith("redirect form"):
			success_form = line.split()[2]
			fail_form = line.split()[3]
			config["redirects"]["success form"] = success_form
			config["redirects"]["fail form"] = fail_form
		if line.startswith("listen"):
			config["port"] = line.split()[1]
	return config

config = parse_conf(CONF_FILE)
domain = config.get("domain")
port = config.get("port")


if MATCH == 1:
	print("HTTP/1.1 302 Found")
	print("Content-Type: text/html")
	cookie["session_id"] = db["users"][username].get("session_id")
	print("Location: http://" + domain + ":" + port + config["redirects"].get("success form"))
	print(cookie.output())
	print("<html><body>")
	print("<h1> Connexion success, redirecting </h1>")
	print("</body></html>")
else:
	print("HTTP/1.1 302 Found")
	print("Content-Type: text/html")
	print("Location: http://" + domain + ":" + port + config["redirects"].get("fail form"))
	print(cookie.output())
	print("<html><body>")
	print("<h1> Connexion failed, redirecting </h1>")
	print("</body></html>")
