import React from 'react';
import { NavBar } from './navbar.js';
import { Footer } from './footer.js';
import './assets/styles/actions.css';

export function Actions()
{
	return (
		<>
		<NavBar />
		<main>
			<p id='mainText'>You can chose multiple actions</p>
		</main>
		<Footer />
		</>
	);
}

function cards()
{
	let actions = ['Custom Page', 'Bad request', '404', 'Upload', 'Delete file'];
}
