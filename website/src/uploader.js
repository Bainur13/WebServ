import React from "react";
import { NavBar } from "./navbar";
import { Footer } from "./footer"
import "./assets/styles/uploader.css"
import {isThemeSet} from './choose_theme';

const isLightTheme = isThemeSet();

export function Uploader()
{
	return (
		<>
		<NavBar />
		<main id={ isLightTheme ? 'uploaderMainLight' : "uploaderMain"}>
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
			<form id={ isLightTheme ? 'uploaderFormLight' : "uploaderForm"} action="/upload" method="POST" enctype="multipart/form-data">
				<div>
					<label for="file">Choisir un fichier :</label>
					<input type="file" id="file" name="file" required></input>
				</div>
				<button id={isLightTheme ? "uploaderSubmitBtnLight" : "uploaderSubmitBtn"} type="submit">Upload</button>
			</form>
		</>
	);
}
