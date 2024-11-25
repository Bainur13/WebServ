import React from "react";
import { NavBar } from './navbar.js';
import { Footer } from './footer.js';
import './assets/styles/success.css';
import { Link } from 'react-router-dom';
import {isThemeSet} from './choose_theme';


export function Success()
{
	return (
		<>
		<NavBar />
		<main>
		<p> Form has been successfully treated </p>
		<Link to='/actions'>Go back to action page</Link>
		</main>
		<Footer />
		</>
	)
}
