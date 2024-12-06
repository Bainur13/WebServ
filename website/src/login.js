import React from "react";
import { NavBar } from './navbar.js';
import { Footer } from './footer.js';
import './assets/styles/404.css';
import { Link } from 'react-router-dom';
import {isThemeSet} from './choose_theme';
import './assets/styles/login.css'

const isLightTheme = isThemeSet();

export function Login()
{
	return (
		<>
		<NavBar />
		<main id={isLightTheme ? 'loginMainLight' : 'loginMain'}>
			<h1 id='loginTitle'>Login</h1>
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
				<div id='internFormDiv'>
					<div id='formLabels'>
						<label> Username </label>
						<label> Password </label>
					</div>
					<div id='formInputs'>
						<input type="text" name="username" required></input>
						<input type="password" name="password" required></input>
					</div>
				</div>
				<button id={isLightTheme ? "creationSubmitBtnLight" : "creationSubmitBtn"} type="submit">Login</button>
			</form>
		</>
	)
}
