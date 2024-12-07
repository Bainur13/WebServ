import React from 'react';
import { Link } from 'react-router-dom';
import { useState } from 'react';
import { NavBar } from './navbar.js';
import { Footer } from './footer.js';
import './assets/styles/actions.css';
import { isThemeSet } from './choose_theme.js';

const isLightTheme = isThemeSet();

export function BadRequest()
{
	return (
		<>
		<NavBar />
		<main id={isLightTheme ? 'themeMainLight' : 'themeMain'}>
			<form className='themeForm' method="post">
				<button className={isLightTheme ? 'themeSubmitBtnLight' : 'themeSubmitBtn'} type="submit">Send a POST request without body</button>
			</form>
		</main>
		<Footer />
		</>
	)
}
