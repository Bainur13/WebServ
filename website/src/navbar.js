import React from 'react';
import logo42 from './assets/images/logo-42.png';
import darklogo42 from './assets/images/42-dark-logo.png';
import './assets/styles/navbar.css'
import { Link } from 'react-router-dom';
import {isThemeSet} from './choose_theme';


const isLightTheme = isThemeSet();

export function NavBar()
{
	return (
		<nav id={isLightTheme ? 'navBarLight' : 'navBar'} >
			<Link to="/actions">
				<div>Webserv</div>
			</Link>
			<main></main>
			<Link to="https://42.fr/en/homepage/">
				<img id='navLogo' src={isLightTheme ? darklogo42 : logo42} alt='logo-42'></img>
			</Link>
		</nav>
	)
}
