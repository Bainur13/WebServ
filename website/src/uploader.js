import React from "react";
import { NavBar } from "./navbar";
import { Footer } from "./footer"
import "./assets/styles/uploader.css"

export function Uploader()
{
	return (
		<>
		<NavBar />
		<main id="uploaderMain">
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
			<form id="uploaderForm" action="/upload" method="POST" enctype="multipart/form-data">
				<div>
					<label for="file">Choisir un fichier :</label>
					<input type="file" id="file" name="file"></input>
				</div>
				<button id="uploaderSubmitBtn" type="submit">Upload</button>
			</form>
		</>
	);
}
