import React from "react";
import { NavBar } from './navbar.js';
import { Footer } from './footer.js';
import './assets/styles/404.css';
import {isThemeSet} from './choose_theme';

const isLightTheme = isThemeSet();

export function CreateAccount()
{
	return (
		<>
		<NavBar />
		<main id={isLightTheme ? 'accCreationMainLight' : 'accCreationMain'}>
			<h1>Create an account</h1>
			<AccountCreationForm />
		</main>
		<Footer />
		</>
	)
}

function AccountCreationForm()
{
	return (
		<>
			<form id={ isLightTheme ? 'accCreationFormLight' : "accCreationForm"} action="/signup" method="POST">
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
