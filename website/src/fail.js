import {React, useEffect} from "react";
import { NavBar } from './navbar.js';
import { Footer } from './footer.js';
import './assets/styles/success.css';
import { Link, useNavigate} from 'react-router-dom';
import {isThemeSet} from './choose_theme';


export function Fail() {
	const navigate = useNavigate();

	useEffect(() => {
	  // Redirection après 3 secondes
	  const timer = setTimeout(() => {
		navigate('/actions');
	  }, 3000);

	  // Nettoyer le timer au démontage du composant
	  return () => clearTimeout(timer);
	}, [navigate]);

	return (
	  <>
		<NavBar />
		<main>
		  <p>Form treatment has failed, you will be redirected in 3 seconds.</p>
		  <Link to="/actions">Go back to the action page</Link>
		</main>
		<Footer />
	  </>
	);
  }
