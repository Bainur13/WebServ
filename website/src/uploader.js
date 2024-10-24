import React from "react";
import { NavBar } from "./navbar";
import { Footer } from "./footer"

export function Uploader()
{
	return (
		<>
		<NavBar />
		<main>
			<h1>Upload a file</h1>
			<UploaderForm />
		</main>
		<Footer />
		</>
	);
}

function UploaderForm()
{
	return (
		<>
			<form action="/upload" method="POST" enctype="multipart/form-data">
				<label for="file">Choisir un fichier :</label>
				<input type="file" id="file" name="file"></input>
				<button type="submit">Envoyer</button>
			</form>
		</>
	);
}
