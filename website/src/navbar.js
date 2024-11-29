import React from 'react';
import logo42 from './assets/images/logo-42.png';
import darklogo42 from './assets/images/42-dark-logo.png';
import './assets/styles/navbar.css'
import { Link } from 'react-router-dom';
import {isThemeSet} from './choose_theme';
import {isLogged} from './login';


const isLightTheme = isThemeSet();
const userName = isLogged();

console.log(userName);

export function NavBar()
{
	return (
		<nav id={isLightTheme ? 'navBarLight' : 'navBar'} >
			<Link to="/actions">
				<div>Webserv</div>
			</Link>
			<LoginLink />
			{userName ? <LogOut /> : ""}
			<Link to="https://42.fr/en/homepage/">
				<img id='navLogo' src={isLightTheme ? darklogo42 : logo42} alt='logo-42'></img>
			</Link>
		</nav>
	)
}

function LoginLink()
{

  if (!userName)
  {
	return (
		<>
			<Link to="/login">
				<div>Sign in</div>
			</Link>
		</>
	)
  }
  else
  {
	return (
		<>
			<div>Hello {userName}</div>
		</>
	)
  }
}

function LogOut()
{
	return (
		<>
		<form method="POST" action='/logout'>
			<input type="hidden" name="unset-cookie" value="session-id" />
			<button type="submit">Log out</button>
		</form>
		</>
	)
}
