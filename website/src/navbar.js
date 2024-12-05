import React from 'react';
import logo42 from './assets/images/logo-42.png';
import darklogo42 from './assets/images/42-dark-logo.png';
import './assets/styles/navbar.css'
import { Link } from 'react-router-dom';
import {isThemeSet} from './choose_theme';
import { useState, useEffect } from 'react';


const isLightTheme = isThemeSet();

function useIsLogged() {
    const [sessionData, setSessionData] = useState(null);
    const [loading, setLoading] = useState(true);
    const [error, setError] = useState(null);

    useEffect(() => {
        let isMounted = true;

        const fetchDatabase = async () => {
            try {
                const response = await fetch('http://localhost:8081/database', {
                    method: 'GET',
                    headers: {
                        'db_password': 'strongpassword',
                    },
                });

                if (!response.ok) {
                    throw new Error('Erreur lors de la récupération des données');
                }

                const database = await response.json();

                const cookies = document.cookie;
                let cookieFound = cookies.split(';').find(el => el.trim().split('=')[0] === "session_id");
                let session_id;
                if (cookieFound) {
                    session_id = cookieFound.split("=")[1];
                }

                if (isMounted && database["sessions"] && session_id && database["sessions"][session_id]) {
                    setSessionData(database["sessions"][session_id]);
                } else {
                    setSessionData(null);
                }
                setLoading(false);

            } catch (err) {
                if (isMounted) {
                    setError(err.message);
                    setLoading(false);
                }
            }
        };

        fetchDatabase();

        return () => {
            isMounted = false;
        };
    }, []);

    return { sessionData, loading, error };
}

export function NavBar()
{
	return (
		<nav id={isLightTheme ? 'navBarLight' : 'navBar'} >
			<Link to="/actions">
				<div>Webserv</div>
			</Link>
			<LoginLink />
			<Link to="https://42.fr/en/homepage/">
				<img id='navLogo' src={isLightTheme ? darklogo42 : logo42} alt='logo-42'></img>
			</Link>
		</nav>
	)
}

function LoginLink()
{
	const { sessionData } = useIsLogged();
	if (!sessionData)
	{
		return (
			<>
				<Link to="/login">
					<div>Sign in</div>
				</Link>
			</>
		)
	}
	else
	{
		return (
			<>
				<div>Hello {sessionData}</div>
				<LogOut />
			</>
		)
	}
}

function LogOut()
{
	return (
		<>
		<form method="POST" action='/logout'>
			<input type="hidden" name="unset-cookie" value="session-id" />
			<button type="submit">Log out</button>
		</form>
		</>
	)
}
