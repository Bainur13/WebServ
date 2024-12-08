import React, { useState, useEffect } from 'react';

export function FetchAndDeleteFiles() {
    const [config, setConfig] = useState({ domain: '', port: '' });
    const [htmlResponse, setHtmlResponse] = useState(null);
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
                setHtmlResponse(htmlContent);

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

            alert('Fichier ou dossier supprimé avec succès');
            setLinks(links.filter(link => link.href !== path));
        } catch (err) {
            setError(err.message);
        } finally {
            setDeleting(false);
        }
    };

    if (error) return <p>Erreur : {error}</p>;
    if (loading) return <p>Chargement des fichiers...</p>;

    return (
        <div>
            <h1>Liste des fichiers et répertoires</h1>
            {links.length === 0 ? (
                <p>Aucun fichier ou répertoire trouvé.</p>
            ) : (
                <ul>
                    {links.map((link, index) => (
                        <li key={index}>
                            <a href={`http://${config.domain}:${config.port}/` + link.href.substr(2)} target="_blank" rel="noopener noreferrer">
                                {link.name}
                            </a>
                            <button onClick={() => handleDelete(link.href)}>
                                Supprimer
                            </button>
                        </li>
                    ))}
                </ul>
            )}
        </div>
    );
}
