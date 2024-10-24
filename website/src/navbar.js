import React from 'react';
import logo42 from './assets/images/logo-42.png';
import './assets/styles/navbar.css'
import { Link } from 'react-router-dom';


export function NavBar()
{
	return (
		<nav id='navBar'>
			<Link to="/actions">
				<div>Webserv</div>
			</Link>
			<main></main>
			<Link to="https://42.fr/en/homepage/">
				<img id='navLogo' src={logo42} alt='logo-42'></img>
			</Link>
		</nav>
	)
}
