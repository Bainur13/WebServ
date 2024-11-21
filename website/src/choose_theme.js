import React from 'react';
import { NavBar } from './navbar';
import { Footer } from './footer';
import ReactDOM from 'react-dom/client';

const cookies = document.cookie;

console.log(cookies);

const isThemeSet = (cookies) =>
{
  if (!cookies.length())
		return 0;
}

export function ChooseTheme()
{
	return (
		<>
		<NavBar />
		<main>
			{isThemeSet ? <LightTheme /> : <DarkTheme />}
		</main>
		<Footer />
		</>
	)
}

function LightTheme()
{
	return (
		<>
		<form action='/themelight' method="post">
			<button type="submit">Switch to Light theme</button>
			<input type="hidden" name="theme" value="light" />

		</form>
		</>
	)
}

function DarkTheme()
{
	return (
		<>
		<form action='/darkTheme' method="post">
			<button type="submitBtn">Switch to Dark theme</button>
			<input type="hidden" name="theme" value="dark" />
		</form>
		</>
	)
}
