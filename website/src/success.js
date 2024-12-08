import React, { useEffect, useState } from 'react';
import { NavBar } from './navbar';
import { Footer } from './footer';
import { Link, useNavigate } from 'react-router-dom';
import './assets/styles/form_redir.css';
import {isThemeSet} from './choose_theme';


const isLightTheme = isThemeSet();

export function Success() {
  const [countdown, setCountdown] = useState(3);
  const navigate = useNavigate();

  useEffect(() => {
    if (countdown === 0) {
      navigate('/actions');
    } else {
      const timer = setInterval(() => {
        setCountdown(prev => prev - 1);
      }, 1000);

      return () => clearInterval(timer);
    }
  }, [countdown, navigate]);

  return (
    <>
      <NavBar />
	  <main className={isLightTheme ? 'redirMainLight' : 'redirMain'}>
	  	<p>Form has been successfully treated, you will be redirected in {countdown} seconds.</p>
        <Link to='/actions'>Go back to the action page</Link>
      </main>
      <Footer />
    </>
  );
}
