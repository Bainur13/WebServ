import React, { useState, useEffect } from 'react';
import { NavBar } from './navbar.js';
import { Footer } from './footer.js';
import './assets/styles/delete_file.css'

export function FetchAndDeleteFiles() {
    const [config, setConfig] = useState({ domain: '', port: '' });
    const [links, setLinks] = useState([]);
    const [error, setError] = useState(null);
    const [loading, setLoading] = useState(true);
    const [deleting, setDeleting] = useState(false);

    useEffect(() => {
        const fetchConfig = async () => {
            try {
                const response = await fetch("/file.conf");
                if (!response.ok) {
                    throw new Error('Impossible de charger la configuration.');
                }
                const configText = await response.text();
                const domainMatch = configText.match(/domain\s+(\S+)/);
                const portMatch = configText.match(/listen\s+(\d+)/);

                if (!domainMatch || !portMatch) {
                    throw new Error('Domaine ou port introuvable dans la configuration.');
                }

                setConfig({ domain: domainMatch[1], port: portMatch[1] });
            } catch (err) {
                setError(err.message);
            }
        };

        fetchConfig();
    }, []);

    useEffect(() => {
        const fetchFiles = async () => {
            if (!config.domain || !config.port) return;

            try {
                const response = await fetch(`http://${config.domain}:${config.port}/delete`, {
					method: 'GET',
				  });
				console.log(config.domain);
				console.log(config.port);
                if (!response.ok) {
                    throw new Error('Erreur lors de la récupération des fichiers.');
                }

                const htmlContent = await response.text();

                // Analyser le HTML pour extraire les liens
                const linksArray = extractLinksFromHTML(htmlContent);
                setLinks(linksArray);
            } catch (err) {
                setError(err.message);
            } finally {
                setLoading(false);
            }
        };

        fetchFiles();
    }, [config]);

    const extractLinksFromHTML = (htmlContent) => {
        const parser = new DOMParser();
        const doc = parser.parseFromString(htmlContent, 'text/html');
        const links = doc.querySelectorAll('a');

		console.log("LINKS = ");
		console.log(links);
        return Array.from(links)
            .filter(link => link.getAttribute('href'))
            .map(link => ({
                href: link.getAttribute('href'),
                name: link.textContent,
            }));
    };

    const handleDelete = async (path) => {
        if (deleting) return; // éviter les suppressions multiples en parallèle
        setDeleting(true);

        try {
            const response = await fetch(`http://${config.domain}:${config.port}/delete/${path}`, {
                method: 'DELETE',
                headers: {
                    'Content-Type': 'application/json',
                }
            });

            if (!response.ok) {
                throw new Error('Erreur lors de la suppression du fichier.');
            }

            // Rafraîchir la liste après suppression
            alert('Fichier ou dossier supprimé avec succès');
            // Refaites le fetch des fichiers après suppression si nécessaire
            setLinks(links.filter(link => link.href !== path));
        } catch (err) {
            setError(err.message);
        } finally {
            setDeleting(false);
        }
    };

    if (error)
	{
		return (
			<>
			<NavBar />
			<main id='deleteFileMain'>
				<p>Erreur : {error}</p>
			</main>
			<Footer />
			</>
		)
	}
    if (loading)
	{
		return (
			<>
			<NavBar />
			<main id='deleteFileMain'>
				<p>Chargement des fichiers...</p>;
			</main>
			<Footer />
			</>
		)
	}

    return (
		<>
		<NavBar />
		<main id='deleteFileMain'>
			<h1>Liste des fichiers et répertoires</h1>
			{links.length === 0 ? (
				<p>Aucun fichier ou répertoire trouvé.</p>
			) : (
				<div>
				{links.map((link, index) => (
						<div className='fileCard'>
							<a href={`http://${config.domain}:${config.port}/` + link.href.substr(2)} target="_blank" rel="noopener noreferrer">
								{link.name}
							</a>
							<button className='deleteBtn' onClick={() => handleDelete(link.href)}>
								Supprimer
							</button>
						</div>
				))}
				</div>
			)}
		</main>
		<Footer />
		</>
    );
}
