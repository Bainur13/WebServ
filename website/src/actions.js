import React from 'react';
import { Link } from 'react-router-dom';
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
			<p id='mainTextActions'>Try one of the following actions</p>
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
		<Link
			className='cards'
			to={definePath(action)}
			onMouseEnter={() => setHoveredAction(action)}  // Definir l'action survolee
			onMouseLeave={() => setHoveredAction('')} // Reinitialiser le contenu quand l'action n'est plus survolee
		>
			{action}
		</Link>
	)
}

function definePath(action)
{
	const paths =
	{
		'Custom Page': '/custom_page',
        'Bad request': '/bad_request',
        '404': '/coucousalut',
        'Upload File': '/uploader',
        'Delete file': '/delete_file',
        'Calculations': '/calulations'
	}
	return paths[action];
}

function CardText({ hoveredAction }) {
    // Messages à afficher pour chaque carte
    const messages = {
        'Custom Page': 'This will create a custom page by asking you personal information.',
        'Bad request': 'This simulates a bad request.',
        '404': 'This displays a 404 error page by accessing a bad URL.',
        'Upload File': 'This lets you upload a file to the server.',
        'Delete file': 'This lets you delete a file from the server.',
        'Calculations': 'Perform some calculations here.'
    };

    // Afficher le message correspondant à l'action hoverée
	let animated = hoveredAction ? 'cardsText' : ''
    return (
        <p id={animated}>{hoveredAction ? messages[hoveredAction] : ''}</p>
    );
}
