import React from 'react';
import { Footer } from './footer.js';
import './assets/styles/homepage.css';
import { Link } from 'react-router-dom';
import { useEffect, useState } from 'react';
import logo42 from './assets/images/logo-42.png';

export function Homepage()
{
	return (
		<div id='mainContainer'>
			<header id='topSide'>
				<h1 id='homePageTitle'>Web Serv</h1>
				<img id='logo42' src={logo42} alt='logo-42'></img>
			</header>
			<main>
				<div id='mainText'>
					<p id='firstSentence'>Web Serv is a 42 project that consists to build a HTTP server from scratch.</p>
					<p id='secondSentence'>It has to be powered in C++</p>
				</div>
				<MainBtn />
			</main>
			<Footer />
		</div>
	);
}

export function MainBtn() {
    const [isActive, setIsActive] = useState(false);

    useEffect(() => {
        const timer = setTimeout(() => {
            setIsActive(true); // met l'etat isActive a true apres un delai
        }, 6500); // 7 secondes (durée de l'animation + délai)

        return () => clearTimeout(timer); // Nettoyage du timer
    }, []);

    return (
		<Link to="/actions">
			<button id="mainButton" className={isActive ? 'active' : ''}>
				Explore Now
			</button>
		</Link>
    );
}
