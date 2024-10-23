import React from 'react';
import { useState } from 'react';
import { NavBar } from './navbar.js';
import { Footer } from './footer.js';
import './assets/styles/actions.css';

export function Actions()
{
	const [hoveredAction, setHoveredAction] = useState('');

	return (
		<>
		<NavBar />
		<main>
			<p id='mainTextActions'>You can chose multiple actions</p>
			<div id='cardsSection'>
				<Cards setHoveredAction={setHoveredAction}/>
			</div>
			<CardText hoveredAction={hoveredAction} />
		</main>
		<Footer />
		</>
	);
}
function Cards( {setHoveredAction} )
{
	let actions = ['Custom Page', 'Bad request', '404', 'Upload File', 'Delete file', 'Calculations'];
	return (
		<>
		{actions.map( action => (
			<Card
			key={action}
			action={action}
			setHoveredAction={setHoveredAction}
			/>
		))}
		</>
	)
}

function Card({ action, setHoveredAction })
{
	return (
		<div
			className='cards'
			onMouseEnter={() => setHoveredAction(action)}  // Definir l'action survolee
            onMouseLeave={() => setHoveredAction('')} // Reinitialiser le contenu quand l'action n'est plus survolee
		>
			{action}
		</div>
	)
}

function CardText({ hoveredAction }) {
    // Messages à afficher pour chaque carte
    const messages = {
        'Custom Page': 'This will create a custom page by asking you personnal informations.',
        'Bad request': 'This simulates a bad request.',
        '404': 'This displays a 404 error page by accessing a bad URL.',
        'Upload File': 'This lets you upload a file on the server.',
        'Delete file': 'This action deletes a file from the server.',
        'Calculations': 'Perform some calculations here.'
    };

    // Afficher le message correspondant à l'action hoverée
	let animated = hoveredAction ? 'cardsText' : ''
    return (
        <p id={animated}>{hoveredAction ? messages[hoveredAction] : ''}</p>
    );
}
