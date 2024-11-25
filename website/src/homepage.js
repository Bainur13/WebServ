import React from 'react';
import { Footer } from './footer.js';
import './assets/styles/homepage.css';
import { Link } from 'react-router-dom';
import { useEffect, useState } from 'react';
import logo42 from './assets/images/logo-42.png';
import {isThemeSet} from './choose_theme';
import darklogo42 from './assets/images/42-dark-logo.png';



const isLightTheme = isThemeSet();

export function Homepage()
{
	return (
		<div id={ isLightTheme ? 'mainContainerLight' : 'mainContainer'}>
			<header id='topSide'>
				<h1 id='homePageTitle'>Web Serv</h1>
				<img id='logo42' src={isLightTheme ? darklogo42 : logo42} alt='logo-42'></img>
			</header>
			<main>
				<div id='mainText'>
					<p id='firstSentence'>Web Serv is a 42 project that consists in building a HTTP server from scratch.</p>
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
        }, 5000); // 5 secondes (durée de l'animation + délai)

        return () => clearTimeout(timer); // Nettoyage du timer
    }, []);

    return (
		<button id={isLightTheme ? "mainButtonLight" : "mainButton"} className={isActive ? 'active' : ''}>
				<Link to="/actions">
				Explore Now
				</Link>
		</button>
    );
}
