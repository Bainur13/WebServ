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
			<p id='mainTextActions'>You can chose multiple actions</p>
			<div id='cardsSection'>
				<Cards />
			</div>
		</main>
		<Footer />
		</>
	);
}

function Cards()
{
	let actions = ['Custom Page', 'Bad request', '404', 'Upload File', 'Delete file', 'Calculations'];
	return (
		<>
		{actions.map( action => (
			<Card key={action} action={action}/>
		))}
		</>
	)
}

function Card({ action })
{
	return (
		<div className='cards'>{action}</div>
	)
}
