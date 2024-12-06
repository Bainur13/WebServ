import React from "react";
import { NavBar } from "./navbar";
import { Footer } from "./footer"
import "./assets/styles/uploader.css"
import {isThemeSet} from './choose_theme';
import { useState } from 'react';

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


function UploaderForm({ isLightTheme }) {
    const [selectedFileName, setSelectedFileName] = useState("No file chosen");

    const handleFileChange = (event) => {
        const file = event.target.files[0];
        setSelectedFileName(file ? file.name : "No file chosen");
    };

    return (
        <>
            <form
                id={isLightTheme ? 'uploaderFormLight' : "uploaderForm"}
                action="/upload"
                method="POST"
                encType="multipart/form-data"
            >
                <div>
                    <label
                        htmlFor="file"
                        id={isLightTheme ? 'customFileLabelLight' : 'customFileLabel'}
                    >
                        Browse
                    </label>
                    <input
                        type="file"
                        id="file"
                        name="file"
                        style={{ display: 'none' }} // Masquer le champ de fichier
                        onChange={handleFileChange} // Mettre à jour l'état au changement
                        required
                    />
                    <span id="fileNameDisplay" className={isLightTheme ? 'fileNameLight' : 'fileName'}>
                        {selectedFileName}
                    </span>
                </div>
                <button
                    id={isLightTheme ? "uploaderSubmitBtnLight" : "uploaderSubmitBtn"}
                    type="submit"
                >
                    Upload
                </button>
            </form>
        </>
    );
}
