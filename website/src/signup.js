import React from "react";
import { NavBar } from './navbar.js';
import { Footer } from './footer.js';
import './assets/styles/404.css';
import {isThemeSet} from './choose_theme';
import { Link } from 'react-router-dom';
import './assets/styles/signup.css';
import './assets/styles/custompage.css';

const isLightTheme = isThemeSet();

export function CreateAccount()
{
	return (
		<>
		<NavBar />
		<main id={isLightTheme ? 'accCreationMainLight' : 'accCreationMain'}>
			<h1 id='accCreationTitle'>Create an account</h1>
			<AccountCreationForm />
			<Link className={isLightTheme ? 'switchLinksLight' : 'switchLinks'} to="/login">
				<div>Already have an account ? Log here</div>
			</Link>
		</main>
		<Footer />
		</>
	)
}

function AccountCreationForm()
{
	return (
		<>
			<form className="accCreationForm" action="/signup" method="POST">
				<div id='internFormDiv'>
					<div id='formLabels'>
						<label> Username </label>
						<label> Password </label>
					</div>
					<div id={ isLightTheme ? 'formInputsLight' : 'formInputs'}>
						<input type="text" name="username" required></input>
						<input type="password" name="password" required></input>
					</div>
				</div>
				<button id={isLightTheme ? "formSubmitBtnLight" : "formSubmitBtn"} type="submit">Create</button>
			</form>
		</>
	)
}
