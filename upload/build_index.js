#!/usr/bin/env node

// En-tête HTTP pour indiquer que la réponse est du HTML
console.log("Content-Type: text/html\n");

// Générer le contenu HTML de la réponse
console.log(`
<!DOCTYPE html>
<html>
<head>
    <title>Exemple CGI en JavaScript</title>
</head>
<body>
    <h1>Bonjour depuis un script CGI en JavaScript (Node.js) !</h1>
    <p>Ceci est une page générée dynamiquement par un script CGI en JavaScript.</p>
</body>
</html>
`);

