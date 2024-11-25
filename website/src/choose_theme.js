import React from 'react';
import { NavBar } from './navbar';
import { Footer } from './footer';
import ReactDOM from 'react-dom/client';
import './assets/styles/choose_theme.css'


const isThemeSet = () =>
{
	const cookies = document.cookie;
	return cookies.split(';').some(el => el.trim() === "theme=light");
}

export function ChooseTheme()
{
	return (
		<>
		<NavBar />
		<main id='themeMain'>
			{isThemeSet() ? <DarkTheme /> : <LightTheme /> }
		</main>
		<Footer />
		</>
	)
}

function LightTheme()
{
	return (
		<>
		<form className='themeForm' action='/themelight' method="post">
			<button className='themeSubmitBtn' type="submit">Switch to Light theme</button>
			<input type="hidden" name="theme" value="light" />
		</form>
		<p className='themeText'>Close your eyes! Light mode incoming! 💡 </p>
		</>
	)
}

function DarkTheme()
{
	return (
		<>
		<form className='themeForm' action='/themedark' method="post">
			<button className='themeSubmitBtn' type="submit">Switch to Dark theme</button>
			<input type="hidden" name="theme" value="dark" />
		</form>
		<p className='themeText'>Enter the dark side... 👨‍💻 </p>
		</>
	)
}
