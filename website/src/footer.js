import React from "react";
import './assets/styles/footer.css'
import {isThemeSet} from './choose_theme';


export function Footer()
{
	return (
		<footer id={isThemeSet() ? 'footerLight' : 'footer'}>
			<div id={isThemeSet() ? 'footerUpperPartLight' : 'footerUpperPart'}>
				<p>Coded by</p>
			</div>
			<div id={isThemeSet() ? 'footerLowerPartLight' : 'footerLowerPart'}>
				<p>Urbain Dumas</p>
				<p>Vincent Da Conceicao Ramos</p>
			</div>
		</footer>
	);
}
