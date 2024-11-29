import React from "react";
import { NavBar } from './navbar.js';
import { Footer } from './footer.js';
import './assets/styles/404.css';
import { Link } from 'react-router-dom';
import {isThemeSet} from './choose_theme';
import database from './database.json';

const isLightTheme = isThemeSet();

export function Login()
{
	return (
		<>
		<NavBar />
		<main id={isLightTheme ? 'loginMainLight' : 'loginMain'}>
			<h1>Login</h1>
			<LoginForm />
			<Link to="/createaccount">
				<div>Don't have an account yet? Sign Up</div>
			</Link>
		</main>
		<Footer />
		</>
	)
}

function LoginForm()
{
	return (
		<>
			<form id={ isLightTheme ? 'loginFormLight' : "loginForm"} action="/connect" method="POST">
				<div>
					<label for="username"> Username </label>
					<input type="text" name="username" required></input>
					<label for="username"> Password </label>
					<input type="password" name="password" required></input>
				</div>
				<button id={isLightTheme ? "creationSubmitBtnLight" : "creationSubmitBtn"} type="submit">Create</button>
			</form>
		</>
	)
}

export function isLogged()
{
	const cookies = document.cookie;
 	let cookieFound = cookies.split(';').find(el => el.trim().split('=')[0] === "session_id");
	let session_id;
	if (cookieFound)
		session_id = cookieFound.split("=")[1];
	return database["sessions"][session_id];
}
