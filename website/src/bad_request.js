import React from 'react';
import { Link } from 'react-router-dom';
import { useState } from 'react';
import { NavBar } from './navbar.js';
import { Footer } from './footer.js';
import './assets/styles/actions.css';
import { isThemeSet } from './choose_theme.js';

function BadRequest()
{
	return (
		<>
		<NavBar />
		<main></main>
		<Footer />
		</>
	)
}
