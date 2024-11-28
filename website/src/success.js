import React, { useEffect, useState } from 'react';
import { NavBar } from './navbar';
import { Footer } from './footer';
import { Link, useNavigate } from 'react-router-dom';

export function Success() {
  const [countdown, setCountdown] = useState(3); // Le compteur commence à 3 secondes
  const navigate = useNavigate();

  useEffect(() => {
    if (countdown === 0) {
      navigate('/actions'); // Redirige après la fin du compte à rebours
    } else {
      // Décrémente le compteur chaque seconde
      const timer = setInterval(() => {
        setCountdown(prev => prev - 1);
      }, 1000);

      // Nettoyage du timer quand le composant est démonté ou quand le compte à rebours atteint 0
      return () => clearInterval(timer);
    }
  }, [countdown, navigate]);

  return (
    <>
      <NavBar />
      <main>
        <p>Form has been successfully treated, you will be redirected in {countdown} seconds.</p>
        <Link to='/actions'>Go back to the action page</Link>
      </main>
      <Footer />
    </>
  );
}
