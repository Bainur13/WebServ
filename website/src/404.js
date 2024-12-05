import React from "react";
import { NavBar } from './navbar.js';
import { Footer } from './footer.js';
import './assets/styles/404.css';
import {isThemeSet} from './choose_theme';


export function Error404()
{
	return (
		<>
		<NavBar />
		<main id={isThemeSet() ? 'errorMainLight' : 'errorMain'}>
			<h1>404 Error, you lost ?</h1>
			<a id={isThemeSet() ? 'backLinkLight' : 'backLink'} href="javascript:history.back()">Go back</a>
		</main>
		<Footer />
		</>
	)
}
