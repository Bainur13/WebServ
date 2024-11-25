import React from 'react';
import { Link } from 'react-router-dom';
import { useState } from 'react';
import { NavBar } from './navbar.js';
import { Footer } from './footer.js';
import './assets/styles/actions.css';
import { isThemeSet } from './choose_theme.js';

const isLightTheme = isThemeSet();

export function Actions()
{
	const [hoveredAction, setHoveredAction] = useState('');

	return (
		<>
		<NavBar />
		<main id={isLightTheme ? 'actionMainLight' : 'actionMain'}>
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
	let actions = ['Custom Page', 'Bad request', '404', 'Upload File', 'Delete file', 'Change Theme'];
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
			className={isLightTheme ? 'cardsLight' : 'cards'}
			to={definePath(action)}
			onMouseEnter={() => setHoveredAction(action)}
			onMouseLeave={() => setHoveredAction('')}
		>
			{action}
		</Link>
	)
}

function definePath(action)
{
	const paths =
	{
		'Custom Page': '/action/custom_page',
        'Bad request': '/action/bad_request',
        '404': '/action/coucousalut',
        'Upload File': '/action/uploader',
        'Delete file': '/action/delete_file',
        'Change Theme': '/action/choose_theme'
	}
	return paths[action];
}

function CardText({ hoveredAction }) {

    const messages = {
        'Custom Page': 'This will create a custom page by asking you personal information.',
        'Bad request': 'This simulates a bad request. (GET request without body)',
        '404': 'This displays a 404 error page by accessing a bad URL.',
        'Upload File': 'This lets you upload a file to the server.',
        'Delete file': 'This lets you delete a file from the server.',
        'Change Theme': 'Chose dark or light theme'
    };

	let animated = hoveredAction ? 'cardsText' : ''
    return (
        <p id={animated}>{hoveredAction ? messages[hoveredAction] : ''}</p>
    );
}
